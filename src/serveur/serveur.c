#include "headerServeur.h"

void recupOrder(const int sClient, char *buff) {
    int restRead = 0;
    restRead = read(sClient, buff, 3);
    if (restRead == -1) {
        printf("impossible de lire.\n");
        return;
    }
}

void recupTime(char *newDateAndTime, time_t time) {
    // Permet de récupérer l'heure local au format HH:MM:SS
    strftime(newDateAndTime, sizeof(newDateAndTime), "%X", localtime(&time));
}

void addLog(bufferToReceive *report, const char *msg, const char *prefixe) {
    memset(report->time, 0, sizeof(report->time));
    recupTime(report->time, time(NULL));
    fprintf(report->log, "[%s]:", report->time);
    fprintf(report->log, "%s%s\n", prefixe, msg);
}

void recupInformation(int sClient, bufferToReceive *report) {
    char sizePseudo[3];
    int retRead = 0;

    retRead = read(sClient, sizePseudo, 2);
    if (retRead == -1) {
        printf("impossible de lire.\n");
        exit(EXIT_FAILURE);
    }

    sizePseudo[2] = '\0';
    report->sizePseudo = atoi(sizePseudo);

    // On passe à la récupération du pseudo.
    retRead = read(sClient, report->pseudo, report->sizePseudo);
    if (retRead == -1) {
        printf("impossible de lire.\n");
        exit(EXIT_FAILURE);
    }
    addLog(report, report->pseudo, PSEUDO_LOG);
}

void newReport(int sClient, bufferToReceive *report) {
    //On doit savoir la taille du pseudo. Qui est forcément inférieur à 25 (donc 2 char pour la taille.)
    // On autorise quand même un message à plus de 10^256 de caractère.
    char sizeMsg[1];
    char buff[256];
    int retRead = 0;
    int i = 0;
    int done = 0;
    char *pathToOpen = NULL;
    char buffTime[50];

    recupInformation(sClient, report);
    // On récupère la taille du message maintenant.
    do {
        retRead = read(sClient, sizeMsg, 1);
        if (retRead == -1) {
            printf("impossible de lire.\n");
            exit(EXIT_FAILURE);
        }
        if (sizeMsg[0] == '|') {
            done = 1;
        } else {
            buff[i] = sizeMsg[0];
            i++;
        }
    } while (done == 0);
    buff[i] = 0;
    report->sizeMsg = atoi(buff);

    // On récupère enfin le message que l'on stock dans un fichier.
    report->msg = malloc(sizeof(char) * report->sizeMsg);
    retRead = read(sClient, report->msg, report->sizeMsg);
    if (retRead == -1) {
        printf("impossible de lire.\n");
        exit(EXIT_FAILURE);
    }
    report->msg[report->sizeMsg + 1] = 0;

    addLog(report, "fin recup information sur socket.", INF_LOG);

    // On alloue la taille de report_Client/ + le pseudo de la personne + ".txt"
    pathToOpen = malloc(sizeof(char) * (14 + report->sizePseudo + 4));

    strcpy(pathToOpen, "report_Client/");
    pathToOpen[14] = 0;
    strcat(pathToOpen, report->pseudo);
    strcat(pathToOpen, ".txt");

    FILE *fd = fopen(pathToOpen, "a");
    if (fd == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        close(sClient);
        //TODO:Envoyer un message d'erreur au client.
        exit(EXIT_FAILURE);
    }
    time_t forRapport = time(NULL);
    strftime(buffTime, sizeof(buffTime), "%d %B %Y a %X", localtime(&forRapport));
    fprintf(fd, "**** rapport du %s ****\n", buffTime);
    fprintf(fd, "****************************************\n\n");

    fprintf(fd, "%s\n\n", report->msg);

    free(pathToOpen);
    pathToOpen = NULL;
    fclose(fd);
    free(report->msg);
    addLog(report, "fin de la session.", INF_LOG);
    close(sClient);
}


void newSendReport(int sClient, bufferToReceive *report) {
    FILE *fd = NULL;
    char pathToOpen[50] = {0};
    int readRet = 0;
    recupInformation(sClient, report);

    strcat(pathToOpen, "report_Client/");
    strcat(pathToOpen, report->pseudo);
    strcat(pathToOpen, ".txt\0");

    fd = fopen(pathToOpen, "r");
    if (fd == NULL) {
        addLog(report, "fichier inexistant", ERR_LOG);
        EnvoieMessage(sClient, "%c", '\0');
        close(sClient);
        addLog(report, "fin de sessions.", END_LOG);
        return;
    } else {
        // Cela permet de sauter dans le client la verification du pseudo.
        while (readRet != EOF) {
            readRet = fgetc(fd);
            if (readRet != EOF)
                EnvoieMessage(sClient, "%c", readRet);
        }
    }
    EnvoieMessage(sClient, "%c", '\0');
    addLog(report, "fin d'envoie Rapport.", INF_LOG);
    close(sClient);
    fclose(fd);
}

int newCommunication(int sClient) {
    int resFork = 0;
    char buff[3] = {0};

    recupOrder(sClient, buff);

    resFork = fork();
    if (resFork == -1){
        perror("Fork\n");
        return -1;
    }
    if (resFork == 0) {
        // On  est dans le fils;
        char *pathLog = NULL;
        bufferToReceive report;

        time_t timestamp = time(NULL);
        strftime(report.time, sizeof(report.time), "%m-%d-%Y", localtime(&timestamp));
        timestamp = time(NULL);

        pathLog = malloc(sizeof(char) * (8 + strlen(report.time)));
        strcat(pathLog, "log/");
        strcat(pathLog, report.time);
        strcat(pathLog, ".txt");
        // On réintialise le tableau.

        report.log = fopen(pathLog, "a");
        if (report.log == NULL) {
            printf("impossible d'ouvrir le fichier de log.\n");
            close(sClient);
            //TODO: envoyer un message au client avant de fermer.
            exit(EXIT_FAILURE);
        }
        free(pathLog);

        // On commence à écrire dans le fichier de log.
        strftime(report.time, sizeof(report.time), "%d %B %Y à %X", localtime(&timestamp));
        fprintf(report.log, "**** Log du %s ****\n", report.time);
        fprintf(report.log, "*****************************************\n");

        timestamp = time(NULL);
        report.order = atoi(buff);
        addLog(&report, buff, ORDER_LOG);
        switch (report.order) {
            case 1:
                newReport(sClient, &report);
                fclose(report.log);
                break;
            case 2:
                newSendReport(sClient, &report);
                fclose(report.log);
                break;
            case 3:
                addLog(&report, "fin service sur demande client.", END_LOG);
                printf("Fin service.\n");
                //TODO: envoyer un message pour cloturer le service.
                close(sClient);
                break;
            default:
                printf("order non reconnus. Fin de la socket.\n");
                close(sClient);
                fclose(report.log);
                break;
        }
        exit(1);
    } else {
        // On est dans le père
        if (atoi(buff) == 3) {
            //TODO: envoyer un message pour cloturer le service.
            close(sClient);
            exit(1);
        }
    }


    return 1;
}
//TODO: penser à gerer si la création du fork plante avec une boucle pour réaisser avant d'abandonner.
void waitConnexion(int s) {
    int list_error = 0, com_error = 0;
    int socketAccepted = 0;
    int stop = 0;

    list_error = listen(s, 1);
    if (list_error == -1) {
        perror("listen\n");
        close(s);
        exit(EXIT_FAILURE);
    }
    while (stop != 1) {
        waitpid(-1, NULL, WNOHANG);
        socketAccepted = AcceptConnexion(s);
        com_error = newCommunication(socketAccepted);
        if (com_error == -1) {
            printf("Erreur lors de la création de la communication.\n");
            close(s);
        }
    }

}

void creationSocket() {
    int socketCreat;

    socketCreat = CreeSocketServeur(PORT);
    waitConnexion(socketCreat);
    //   printf("En attente de connexion...\n");
}

int main(){
    creationSocket();
    return 0;
}

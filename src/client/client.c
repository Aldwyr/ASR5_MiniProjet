#include "headerClient.h"


void pseudoUser(char pseudo[25]) {
    int verif = 0;
    printf("Bonjour, veillez vous authentifier\nAttention, taille pseudo limité à 25 caractères\nUne chaine vide n'est pas accepté.\n");

    while (verif == 0) {
        fctErrorPersonal(readLine(pseudo, 25));
        if (pseudo[0] != 0) {
            verif = 1;
        } else {
            printf("Une chaine vide ou supérieur à 25 caractères n'est pas accepté, veille recommencer.\n");
        }
    }
}

void sendToServeur(int sServeur, char *msg, int sizeMsg) {
    int returnWrite = 0;
    returnWrite = write(sServeur, msg, sizeMsg);
    if (returnWrite == -1) {
        printf("error to send msg.\n");
        exit(EXIT_FAILURE);
    }
}

void set_buffer_struct(bufferToSend *report) {
    char tmp[3];
    // Ajout de la taille du pseudo dans la structure.

    if (strlen(report->pseudo) < 10) {
        report->sizePseudo[0] = '0';
        convertIntToChar(tmp, strlen(report->pseudo));
        tmp[1] = 0;
        strcat(report->sizePseudo, tmp);
    } else {
        convertIntToChar(report->sizePseudo, strlen(report->pseudo));
        report->sizePseudo[2] = 0;
    }

    convertIntToChar(report->sizeMsg, strlen(report->msg));
    // Ajout du \0 à la fin de la taille.
    report->sizeMsg[strlen(report->sizeMsg) + 1] = 0;
}


void sendReportToServeur(const int sServeur, bufferToSend *report) {
    //On envoie l'ordre.
    sendToServeur(sServeur, report->order, strlen(report->order));

    // J'envoie la taille du pseudo.
    sendToServeur(sServeur, report->sizePseudo, strlen(report->sizePseudo));

    // j'envoie le pseudo.
    sendToServeur(sServeur, report->pseudo, strlen(report->pseudo));

    // Envoie de la taille du message
    sendToServeur(sServeur, report->sizeMsg, strlen(report->sizeMsg));

    // On envoie en plus un séparateur pour séparer l'entête du reste du message.
    sendToServeur(sServeur, "|", 1);

    // Envoie du message complete.
    sendToServeur(sServeur, report->msg, strlen(report->msg));
}


void sendReport(int s, bufferToSend *report) {
    // 1er temps, envoie de l'ordre voulu.

    strcat(report->order, SEND_RAPPORT);
    report->order[3] = 0;

    set_buffer_struct(report);
    printf("l'order est : %s\n", report->order);
    printf("la taille du pseudo est : %s\n", report->sizePseudo);
    printf("le pseudo est : %s\n", report->pseudo);
    printf("la taille du message est de : %s\n", report->sizeMsg);
    printf("le message = %s\n", report->msg);
    printf("Envoie rapport....\n");

    sendReportToServeur(s, report);

    printf("Fin envoie rapport.\n");

}

//TODO: On peut proposer d'envoyer un fichier au lieu d'écrire un texte.
void newReport() {
    int socketServeur;
    size_t actualMsgTaille = 0;
    char resp = 'n';
    char *host = HOST;
    char *port = PORT;
    char buff[TAILLE_MSG];
    bufferToSend report;
    report.msg = NULL;

    if ((report.msg = malloc(sizeof(char *))) == NULL) {
        printf("erreur lors de l'allocation de malloc. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }

    socketServeur = CreeSocketClient(host, port);
    if (socketServeur == -1) {
        printf("impossible de se connecter au serveur.\nVeillez recommencer\n");
        return;
    }
    // Si on arrive la, c'est que le client est connecté au serveur. On peut donc commencer à envoyer des données.

    // entrer pseudo
    pseudoUser(report.pseudo);
    printf("le pseudo est : %s\n", report.pseudo);

    // Entrer du rapport.
    printf("Merci d'écrire votre rapport :\nUne fois fini, écrivez \"fin\"\n");
    while (resp == 'n') {
        fctErrorPersonal(readLine(buff, TAILLE_MSG));
        if (strcmp(buff, "fin") == 0) {
            do {
                printf("fin saisie du rapport, en êtes vous sûr ? Y/n\n");
                readChar(&resp);
            } while (resp != 'Y' && resp != 'n');

        }
        if (resp == 'n') {
            if (memcmp(report.msg, buff, strlen(buff) + actualMsgTaille) < 0) {
                report.msg = realloc(report.msg, strlen(buff) + actualMsgTaille);
                if (report.msg == NULL) {
                    printf("erreur lors de la saisie.\n");
                    exit(EXIT_FAILURE);
                }
            }
            actualMsgTaille += strlen(buff) + 1;
            strcat(report.msg, "\n");
            strcat(report.msg, buff);
        }
    }
    // Pour une raison que j'ignore, il y a un \n au début du message.
    // Donc je change le pointeur vers la 1er case valide.
    report.msg[0] = report.msg[1];

    sendReport(socketServeur, &report);

    free(report.msg);
    memset(report.order, 0, 4);
    memset(report.sizePseudo, 0, 3);
    memset(report.sizeMsg, 0, 256);
    report.msg = NULL;
    close(socketServeur);
}

void stopServeur() {
    int socketServeur = 0;

    socketServeur = CreeSocketClient(HOST, PORT);
    if (socketServeur == -1) {
        printf("impossible de se connecter au serveur.\nVeillez recommencer\n");
        return;
    }
    sendToServeur(socketServeur, STOP_SERVEUR, 3);
}

void receiveRapport(){
    int socketServeur = 0;
    int readRet = 0;
    char *host = HOST;
    char *port = PORT;
    char pseudo[25];
    FILE *fd = NULL;
    char pathToOpen[30];
    char sizePseudp[3];
    char buff[1] = {'0'};

    pseudoUser(pseudo);
    printf("le pseudo est : %s\n", pseudo);

    socketServeur = CreeSocketClient(host, port);
    if (socketServeur == -1) {
        printf("impossible de se connecter au serveur.\nVeillez recommencer\n");
        return;
    }

    //On envoie l'ordre.
    sendToServeur(socketServeur, MAKE_MRAPPORT, 3);
    // On envoie la taille du pseudo.
    convertIntToChar(sizePseudp, strlen(pseudo));
    sendToServeur(socketServeur, sizePseudp, 2);
    //On envoie le pseudo.
    sendToServeur(socketServeur, pseudo, strlen(pseudo));
    printf("En attente du rapport...\n");


    // On verifie si le pseudo existe.
    if (strcmp(RecoieLigne(socketServeur), "err||") == 0) {
        printf("Le pseudo demandé n'existe pas.\nRecommencé.\n");
    } else {
        strcat(pathToOpen, pseudo);
        strcat(pathToOpen, ".txt");
        // On supprime le fichier s'il existe. l'option "r" de fopen ne crée pas le fichier s'il n'existe pas, c'est comme cela que l'on vérifier l'existance du fichier.
        fd = fopen(pathToOpen, "r");
        if (fd == NULL) {
            remove(pathToOpen);
        }
        fclose(fd);
        fd = fopen(pathToOpen, "w+");
        fprintf(fd, "************** Rapport des entrée de %s **************\n\n", pseudo);
        while (buff[0] != '\0') {
            readRet = read(socketServeur, buff, 1);
            if (readRet == -1) {
                printf("Erreur lors de la lecture");
                close(socketServeur);
                return;
            }
            fprintf(fd, "%c", buff[0]);
        }
        fprintf(fd, "\n***************************************\n**** Fin Rapport ****");
        fclose(fd);
    }
    close(socketServeur);
}

void menu(){
    printf("merci de choisir ce que vous voulez faire :\n");
    printf("1 - Envoie d'un rapport.\n");
    printf("2 - Création d'un rapport.\n");
    printf("3 - demande des log.\n");
    printf("4 - arrêter le serveur.\n");
    printf("5 - sortir.\n");
}

void (* menuChosen())(){
    char text[10];
    int value = 0;
    while (value == 0) {

        readLine(text, 2);
        value = strtol(text, NULL, 10);
        switch (value) {
            case 1:
                return newReport;
                break;
            case 2:
                return receiveRapport;
                break;
            case 4:
                return stopServeur;
                break;
            case 5:
                printf("fermuture du programme.\nMerci est bonne journée.\n");
                exit(1);
                break;
            default:
                value = 0;
                printf("Erreur lors du choix. merci de choisir une valeur dans les choix proposé.\n");
                menu();
                break;
        }
    }
    return 0;
}


int main() {
    void (*ptrFunction)(void);
    while (1) {
        printf("bienvenu au client.\n\n");
        menu();
        ptrFunction = menuChosen();
        (*ptrFunction)();
    }

    return 0;
}

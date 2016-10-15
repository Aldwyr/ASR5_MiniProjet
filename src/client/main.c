#include <stdlib.h>
#include <stdio.h>


#include "creatConnexion.h"
#include "../commun/socklib.h"

#define VERSION_LOGICIEL 1
#define SEND_RAPPORT 001
#define MAKE_MRAPPORT 002
#define TAILLE_MSG 32768  // 2^15 octet pour écrire, c'est pas mal, non ? :D


void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int readChar(char *c) {
    if ((*c = fgetc(stdin)) != NULL) {
        viderBuffer();
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}

int readLine(char *str, const int size) {
    char *findCharEnter = NULL;

    if (fgets(str, size, stdin) != NULL) {
        findCharEnter = strchr(str, '\n');
        if (findCharEnter != NULL) {
//            *findCharEnter = '\0';
        } else
            viderBuffer();
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}

//TODO: On peut proposer d'envoyer un fichier au lieu d'écrire un texte.
void sendRapport(){
    int socketServeur;
    long int order = SEND_RAPPORT;
    size_t actualMsgTaille = 0;
    char resp = 'n';
    char *host = "localhost";
    char *port = "8080";
    char buff[TAILLE_MSG];
    char *finalRapport = malloc(sizeof(char));
    //   printf("je suis la fonction pour envoyer un rapport.\n");

/*
    socketServeur = CreeSocketClient(host, port);
    if (socketServeur == -1) {
        return;
    }
*/
    // Si on arrive la, c'est que le client est connecté au serveur. On peut donc commencer à envoyer des données.
    printf("Merci d'écrire votre rapport :\nUne fois fini, appuyer 2 fois de suite sur la touche entrée\n");
    while (resp == 'n') {
        readLine(buff, TAILLE_MSG);
        if (strcmp(buff, "\n") == 0) {
            do {
                printf("fin saisie du rapport, en êtes vous sûr ? Y/n\n");
                readChar(&resp);
            } while (resp != 'Y' && resp != 'n');

        }
        if (resp == 'n') {
            if (memcmp(finalRapport, buff, strlen(buff) + actualMsgTaille) < 0) {
                finalRapport = realloc(finalRapport, strlen(buff) + actualMsgTaille);
            }
            actualMsgTaille += strlen(buff) + 1;
            strcat(finalRapport, "\n");
            strcat(finalRapport, buff);
        }
//    printf("%s", finalRapport);

    }
    printf("%s", finalRapport);
}

void receiveRapport(){
    printf("Je suis la fonction pour donner le rapport mensuel.\n");
}

void menu(){
    printf("merci de choisir ce que vous voulez faire :\n");
    printf("1 - Envoie d'un rapport.\n");
    printf("2 - Créeation d'un rapport mensuel.\n");
    printf("3 - sortir.\n");
}

void (* menuChosen())(){
    char text[10];
    int value = 0;
    while (value == 0) {

        readLine(text, 2);
        value = strtol(text, NULL, 10);
        switch (value) {
            case 1:
                return sendRapport;
                break;
            case 2:
                return receiveRapport;
                break;
            case 3:
                printf("fermuture du programme.\nMerci est bonne journée.\n");
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
    
    printf("bienvenu au client %d\n", VERSION_LOGICIEL);
    menu();
    ptrFunction = menuChosen();
    (*ptrFunction)();
    
    
    return 0;
}

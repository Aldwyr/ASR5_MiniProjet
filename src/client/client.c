#include <stdlib.h>
#include <stdio.h>

#include "creatConnexion.h"
#include "../commun/socklib.h"
#include "../commun/usualFct.h"
#include "headerClient.h"

#define SEND_RAPPORT 1
#define MAKE_MRAPPORT 2
#define STOP_SERVEUR 3
#define TAILLE_MSG 32768  // 2^15 octet pour écrire, c'est pas mal, non ? :D


//TODO:faire la fonction au serveur qui gère l'authentification salement Sans sécurité. :D
void pseudoUser(char pseudo[25]) {
    printf("Bonjour, veillez vous authentifier\n Attention, taille pseudo limité à 25 caractère\n");
    fctErrorPersonal(readLine(pseudo, 25));
}

void kingdomOfFreedom(void **newFreeGuys) {
    free(*newFreeGuys);
    *newFreeGuys = NULL;
}

//TODO: free completeBuffer
void set_buffer_head(char **completBuffer, const char order, const char pseudo[]) {
    *completBuffer = malloc(sizeof(char));
    size_t sizePseudo = strlen(pseudo);

    *completBuffer[0] = order;
    // On veut : connaitre la taille des objet à mettre dans le tableau.
    // CAD, la taille en octect du pseudo, la taille du pseudo
    memcpy(*completBuffer, &sizePseudo, sizeof(size_t));
    memcpy(*completBuffer, pseudo, sizeof(char) + strlen(pseudo) + 1);

}

void set_buffer_body(char **completBuffer, const char *msg) {
    size_t sizeMsg = strlen(msg);

    memcpy(*completBuffer, &sizeMsg, sizeof(size_t));
    memcpy(*completBuffer, msg, sizeof(char) + strlen(msg));
}

void sendReport(int s, char *report, char *pseudo) {
    // 1er temps, envoie de l'ordre voulu.
    char *completBuffer = NULL;
    char order = SEND_RAPPORT;

    set_buffer_head(&completBuffer, order, pseudo);
    set_buffer_body(&completBuffer, report);


    kingdomOfFreedom(&completBuffer);
}

//TODO: On peut proposer d'envoyer un fichier au lieu d'écrire un texte.
//TODO: On peut prendre en compte le ctrl+D pour faire le EOF. :)
void newReport() {
    int socketServeur;
    size_t actualMsgTaille = 0;
    char resp = 'n';
    char *host = "localhost";
    char *port = "8080";
    char buff[TAILLE_MSG];
    char *finalRapport = NULL;
    char pseudo[25];

    if ((finalRapport = malloc(sizeof(char *))) == NULL) {
        printf("erreur lors de l'allocation de malloc. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
/*
    socketServeur = CreeSocketClient(host, port);
    if (socketServeur == -1) {
        printf ("impossible de se connecter au serveur.\n Veillez recommencer\n");
        return;
    }
*/
    // Si on arrive la, c'est que le client est connecté au serveur. On peut donc commencer à envoyer des données.

    // entrer pseudo
    pseudoUser(pseudo);
    printf("le pseudo est : %s\n", pseudo);

    //TODO: penser à vérifier donner la possibilier à l'utilisateur de recommencer.
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
            if (memcmp(finalRapport, buff, strlen(buff) + actualMsgTaille) < 0) {
                finalRapport = realloc(finalRapport, strlen(buff) + actualMsgTaille);
            }
            actualMsgTaille += strlen(buff) + 1;
            strcat(finalRapport, "\n");
            strcat(finalRapport, buff);
        }
    }
    sendReport(socketServeur, finalRapport, pseudo);
    kingdomOfFreedom((void *) &finalRapport);
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
                return newReport;
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
    printf("bienvenu au client.\n\n");
    menu();
    ptrFunction = menuChosen();
    (*ptrFunction)();
    
    
    return 0;
}

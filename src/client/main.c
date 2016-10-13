#include <stdlib.h>
#include <stdio.h>

#include "creatConnexion.h"
#include "../commun/socklib.h"

#define VERSION_LOGICIEL 1
#define SEND_RAPPORT 001
#define MAKE_MRAPPORT 002


void sendRapport(){
    int socketServeur;
    char *host = "localhost";
    char *port = "8080";
    printf("je suis la fonction pour envoyer un rapport.\n");


    socketServeur = CreeSocketClient(host, port);
    // Si on arrive la, c'est que le client est connecté au serveur. On peut donc commencer à envoyer des données.
    EnvoieMessage(socketServeur, "Ceci est un test : %d", 42);

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
    char text[10] = {0};
    int value = 0;
    while (value == 0) {
        
        fgets(text, 2, stdin);
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

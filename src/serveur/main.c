#include <stdio.h>
#include <sys/socket.h>
#include "../commun/socklib.h"

#define PORT "8080"
#define TAILL_BUFF 256

int recupOrder(const int sClient) {
//    int nbRead = 0;
    //   char buff[TAILL_BUFF];

    return 0;
}

int newCommunication(const int sClient) {
    int resFork = 0;

    resFork = fork();
    if (resFork == -1){
        perror("Fork\n");
        return -1;
    }
    if (resFork == 0) {
        // On  est dans le fils;
        recupOrder(sClient);
    } else {
        // On est dans le père

    }
}
//TODO: penser à gerer si la création du fork plante avec une boucle pour réaisser avant d'abandonner.
void waitConnexion(int s) {
    int list_error = 0, com_error = 0;
    int socketAccepted = 0;

    list_error = listen(s, 1);
    if (list_error == -1) {
        perror("listen\n");
        close(s);
        exit(EXIT_FAILURE);
    }
    socketAccepted = AcceptConnexion(s);
    com_error = newCommunication(socketAccepted);

}

void creationSocket() {
    int socketCreat;

    socketCreat = CreeSocketServeur(PORT);
    waitConnexion(socketCreat);
    printf("En attente de connexion...\n");
}

int main(){
    creationSocket();
    return 0;
}

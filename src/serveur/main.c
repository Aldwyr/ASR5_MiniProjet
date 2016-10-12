#include <stdio.h>
#include <sys/socket.h>
#include "../commun/socklib.h"


void waitConnexion(int s) {
    int list_error = 0;
    int socketAccepted = 0;

    list_error = listen(s, 1);
    if (list_error == -1) {
        perror("listen\n");
        close(s);
        exit(EXIT_FAILURE);
    }
    socketAccepted = AcceptConnexion(s);
    printf("j'ai reçu une demande de connexion");
}

void creationSocket() {
    int socketCreat;

    socketCreat = CreeSocketServeur("8080");
    waitConnexion(socketCreat);
    printf("la socket est crée!!:D\n");
}

int main(){
    creationSocket();
    return 0;
}

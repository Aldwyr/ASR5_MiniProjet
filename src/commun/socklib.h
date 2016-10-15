#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//#include <error.h>
#include <string.h>
#include <stdio.h>

/* Une partie nécessaire pour utiliser les sockets sous linux et windows */
#if defined (WIN32)
#include <winsock2.h>
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

//#define MSG_NOSIGNAL -1 //TODO: celle-l� devrait �tre d�finie dans <sys/socket.h> ???

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
/**
 * @file socklib.h
 *
 * @author Rico Fabien <fabien.rico@univ-lyon1.fr>
 *
 * @brief Contient les prototypes des fonctioncs de socklib.c
 */

/**
 * @defgroup sockLib LibSock
 * @brief Les fonctions utiles pour la communications entre le client et le serveurs.
 *  @{
 */

/**
 * @brief Cree une socket d'attente pour le serveur sur le port port
 * @param port : le port utilisé
 * @return la socket d'attente ou -1 en cas d'erreur
 *
 * en cas d'erreur, un message explicatif est affich� sur la sortie d'erreur 
 * standart
 */
int CreeSocketServeur(const char *port);

int CreeSocketClient(const char *serveur, const char *port);

///retourne la socket accept�e
int AcceptConnexion(int s);

/**
 * Lire les donn�es sur une socket et les �crire automatiquement dans un descripteur de fichier
 * Cette fonction stoppe la lecture lorsque la soket est ferm�e.
 * @param sock : la socket d'o� proviennent les donn�es, cela fonctionne aussi 
 *               si sock est un file descriptor quelconque
 * @param fd : le descripteur de fichier sur lesquel enregistrer les donn�es
 * @return : si cela a fonctionn� le nombre d'octets lus, sinon -1
 */
int RecoieEtSauveDonnees(int fd, int sock);

/**
 * Lire les donn�es sur une socket (uniquement j'utilise recv) jusqu'� arriv� � un retour chariot '\n' la donn�e est stok�e dans un tableau dont la taille est adapt� pour cela).
 * @param sock : la socket de lecture
 * @return la chaine lue � lib�rer par free
 */
char *RecoieLigne(int sock);

/** 
 * envoie le message format� sur la socket s (comme un printf)
 * @param s : la socket sur laquel ecrire le message
 * @param format : le format du message (comme pour printf)
 * @param  ...:
 * @return le nombre d'octet �crit ou -1 s'il y a eu un probl�me
 */
int EnvoieMessage(int s, char *format, ...);

/**
 * Regarde s'il y a qqchose � lire sur une socket
 * @param s : la socket
 * @return * -1 s'il y a une erreur
 *         * -2 s'il n'y a rien � lire
 *         * 0 si la socket est ferm�e
 *         * 1 s'il y a qqchose � lire
 */
int TestLecture(int s);
/** }@*/
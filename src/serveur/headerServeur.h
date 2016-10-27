//
// Created by Grégory GUEUX on 26/10/2016.
//

#ifndef CLIENT_SERVEURHEADER_H_H
#define CLIENT_SERVEURHEADER_H_H

#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/wait.h>
#include "../commun/socklib.h"

#define PORT "8080"
#define TAILL_BUFF 256

#define ORDER_LOG "order: "
#define PSEUDO_LOG "pseudo: "
#define END_LOG "end service: "
#define INF_LOG "info: "
#define ERR_LOG "Error: "

/**
 * @file serveurHeader.h
 *
 * @author Gueux Grégory <gregory.gueux@etu.univ-lyon1.fr>
 *
 * @brief Contient les prototypes des fonctions de serveur.c
 */

/**
 * @defgroup serveur Serveur
 *
 * @brief Les fonctions principals du serveur.
 * @{
 */

/**
 * @struct sBufferToSend headerClient.h
 * @brief Représente un rapport complet avec le header à envoyer.
 */

typedef struct sbufferToReceive {
    /// l'ordre qui est envoyé.
    int order;
    /// La taille du pseudo.
    int sizePseudo;
    /// Le pseudo.
    char pseudo[25];
    /// La taille du message.
    int sizeMsg;
    /// le message.
    char *msg;
    /// Le temps pour les log.
    char time[256];
    ///le fichier de log.
    FILE *log;
} bufferToReceive;

/**
 * @brief récupère l'order du client.
 * @param sClient La socket du client.
 * @param buff Le buffer qui contiendra l'order.
 */
void recupOrder(const int sClient, char *buff);

/**
 * @brief Initialise une nouvelle communication entre le client et le serveur.
 * @note On procéde a un fork pour permettre au serveur de continuer à attendre des communications.
 * @param sClient La sockets du client.
 * @return
 */
int newCommunication(int sClient);

/**
 * @brief Permet de mettre le processus sur écoute et d'attendre une connexion entrante.
 * @param s La socket qui est disponible sur un port. donnée.
 */
void waitConnexion(int s);

/**
 * @brief Crée un socket pour le serveur.
 */
void creationSocket();

/**
 * @brief récupère et enregistre le rapport qu'a envoyé le client.
 * @param sClient La socket du client.
 * @param report Le rapport du client.
 */
void newReport(int sClient, bufferToReceive *report);

/**
 * @brief envoie tout les rapports du clients dans un seul fichier.
 * @param sClient La socket du client.
 * @param report Le rapport du client.
 */
void newSendReport(int sClient, bufferToReceive *report);

/**
 * @brief Renvoie la date Local + l'heure local.
 * @param newDateAndTime La chaine de caractère où stocker la date.
 * @param time La date réinitialiser.
 */
void recupTime(char *newDateAndTime, time_t time);

/**
 * @brief Permet d'ajouter un entrée dans le fichier de log de la sessions.
 *
 * @param report La structure qui contient le fd du fichier de log.
 * @param msg le message à mettre dans le fichier de log.
 * @param prefixe Le préfixe à mettre avant le message.
 */
void addLog(bufferToReceive *report, const char *msg, const char *prefixe);

/**
 * @brief récupère les informations qui sont forcément envoyer.
 * @param sClient La socket du client.
 * @param report La structure à remplir.
 */
void recupInformation(int sClient, bufferToReceive *report);
/** }@ */
#endif //CLIENT_SERVEURHEADER_H_H

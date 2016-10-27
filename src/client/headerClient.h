//
// Created by Grégory GUEUX on 18/10/2016.
//

#ifndef CLIENT_HEADERCLIENT_H
#define CLIENT_HEADERCLIENT_H

#include <stdlib.h>
#include <stdio.h>

#include "creatConnexion.h"
#include "../commun/socklib.h"
#include "../commun/usualFct.h"

#define SEND_RAPPORT "001"
#define MAKE_MRAPPORT "002"
#define STOP_SERVEUR "003"


#define HOST "localhost"
#define PORT "8080"
#define TAILLE_MSG 32768  // 2^15 octet pour écrire, c'est pas mal, non ? :D

/**
 * @file headerClient.h
 *
 * @author Grégory Gueux <gregory.gueux@etu.univ-lyon1.fr>
 *
 * @brief Contient les prototypes des fonctions de main.c
 */

/**
 * @defgroup client  Client
 *
 * @brief Les fonctions principaux du client
 * @{
 */

/**
 * @struct sBufferToSend headerClient.h
 * @brief Représente un rapport complet avec le header à envoyer.
 */

typedef struct sbufferToSend {
    /// l'ordre qui est envoyé.
    char order[4];
    /// La taille du pseudo.
    char sizePseudo[3];
    /// Le pseudo.
    char pseudo[25];
    /// La taille du message. Qui est limité à 10^256 caractère maxi.
    char sizeMsg[256];
    /// le message.
    char *msg;
} bufferToSend;


/**
 * @brief La fonction permet de selection une fonction selon le choix du client.
 *
 * @return Le pointeur de la fonction choisie par le client.
 */
void (*menuChosen())();

/// affichie le menu des choix à l'écran.
void menu();

//TODO: définir le nombre de rapport à retourner.
/// permet de recevoir le rapport mensuelle.
void receiveRapport();

/// Permet d'écrire ou d'envoyer un nouveau rapport.
void newReport();

/**
 * @brief envoie le rapport au seveur.
 *
 * @param socketServeur La socket du serveur.
 * @param report La structure @ref
 */
void sendReport(int socketServeur, bufferToSend *report);

/**
 * @brief parce que tout le monde aspire à la liberté, même des octets veulent pouvoir bénéficier de cela.
 *
 * @param newFreeGuys Un candidiat pour rejoindre le royaume.
 */
void kingdomOfFreedom(void **newFreeGuys);

/**
 * @brief Permet de récupérer le pseudo de l'utilisateur sur l'entrée standard.
 * @param pseudo
 */
void pseudoUser(char pseudo[25]);

/**
 * @brief Complète la structure du rapport. C'est-à-dire la taille du pseudo et la taile du message.
 *
 * @param report Le rapport complet.
 */
void set_buffer_struct(bufferToSend *report);

/**
 * @brief Envoie l'ordre au client.
 * @param sServeur La socket qui est connecté au client.
 * @param report La structure du rapport.
 */
void sendReportToServeur(const int sServeur, bufferToSend *report);

/**
 * @brief Arrête le serveur distant.
 */
void stopServeur();

/**
 * @brief envoie quelque chose sur la socket donnée
 * @param sServeur La socket du serveur
 * @param msg Le message à envoyer
 * @param sizeMsg La taille du message à envoyer.
 */
void sendToServeur(int sServeur, char *msg, int sizeMsg);

/** }@*/

#endif //CLIENT_HEADERCLIENT_H

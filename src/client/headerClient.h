//
// Created by Grégory GUEUX on 18/10/2016.
//

#ifndef CLIENT_HEADERCLIENT_H
#define CLIENT_HEADERCLIENT_H

/**
 * @file headerClient.h
 *
 * @author Grégory Gueux <gregory.gueux@etu.univ-lyon1.fr>
 *
 * @brief Contient les prototypes des fonctions de main.c
 */

/**
 * @defgroup main  Client
 *
 * @brief Les fonctions principaux du client
 * @{
 */
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
 * @param report Est le rapport écrit soit par le client, soit récupèrer dans un fichier.
 * @param pseudo Est le pseudo de l'utilisateur.
 */
void sendReport(int socketServeur, char *report, char *pseudo);

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
 * @brief Initialise la tête du buffer à envoyer au server avec, dans l'order : le Buffer, la taille du pseudo, le pseudo.
 *
 *
 * @note Le message sera ajouté plus tard. Selon le type d'ordre donnée.
 * @param completBuffer Le buffer que l'on remplira.
 * @param order L'ordre à envoyer au serveur.
 * @param pseudo Le pseudo de l'utilisateur.
 */
void set_buffer_head(char **completBuffer, const char order, const char pseudo[]);

/**
 * @brief Ajoute la taille du message et le corps du rapport au buffer.
 * @param completBuffer Le buffer complet à envoyer
 * @param msg le rapport de l'utilisateur.
 */
void set_buffer_body(char **completBuffer, const char *msg);
/** }@*/
#endif //CLIENT_HEADERCLIENT_H

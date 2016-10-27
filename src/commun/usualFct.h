//
// Created by Grégory GUEUX on 18/10/2016.
//

#ifndef CLIENT_USUALFCT_H
#define CLIENT_USUALFCT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// =============================================================================
// Définitions pour doxygen

/**
 * @file usualFct.h
 *
 * @author Grégory GUEUX <gregory.gueux@etu.univ-lyon1.fr>
 *
 * @brief Contient les prototypes des fonctions de usualFct.c.
 */

/**
 * @defgroup usualFct    UsualFonction
 *
 * @brief Les fonctions utile pour le client et le serveur.
 * @{
 */

/**
 * @brief evalue la fonction si elle ne retourne pas une erreur.
 *
 * @warning si une erreur est détecté, le programme est quittée sans fermer le serveur.
 * @param value la valeur du param retourné.
 */
void fctErrorPersonal(int value);

/**
 * @brief lit une ligne sur l'entrée standard et vérifier la fonction fgets.
 * @param str le buffer où sera écrit la chaine de caractère.
 * @param size la taille à lire.
 * @return 0 si fgets n'a pas fonctionné.
 * @return 1 si tout s'est bien passsé.
 */
int readLine(char *str, const int size);

/**
 * @brief lit un caractère sur l'entrée standard et vérifier la fonction fgetc.
 * @param c Un pointeur sur un char
 * @return 0 si fgetc a rencontré une erreur.
 * @return 1 si tout s'est bien passé.
 */
int readChar(char *c);

/// vide le buffer de la sortie standard.
void viderBuffer();

/**
 * @brief Convertie un entier int en char *
 * @param tab le tableau ou sera stocker le char*
 * @param intergerToConvert L'entier à convertir.
 */
void convertIntToChar(char *tab, const size_t intergerToConvert);
/** }@*/

#endif //CLIENT_USUALFCT_H

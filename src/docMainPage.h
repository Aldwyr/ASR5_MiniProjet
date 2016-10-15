//
// Created by Grégory GUEUX on 18/10/2016.
//
/**
 * @mainpage projet creation de protocole
 *
 * @author Gregory GUEUX      <gregory.gueux@etu.univ-lyon1.fr>
 *
 * @brief Vous trouverez ici toute la documentation relative au projet de création d'un protocole client serveur.
 *
 *
 * @section sec1 le projet
 *
 *      @subsection sub11 En résumé
 *      le but du projet est de créer un protocole de communication entre deux processus qui n'ont pas forcément de lien
 *      entre eux (via un fork par exemple). Cela, grâce à l'utilisation des sockets.
 *
 *      @subsection sub12 Client
 *      Le client est le programme qui doit se trouver sur la machine de l'utilsateur. Il permet d'envoyer un rapport au
 *      @ref Serveur ou de demander que ce dernier fasse un rapport completer sur les derniers rapport reçu.
 *
 *      @subsection sub13 Serveur
 *      Le serveur doit être présent soit sur une machine distante soit sur la machine en local.
 *      Il s'occupe de récupèrer les rapports des clients et de faire
 *      un rapport sur ces derniers sur demande du client.
 *      @warning il doit être lancé  AVANT le @ref client.
*/
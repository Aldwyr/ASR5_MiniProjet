//
//  creatConnexion.h
//  
//
//  Created by Grégory GUEUX on 04/10/2016.
//
//

#ifndef __CREAT_CONNEXION_h
#define __CREAT_CONNEXION_h

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
//#include <error.h>
#include <string.h>
#include <stdio.h>

//Une partie n√©cessaire pour utiliser les sockets sous linux et windows
/*
#if defined (WIN32)
#include <winsock2.h>
#elif defined (linux)
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int creationSocketClient(const char host, const int port);


#endif /* creatConnexion_h */

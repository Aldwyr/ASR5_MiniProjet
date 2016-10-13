#!/bin/bash
# Creation de la libsock.a
if [ ! -f "lib/libsock.a" ]
then
	echo "creation de la libock.a"
	gcc -c src/commun/socklib.c -o src/commun/socklib.o
	ar -rv lib/libsock.a src/commun/socklib.o
else
	echo "la lib est deja presente."
fi
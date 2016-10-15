#!/bin/bash
# Creation de la libsock.a
if [ ! -f "lib/libsock.a" ]
then
	echo "creation de la libock.a"
	gcc -c src/commun/socklib.c -o src/commun/socklib.o
	ar -rv lib/libsock.a src/commun/socklib.o
else
	echo "la libsock.A est deja presente."
fi

if [ ! -f "lib/libUsualFonction.a" ]
then
    echo "création de la libUsualFonction.a"
    gcc -c src/commun/usualFct.c -o src/commun/usualFct.o
    ar -rv lib/libUsualFonction.a src/commun/usualFct.o
else
    echo "la libUsualFonction.a est déjà présente."
fi

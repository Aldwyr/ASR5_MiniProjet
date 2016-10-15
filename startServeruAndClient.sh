#!/bin/bash
# Fichier "startServeur"

sh creationLib.sh

make re
make clean
./bin/serveur/serveur&
sleep 1
clear
./bin/client/client

#!/bin/bash
# Fichier "startServeur"

sh creationLib.sh

make re
./bin/serveur/serveur&
sleep 1
./bin/client/client

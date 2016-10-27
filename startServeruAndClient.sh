#!/bin/bash
# Fichier "startServeurAndClient"

sh creationLib.sh

make re
make clean
cd bin/serveur/
sh startServeur.sh
sleep 1
cd ../client/
clear
sh starClient.sh

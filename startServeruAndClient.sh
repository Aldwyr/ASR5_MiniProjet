#!/bin/bash
# Fichier "startServeur"

make re
./bin/serveur/serveur&
sleep 1
./bin/client/client

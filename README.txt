**** PROJET ASR5 - GUEUX GREGORY - 11407831****
***********************************************

pour lancer :
1) lancer un terminal.
2) aller à la racine du programme.
3) faire un « make » ou « make re »
	3.1) Si les libs ne sont pas présent dans le dossier lib/, vous pouvez les 
		recompiler avec le script sh creationLib.sh.
4) lancer les programme.
	4.1.1) Lancer le serveur directement dans sont dossier : « bin/serveur/« puis lancer « ./serveur& » (Obligatoire, sinon, il ne pourra pas écrire dans les dossiers qui sont dans bin/serveur/)
	4.1.2)faite de même pour l’exécutable du client dans « bin/client » puis lancer « ./client » (pas obligatoire, il mettra les rapport la où vous avez lancer l’exécutable)


3.bis) Soit lancer le script sh « startServeruAndClient.sh » qui s’occupera de tout. en relançant la compilation des lib statiques (si non présente) et des exécutable.

Vous pouvez aussi regarder la documentation disponible dans « doc/html/index.html » pour savoir ce que font les différentes fonctions utilisé. 

Vous n’êtes pas obligé de killer le serveur via le terminal. Le client peut le faire via un choix de menu.

Attention: cela ne marche que en local. Le port 8080 sera utilisé pour cela.
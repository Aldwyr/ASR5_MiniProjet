//
// Created by Grégory GUEUX on 18/10/2016.
//

#include "usualFct.h"

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int readChar(char *c) {
    if ((*c = fgetc(stdin)) != EOF) {
        viderBuffer();
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}


int readLine(char *str, const int size) {
    char *findEnterChar = NULL;

    if (fgets(str, size, stdin) != NULL) {
        findEnterChar = strchr(str, '\n');
        if (findEnterChar != NULL) {
            *findEnterChar = '\0';
        } else {
            viderBuffer();
        }
        return 1;
    } else {
        viderBuffer();
        perror("fgets");
        return 0;
    }
}

void fctErrorPersonal(int value) {
    if (value == 0) {
        printf("impossible de lire la ligne, merci de recommencer.\n");
        exit(EXIT_FAILURE);
    }
}

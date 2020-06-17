#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include "fileTabChar.h"

char *fileToChar(char *path) {

    FILE *fich = NULL;
    int sz = 0;
    fich = fopen(path, "r");
    fseek(fich, 0L, SEEK_END);
    sz = ftell(fich);
    char *tab = malloc(sz * sizeof(char));
    fseek(fich, 0, SEEK_SET);

    if (fich != NULL) {
        if (tab) {
            fread(tab, 1, sz, fich);
        }
        fclose(fich);
        return tab;

    }
}

int fileSize(char * path){
    FILE *fich = NULL;
    int sz = 0;
    fich = fopen(path, "r");
    fseek(fich, 0L, SEEK_END);
    sz = ftell(fich);
    fclose(fich);
    return sz;
}
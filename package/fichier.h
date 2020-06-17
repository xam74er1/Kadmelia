//
// Created by vincent on 13/06/2020.
//

#ifndef GROUPE7_FICHIER_H
#define GROUPE7_FICHIER_H

#include <stdint.h>
#include "node.h"

typedef struct Fichier{
    uint32_t idnode[5];
    uint32_t hashnom[5];
    uint32_t hashfichier[5];
    int taille;
    char nom[255];
}Fichier;

void inFichier(Fichier * fichier, Node *proprio ,uint32_t hashnom[5],uint32_t hashfichier[5],int taille,char nom[255]);

#endif //GROUPE7_FICHIER_H

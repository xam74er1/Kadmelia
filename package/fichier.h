//
// Created by vincent on 13/06/2020.
//

#ifndef GROUPE7_FICHIER_H
#define GROUPE7_FICHIER_H

typedef struct Fichier{
    uint32_t idnode[5];
    uint32_t nom[5];
    uint32_t fichier[5];
    char nom[];
    int taille;
}Fichier;

#endif //GROUPE7_FICHIER_H

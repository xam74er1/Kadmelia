//
// Created by vincent on 13/06/2020.
//

#include "fichier.h"
void inFichier(Fichier * fichier, Node *proprio ,uint32_t hashnom[5],uint32_t hashfichier[5],int taille,char nom[255]){
    for(int i = 0;i<IDLENGTH_INT;i++){
        fichier->idnode[i] = proprio->id[i];
    }

    for(int i = 0;i<IDLENGTH_INT;i++){
        fichier->hashnom[i] = hashnom[i];
    }

    for(int i = 0;i<IDLENGTH_INT;i++){
        fichier->hashfichier[i] = hashfichier[i];
    }

    fichier->taille = taille;
    strcpy(fichier->taille,nom);

}
//
// Created by vincent on 12/06/2020.
//

#ifndef GROUPE7_BDD_H
#define GROUPE7_BDD_H

#include "../lib/sqlite3.h"
#include <inttypes.h>
#include "node.h"
#include "fichier.h"

int createDatabase();

void getNode(uint32_t id[5], Node *node);
void setNode(Node *node);

void SetFile(Fichier *fichier);
void findNode(uint32_t hash[5], Node * node);
void SetFile(Node * from,uint32_t idnode[5], uint32_t hashword[5], uint32_t hashfile[5],char nom[], int taille);
void findNode(Node * from,uint32_t hash[5], Node * node);

void setlocalfile(char nom[], char chemin[]);
char* getfilepath(char nom[]);
void getfichier(uint32_t hashnom[5], Fichier *fichier, Node *node);
void setlocalfile(Node * from,char nom[], char chemin[]);

#endif //GROUPE7_BDD_H

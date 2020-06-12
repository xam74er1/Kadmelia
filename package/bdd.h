//
// Created by vincent on 12/06/2020.
//

#ifndef GROUPE7_BDD_H
#define GROUPE7_BDD_H

#include "../lib/sqlite3.h"
#include <inttypes.h>
#include "node.h"

int createDatabase (Node * from) ;

void getNode(Node * from,uint32_t id[5], Node *node);
void setNode(Node * from,Node *node);

void SetFile(Node * from,uint32_t idnode[5], uint32_t hashword[5], uint32_t hashfile[5],char nom[], int taille);
void findNode(Node * from,uint32_t hash[5], Node * node);

void setlocalfile(Node * from,char nom[], char chemin[]);

#endif //GROUPE7_BDD_H

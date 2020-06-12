//
// Created by vincent on 12/06/2020.
//

#ifndef GROUPE7_BDD_H
#define GROUPE7_BDD_H

int createDatabase();

void getNode(uint32_t id[5], Node *node);
void setNode(Node *node);

void SetFile(uint32_t idnode[5], uint32_t hashword[5], uint32_t hashfile[5],char nom[], int taille);
void findNode(uint32_t hash[5], Node * node);

#endif //GROUPE7_BDD_H

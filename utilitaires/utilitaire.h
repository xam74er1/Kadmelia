//
// Created by xam74 on 18/04/2020.
//

#ifndef GROUPE7_UTILITAIRE_H
#define GROUPE7_UTILITAIRE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../package/node.h"

char* concat(char *s1, char *s2);

int xordistance(int a , int b );


int GreatOrEqueals(int * original,int * compare,int length);
int * xordistanceTableau(int * srcA,int * srcB,int length);

//Void est une node
void printNode(struct Node * test);

void printBukket(struct Node * node);

#endif //GROUPE7_UTILITAIRE_H
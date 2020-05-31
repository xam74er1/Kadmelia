//
// Created by root on 5/31/20.
//

#ifndef GROUPE7_BUKKET_H
#define GROUPE7_BUKKET_H

#define K_BUCKET 1
#include "node.h"

typedef struct Bucket{
    struct Node * bukket[K_BUCKET];
            int nbVoisin ;
}Bucket;

void iniBucket(Bucket * bucket); //Initilse un bukket
void * add_node_to_bukket(struct Node * node,Bucket * bucket);//Ajoute une node au bukket

Bucket * find_Bucket(struct Node * from,struct Node * toPlace);//Trouve le bukket a dequoite pour ajoute toPlace

#endif //GROUPE7_BUKKET_H

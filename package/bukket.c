//
// Created by root on 5/31/20.
//

#include <stdbool.h>
#include "bukket.h"
//Initilse un bukket
void iniBucket(Bucket * bucket){
bucket->nbVoisin = 0;
}

Bucket * find_Bucket(Node * from,Node * toPlace){
char isPosioned = false;

int tabPos = 0;
/*
 * Principe genrale de l'ago :
 * Trouve dans quelle bukket positione ma nouvelle node
 *
 * Pour cela on place des que un bit differe
 * On dois donc contine jusca ce que que un bit sois diffrent
 *
 * Pour cela :
 * On commence par trouve la diffrence avec un xor
 * Puis on applique un mask de bit pour selectione (ex : 0100 and 1000 = 0000)
 *
 * Si on ne troue pas on decle le mask de bit de 1 crand vers la droite (ex avant 1000 , apres 01000) , cela ce fait avec l'operation >>1
 *
 */
for(int i = 0;i<IDLENGTH_INT&&!isPosioned;i++){

    int xor = from->id[i]^ toPlace->id[i];//On fait un xor des 2
    int mask = 1<<sizeof(uint32_t);//on realise un masque pour selectione les bit 1 a 1, ici positone a 2^32 ou 100..000 (avec 32 bit)
    for(int j = 0;j<sizeof(uint32_t)&&!isPosioned;j++){
        if(xor&&mask){//Si le bit egale a 1 alors il y a une diffrence et on a trouve
            isPosioned = true;
        }else{
            tabPos++;
        }
mask = mask >>1;//on decla le mask de 1
    }
}

if(tabPos<NBBUCKET){
    return from->listBucket[tabPos];
}
//Si ID est la meme que moi alors je retourne 0;
return 0;
}

//ajoute une node au bukket
void * add_node_to_bukket(struct Node * node,Bucket * bucket){

    Node *backup = bucket->bukket[K_BUCKET-1];
//On decale tout de 1
    void * source = (void *) bucket->bukket;
    void * destination = (void *) ( bucket->bukket+ 1 );
    size_t size = K_BUCKET * sizeof( Node * );
    memmove( destination, source, size );

    //on ajoute lelment au debut
    bucket->bukket[0] = node;

    //Pas sur de cette setion a voir si elle pose des pbr
    if(bucket->nbVoisin>K_BUCKET){
        free(backup);
    }


}
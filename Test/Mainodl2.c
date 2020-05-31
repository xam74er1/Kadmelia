//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include "string.h"
#include "kademiliaTest.h"
/*
 * Sert a cree plein de node
 */
void peupleNode(Node * tab[],int nb){
    for (int i = 0; i < nb; ++i) {
        Node n ;
        ini(&n);
        tab[i] = &n;
    }
}
/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main() {
    printf("start 2\n");

    srand(time(NULL));   // Initialization, du random

    Node node1,node2;//declration de 2 node


    int tabIndex = 1;

    ////////////////// NOde 1 ////////////////
    ini(&node1);//initilisation de la node 1
    setNodeIdSimple(&node1,10);
    createFifo(&node1);//Creation de la pipe por la node 1

    tabIndex++;

    ////////////////////////Node 2 ////////////
    ini(&node2);
    setNodeIdSimple(&node2,tabIndex);
    tabIndex++;
//je rajoute des voisn a ma node 2
    Node voisinA,voisinB;//declration des voisin

    ini(&voisinA);//intilisation des voidin
    setNodeIdSimple(&voisinA,tabIndex);
    createFifo(&voisinA);
    tabIndex++;

    ini(&voisinB);
    setNodeIdSimple(&voisinB,tabIndex);
    createFifo(&voisinB);
    tabIndex++;

    //ajout des voisin
    addVoisin(&node2,&voisinA);
    addVoisin(&node2,&voisinB);

    printf("Voisin A %s , Vosin B %s \n",getPipeFromId(voisinA.id),getPipeFromId(voisinB.id));

    //creation de la pipe
    createFifo(&node2);
    tabIndex++;

    addVoisin(&node1,&node2);

    Node *tab[2] = {&node1,&node2};
/*
    send(&node1,"hello");
    receive(&node1);
*/

//On vas uttilise des theared pour simule un reseau
    pthread_t t1,t2,ta,tb;
    //On cree 2 thead qui auron pour role decoute quand on tente de communique avec la pipe
    pthread_create(&t2,NULL,testReceive,&node2);
    pthread_create(&t1,NULL,testReceive,&node1);
    pthread_create(&ta,NULL,testReceive,&voisinA);
    pthread_create(&ta,NULL,testReceive,&voisinB);
    printf("Apres thread \n");


    //testSend(&node2,getPipeFromId(&node2.id),"helloZ");
    //la pipe 1 demende a la pipe 2 de lui donne ses voisn
   // askVoisin(&node1,getPipeFromId(&node2.id));

    findClosedNeibourg(&node1);

    //On attend que les thrad aye fini avant de termine le programe
    pthread_join(t2,NULL);
    pthread_join(t1,NULL);
    pthread_join(ta,NULL);
    pthread_join(tb,NULL);
    return 0;
}

//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include "string.h"
#include "kademiliaTest.h"

void peupleNode(Node * tab[],int nb){
    for (int i = 0; i < nb; ++i) {
        Node n ;
        ini(&n);
        tab[i] = &n;
    }
}

int main() {
    printf("start 2\n");

    srand(time(NULL));   // Initialization, should only be called once.
    Node node1,node2;
    int tabIndex = 0;
    ini(&node1);


    createFifo(&node1);

    tabIndex++;

    ini(&node2);

    Node voisinA,voisinB;
    ini(&voisinA);
    ini(&voisinB);

    addVoisin(&node2,&voisinA);
    addVoisin(&node2,&voisinB);

    printf("Voisin A %s , Vosin B %s \n",getPipeFromId(voisinA.id),getPipeFromId(voisinB.id));

    createFifo(&node2);
    tabIndex++;



    Node *tab[2] = {&node1,&node2};
/*
    send(&node1,"hello");
    receive(&node1);
*/


    pthread_t t1,t2;
    pthread_create(&t2,NULL,testReceive,&node2);
    pthread_create(&t1,NULL,testReceive,&node1);
    printf("Apres thread \n");
    //testSend(&node2,getPipeFromId(&node2.id),"helloZ");
    askVoisin(&node1,getPipeFromId(&node2.id));
    pthread_join(t2,NULL);


    return 0;
}

//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include "string.h"
#include "kademiliaTest.h"

int main() {
    printf("start \n");

    srand(time(NULL));   // Initialization, should only be called once.
    Node node1,node2;
    int tabIndex = 0;
ini(&node1);
node1.tabIndex = tabIndex;

    createFifo(&node1);

tabIndex++;

    ini(&node2);
    node2.tabIndex = tabIndex;
    createFifo(&node2);
    tabIndex++;



    Node *tab[2] = {&node1,&node2};

    send(&node1,"hello");
    receive(&node2);

/*
    printf("fork\n");

    int x = 0;
    fork();
    int tmp  =x;
    x++;
    send(tab[tmp%2],getPipeFromId(tab[tmp%2]->id));
    receive(tab[tmp%2]);

*/


    return 0;
}

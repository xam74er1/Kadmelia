//
// Created by root on 5/21/20.
//
#include "../package/node.h"
#include "../package/send_udp.h"
#include "../utilitaires/utilitaire.h"
int main() {
    srand(time(NULL));   // Initialization, du random
    Node nodeA,nodeB,nodeC;

    ini(&nodeA);
    setNodeIdSimple(&nodeA,1);

    ini(&nodeB);
    setNodeIdSimple(&nodeB,2);

    ini(&nodeC);
    setNodeIdSimple(&nodeC,3);

    printNode(&nodeA);
    printNode(&nodeB);

    pthread_t t1,t2;

    pthread_create(&t2,NULL,receive_udp,&nodeB);
    sleep(2);
    printf("Apres thead \n");
    send_udp(&nodeA,&nodeB);
    sleep(2);
    send_udp(&nodeC,&nodeB);
    pthread_join(t2,NULL);
}
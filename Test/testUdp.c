//
// Created by root on 5/21/20.
//
#include "../package/node.h"
#include "../package/send_udp.h"
#include "../utilitaires/utilitaire.h"
#include "../package/ping.h"

int main() {
    srand(time(NULL));   // Initialization, du random
    Node nodeA,nodeB,nodeC;

    ini(&nodeA);
    setNodeIdSimple(&nodeA,1);

    ini(&nodeB);
    setNodeIdSimple(&nodeB,2);

    ini(&nodeC);
    setNodeIdSimple(&nodeC,3);

    addVoisin(&nodeA,&nodeB);

    printNode(&nodeA);
    printNode(&nodeB);

    pthread_t t1,t2;

    pthread_create(&t2,NULL,receive_paquette,&nodeB);
    pthread_create(&t1,NULL,receive_paquette,&nodeA);
    sleep(2);
    printf("Apres thead \n");
    ping(&nodeA,&nodeB);
    sleep(2);

    pthread_join(t2,NULL);
    pthread_join(t1,NULL);
}
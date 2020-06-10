//
// Created by root on 6/3/20.
//

//
// Created by root on 5/31/20.
//

//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include "string.h"
#include "../package/node.h"
#include "../package/send_udp.h"
#include "../package/find_node.h"

/*
 * OBjectife du test : verifie que une node trouve bien dans la node la plus proche dans le reseau
 *
 * Deroulement : On commence par cree manuellment un reseau virutelle de node (peupleNodeMain)
 * puis on demende a une node de trouve la node la plus proche de sois dans le reseau (on dois avoir la node id : 4
 *
 * Second test est de reaise 2 saut pour trouve une node dans le reseau , on dois trouve la node id : 0
 */

/*
 * Sert a cree plein de node
 */
void peupleNode(Node * tab[],int nb){
    for (int i = 0; i < nb; ++i) {
        Node * n = malloc(sizeof(Node)) ;
        ini(n);
        setNodeIdSimple(n,i+1);

        tab[i] = n;
    }
    //On set les voisin
    //On vas laisse sa mais on vas change les vo
    for(int i =0;i<nb;i++){
        int tmp = (i+1)%nb;
        int* valleur =tab[i]->id;

        int *min = xordistanceTableau(tab[tmp]->id, valleur, IDLENGTH_INT);
        Node *nodeMin = tab[tmp];

        for (int j = 0; j < nb; j++) {
            if(i!=j){sleep(0.1);
                int *delta = xordistanceTableau(tab[j]->id, valleur, IDLENGTH_INT);
                if (GreatOrEqueals( min,delta, IDLENGTH_INT) > 0) {
                    // free(min);
                    min = delta;
                    nodeMin = tab[j];
                }

            }

        }
        addVoisin(tab[i],nodeMin);

        //SI la node actelle est plus pete que la node min , elle devien le nvx min

    }

}

void peupleNodeMain(Node * tab[]){
    for (int i = 0; i < 4; ++i) {
        Node * n = malloc(sizeof(Node)) ;
        ini(n);
        tab[i] = n;
        setNodeIdSimple(n,i);
    }


}

/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main() {
    printf("start 2\n");

    srand(time(NULL));   // Initialization, du random

    Node node1,nodeStart;//declration de 2 node


    int tabIndex = 1;

    ////////////////// NOde 1 ////////////////
    ini(&node1);//initilisation de la node 1
    setNodeIdSimple(&node1,4);

    ini(&nodeStart);
    setNodeIdSimple(&nodeStart,5);

    tabIndex++;
    int nb = 4;
    Node ** tab = malloc(sizeof(Node *)*nb);

    peupleNodeMain(tab);


/*
    send(&node1,"hello");
    receive(&node1);
*/

//On vas uttilise des theared pour simule un reseau
    pthread_t t1,t2;
    pthread_t ** tabThread = malloc(sizeof(pthread_t )*nb);
    for (int i = 0; i < nb; ++i) {
        pthread_t tmp;
        tabThread[i] = &tmp;
        pthread_create(tabThread[i],NULL,receive_udp,tab[i]);
        sleep(0.1);
    }
    //On cree 2 thead qui auron pour role decoute quand on tente de communique avec la pipe
    sleep(1);

    pthread_create(&t1,NULL,receive_udp,&node1);
    pthread_create(&t2,NULL,receive_udp,&nodeStart);

    sleep(1);

    printf("\n Apres thread \n\n\n\n");

for(int i =0;i<nb;i++){
    printf("Node : ");
    printNode(tab[i]);

    addVoisin(tab[i],&nodeStart);
    find_node(tab[i],tab[i]->id);
    printf("\n\n");
}
addVoisin(&node1,&nodeStart);
    find_node(&node1,node1.id);





printf("\n\n\n--------");
    for(int i =0;i<nb;i++) {
        printf("Node : ");
        printNode(tab[i]);
printBukket(tab[i]);
    }

    printf("Node ");
    printNode(&node1);
    printBukket(&node1);

    printf("Node ");
    printNode(&nodeStart);
    printBukket(&nodeStart);

    printf("LAST FIND NODE");
    sleep(1);
    printf("------\n\n\n\n");
    int * testTab[5];
    for(int i = 0;i<5;i++){
        testTab[i] = 0;
    }


    //On seche la node 0 , a la fin le messag dois etre "Le voisin final est nodespace/0-0-0-0-0 "
    find_node(&node1,testTab);

    pthread_join(t2,NULL);
    pthread_join(t1,NULL);
    for (int j = 0; j < nb; ++j) {
        pthread_join(tabThread[j],NULL);
    }


    return 0;
}

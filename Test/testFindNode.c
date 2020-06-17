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
    }
//Voisin de 0 : 7 et 3
    setNodeIdSimple(tab[0],0);
    addVoisin(tab[0],tab[1]);
    addVoisin(tab[0],tab[3]);

    //Voisin de 3 : 0 et 7
    setNodeIdSimple(tab[1],3);
    addVoisin(tab[1],tab[0]);
    addVoisin(tab[1],tab[3]);

    //Voisin de 5 : 7 et 0
    setNodeIdSimple(tab[2],5);
    addVoisin(tab[2],tab[3]);
    addVoisin(tab[2],tab[0]);

    //Voisin de 7 : 3 et 5
    setNodeIdSimple(tab[3],7);
    addVoisin(tab[3],tab[1]);
    addVoisin(tab[3],tab[2]);





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
    setNodeIdSimple(&node1,4);


    tabIndex++;
    int nb = 4;
    Node ** tab = malloc(sizeof(Node *)*nb);

    peupleNodeMain(tab);


    //Noe princiepale vosin de 4 : 5 et 3
    addVoisin(&node1,tab[2]);
    addVoisin(&node1,tab[1]);

    for(int i = 0;i<nb;i++){
        printNode(tab[i]);
        printBukket(tab[i]);
        printf("\n");
    }

    printNode(&node1);
    printBukket(&node1);

/*
    send(&node1,"hello");
    receive(&node1);
*/

//On vas uttilise des theared pour simule un reseau
    pthread_t t1;
    pthread_t ** tabThread = malloc(sizeof(pthread_t )*nb);
    for (int i = 0; i < nb; ++i) {
        pthread_t tmp;
        tabThread[i] = &tmp;
        pthread_create(tabThread[i],NULL,receive_paquette,tab[i]);
        sleep(0.1);
    }
    //On cree 2 thead qui auron pour role decoute quand on tente de communique avec la pipe
    sleep(1);

    pthread_create(&t1,NULL,receive_paquette,&node1);

    sleep(1);

    printf("\n Apres thread \n\n\n\n");


    //testSend(&node2,getPipeFromId(&node2.id),"helloZ");

    printf("\n\n\n\n");
    //Objectife trouve la node la plus proche de sois dans le reseau , a la fin le messag dois etre "Le voisin final est nodespace/5-0-0-0-0 "
    find_node(&node1,node1.id);

    sleep(1);
    printf("------\n\n\n\n");
    int * testTab[5];
    for(int i = 0;i<5;i++){
        testTab[i] = 0;
    }

    //On seche la node 0 , a la fin le messag dois etre "Le voisin final est nodespace/0-0-0-0-0 "
    find_node(&node1,testTab);

    //On attend que les thrad aye fini avant de termine le programe

    pthread_join(t1,NULL);
    for (int j = 0; j < nb; ++j) {
        pthread_join(tabThread[j],NULL);
    }

    return 0;
}

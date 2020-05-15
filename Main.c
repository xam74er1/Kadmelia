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
        Node * n = malloc(sizeof(Node)) ;
        ini(n);
        setNodeIdSimple(n,i+1);
        createFifo(n);
        tab[i] = n;
    }
    //On set les voisin
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
    int nb = 9;
    Node ** tab = malloc(sizeof(Node *)*nb);

    peupleNode(tab,nb);


   // peupleNode(tab,nb);
    for(int i =0;i<nb;i++){
        printf("node : %s : voisin  %s \n",getPipeFromId(tab[i]->id),getPipeFromId(tab[i]->voisin[0]->id));
    }

    addVoisin(&node1,tab[0]);

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
        pthread_create(tabThread[i],NULL,testReceive,tab[i]);
    }
    //On cree 2 thead qui auron pour role decoute quand on tente de communique avec la pipe


    pthread_create(&t1,NULL,testReceive,&node1);



    printf("\n Apres thread \n\n\n\n");


    //testSend(&node2,getPipeFromId(&node2.id),"helloZ");
    //la pipe 1 demende a la pipe 2 de lui donne ses voisn
    // askVoisin(&node1,getPipeFromId(&node2.id));

    findClosedNeibourg(&node1);

    //On attend que les thrad aye fini avant de termine le programe

    pthread_join(t1,NULL);
    for (int j = 0; j < nb; ++j) {
        pthread_join(tabThread[j],NULL);
    }

    return 0;
}

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

    for (int i = 0; i < 4; ++i) {
        createFifo(tab[i]);
    }



}

/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main(int argc, char **argv) {

    ///////////////
    ///Arguments///
    ///////////////
    int c;

    while (1)
    {
        static struct option long_options[] =
                {
                        {"ip",  required_argument, 0, 'i'},
                        {"port",  required_argument, 0, 'p'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "i:p:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 'i':
                printf ("option -i: `%s'\n", optarg);
                break;

            case 'p':
                printf ("option -p: `%s'\n", optarg);
                break;

            default:
                abort ();
        }
    }

    ///////


    printf("start 2\n");

    srand(time(NULL));   // Initialization, du random

    Node node1,node2;//declration de 2 node


    int tabIndex = 1;

    ////////////////// NOde 1 ////////////////
    ini(&node1);//initilisation de la node 1
    setNodeIdSimple(&node1,4);
    createFifo(&node1);//Creation de la pipe por la node 1

    tabIndex++;
    int nb = 4;
    Node ** tab = malloc(sizeof(Node *)*nb);

    peupleNodeMain(tab);


   // peupleNode(tab,nb);
    for(int i =0;i<nb;i++){
        printf("node : %s : voisin  %s \n",getPipeFromId(tab[i]->id),getPipeFromId(tab[i]->voisin[0]->id));
    }
    //Noe princiepale 4 : 5 et 3
    addVoisin(&node1,tab[2]);
    addVoisin(&node1,tab[1]);

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
    printf("\n\n\n\n");
    find_node(&node1,node1.id);
    printf("\n\n\n\n");
    int * testTab[5];
    for(int i = 0;i<5;i++){
        testTab[i] = 0;
    }
    find_node(&node1,testTab);

    //On attend que les thrad aye fini avant de termine le programe

    pthread_join(t1,NULL);
    for (int j = 0; j < nb; ++j) {
        pthread_join(tabThread[j],NULL);
    }

    return 0;
}

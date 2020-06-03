//
// Created by root on 5/27/20.
//



#include <stdbool.h>
#include "find_node.h"
#include "send_udp.h"



//Worik in Progresse


void find_node(struct Node *node, int *id) {

    printf("Debut de la rechesse de voisin pour id : %s \n",getPipeFromId(id));
    int nbVoisin = 1;
    Node ** tabVoisin = malloc(sizeof(Node *)*255);
    tabVoisin[0] = nodeLaPlusProche(node,id);
    printf("Node la plus proche au debut : %s \n",getPipeFromId(tabVoisin[0]->id));


    int  delta = 1;

    do{

        node->buffer = 0; //On vas attendre que un therad assyncrone ecrive ici l'id de la node recus , a ce moment le ptr sera diffrent de 0
        send_find_node(node,tabVoisin[nbVoisin-1],id);

        //Tanque l'on a pas recus une reponce on attend
        while(node->buffer == 0){
            sleep(0.1);
        }
        //On revois le pointeur vers la node recus
        Node * recus = (Node *) node->buffer;


        printf("Le voisin temporaire le plus proche est :  \n");printNode(recus);

        int * nvx = xordistanceTableau(id, recus->id, IDLENGTH_INT);
        int * old = xordistanceTableau(id,tabVoisin[nbVoisin-1]->id,IDLENGTH_INT);



        delta = GreatOrEqueals(old,nvx,IDLENGTH_INT);



        if(delta>0) {
            nbVoisin++;

            tabVoisin[nbVoisin - 1] = recus;
        }


printf("\n");
    }while(delta>0);

    printf("Le voisin final est %s \n",getPipeFromId(tabVoisin[nbVoisin-1]->id));
}
/*
*Input : la node en question , valleur de comparaison
* Renvois la node la plus proche de la valleur
        * Cela revien a fair un rechsse de min
*/


Node *nodeLaPlusProche(Node *node, int *valleur) {
    int *min;
    Node * nodeMin = 0;

    int i = 0;
//on chesse le premier buckette non vide
    while(node->listBucket[i]->nbVoisin==0&&i<(NBBUCKET-1)) i++;
//On est sur un paque qui nexite pas et qui ne contien pas de node
//On est surment arrive a la fin
//donc on arrete la
    if(!node->listBucket[i]->bukket[0]){

        return node;
    }

        nodeMin = node->listBucket[i]->bukket[0];

      min = xordistanceTableau(nodeMin->id, valleur, IDLENGTH_INT);



    for(int j = 1;j<node->listBucket[i]->nbVoisin;j++){
        int *delta = xordistanceTableau(node->listBucket[i]->bukket[j], valleur, IDLENGTH_INT);
        //SI la node actelle est plus pete que la node min , elle devien le nvx min
        printf("min : %s , delta : %s \n",getPipeFromId(min),getPipeFromId(delta));
        if (GreatOrEqueals(min, delta, IDLENGTH_INT) > 0) {
            free(min);
            min = delta;
            nodeMin = node->listBucket[i]->bukket[j];
        }
        free(delta);
    }

    i++;

    for(i;i<NBBUCKET;i++){
        if(node->listBucket[i]->nbVoisin>0){
            for(int j = 0;j<node->listBucket[i]->nbVoisin;j++){
                int *delta = xordistanceTableau(node->listBucket[i]->bukket[j], valleur, IDLENGTH_INT);
                //SI la node actelle est plus pete que la node min , elle devien le nvx min
                printf("min : %s , delta : %s \n",getPipeFromId(min),getPipeFromId(delta));
                if (GreatOrEqueals(min, delta, IDLENGTH_INT) > 0) {
                    free(min);
                    min = delta;
                    nodeMin = node->listBucket[i]->bukket[j];
                }
                free(delta);
            }
        }
    }
    if(nodeMin) {
        return nodeMin;
    }else{
        return node;
    }

}

void send_find_node(Node * from,Node * to,int * value){
    send_udp(from,to,MSG_FIND_NODE,value,IDLENGTH_SIZE);

}

/*
 * Action lors que je recois un find node , je lui renvois la node la plus prohce
 */
void receive_find_node(Node * from,Node * to,void * buffer){
    uint32_t idToFind[IDLENGTH_INT];
    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(&idToFind,buffer+decalage,IDLENGTH_SIZE);

    Node * close = nodeLaPlusProche(from,idToFind);
    int *delta = xordistanceTableau(close->id, idToFind, IDLENGTH_INT);
    int *xor = xordistanceTableau(from->id, idToFind, IDLENGTH_INT);

    //Si la node la plus proche est la minenne alors je remplace
    if (GreatOrEqueals(delta, xor, IDLENGTH_INT) > 0) {
    close = from;
    }
printf("Node renvoyer %s\n",getPipeFromId(close->id));
    int size = IDLENGTH_SIZE+sizeof(struct sockaddr_in);
    void * data = malloc(size);
//On copy id et addr ip
    memcpy(data,&close->id,IDLENGTH_SIZE);
    memcpy(data+IDLENGTH_SIZE,&close->addr_ip,sizeof(struct sockaddr_in));

    send_udp(from,to,MSG_FIND_NODE_REP,data,size);

    //on ajoute le voisin a la fin
    addVoisin(from,to);

}

void receive_closed_node(Node * from,Node * to,void * buffer){
    Node * close = malloc(sizeof(Node));

    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(&close->id,buffer+decalage,IDLENGTH_SIZE);
    memcpy(&close->addr_ip,buffer+decalage+IDLENGTH_SIZE,sizeof(struct sockaddr_in));

    printNode(close);

from->buffer = close;

}
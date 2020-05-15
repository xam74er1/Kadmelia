#include "../kademiliaTest.h"

void peupleNode(Node * tab[], int nb){
    for (int i = 0; i < nb; ++i) {
        Node * n =malloc(sizeof(Node)) ;
        ini(n);

        tab[i] = n;

        printf(" id : %s - %s  %d \n",getPipeFromId(n->id),getPipeFromId(tab[i]->id),i);
    }
    printf("\n\n");
    for(int i =0;i<nb;i++){
        printf(" id : %s \n",getPipeFromId(tab[i]->id));
    }
    printf("\n\n");
}
/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main() {

    Node ** tab = malloc(sizeof(Node *)*5);

    peupleNode(tab,5);

    for(int i =0;i<5;i++){
        printf(" id : %s \n",getPipeFromId(tab[i]->id));
    }

}
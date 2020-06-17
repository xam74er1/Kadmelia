//
// Created by root on 6/3/20.
//

#include "../package/node.h"

int main() {
/*
 * Verrifie que tout est bien plae au bonne endrois
 */
    Node nodeA;
    ini(&nodeA);
setNodeIdSimple(&nodeA,2);

    Node nodeB;
    ini(&nodeB);
    setNodeIdSimple(&nodeB,5);

    Node nodeC;
    ini(&nodeC);
    setNodeIdSimple(&nodeC,0);

    Node nodeD;
    ini(&nodeD);
    setNodeIdSimple(&nodeD,2);
    nodeD.id[1] = 2;


    addVoisin(&nodeA,&nodeB);
    addVoisin(&nodeA,&nodeC);
    addVoisin(&nodeA,&nodeD);

    for(int i =0;i<NBBUCKET;i++){
        if(nodeA.listBucket[i]->nbVoisin!=0){
            printf(" %d , %s \n",i,getPipeFromId(nodeA.listBucket[i]->bukket[0]->id));
        }
    }


}
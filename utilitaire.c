//
// Created by xam74 on 18/04/2020.
//

#include "utilitaire.h"


char *concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void printNode(Node * test){

    printf(" ip : %d \t port %d \t id :",test->ipAddres,test->port);

    for (int i = 0; i < IDLENGTH_INT; ++i) {
        printf("%x ",test->id[i]);
    }
}


int *xordistanceTableau(int *srcA, int *srcB, int length) {


    int * xor = malloc(sizeof(srcA[0])*length);
    for (int i = 0; i <length ; ++i) {
        xor[i] = srcA[i] ^ srcB[i];

    }

    return xor;
}

int xordistance(int a, int b) {
    return a^b;
}
/*  Great or Equal
 * Goal : a > b ? . On retoune a la premie difference trouve
 * Input : 2 tableau le longeure equivallente
 * Output :
 *          0 if a == b
 *          1 if a > b
 *          -1 if a <b
 */

int GreatOrEqueals(int *original, int *compare, int length) {

    for (int i = 0; i <length ; ++i) {
        int delta = original[i] - compare[i];
        if(delta!=0){
            return delta ;
        }
    }

    return 0;
}




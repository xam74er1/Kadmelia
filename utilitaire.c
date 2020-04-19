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
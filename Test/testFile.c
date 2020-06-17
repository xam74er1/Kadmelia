#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include "../utilitaires/fileTabChar.h"

int main(){
    char * path = "test.txt";

    char * res =  fileToChar(path);

    printf("message lus : %s \n",res);
    return 0;
}
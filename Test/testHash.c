//
// Created by root on 6/10/20.
//

#include "../utilitaires/hashFile.h"
#include "../package/node.h"

int main(){
char * test2 ="hello world2";
    char * test ="hello world";

    uint32_t * tab2 =  hashString(test2);

    printf("%s = %s \n",test2,getPipeFromId(tab2));

 uint32_t * tab =  hashString(test);

 printf("%s = %s \n",test,getPipeFromId(tab));

    uint32_t * hashF = hashFile("test.txt");

    printf("%s\n",getPipeFromId(hashF));
    return 0;
}
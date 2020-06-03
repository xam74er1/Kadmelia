//
// Created by root on 5/6/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <openssl/sha.h>
#include "../lib/openssl/sha.h"
#include <inttypes.h>

union mysha1{
    uint32_t shaint[5];
    unsigned char shachar[20];
};

int main()
{
    const unsigned char str[] = "Original String";
    union mysha1 hash;

    SHA1(str, sizeof(str) -1, hash.shachar);

    fprintf(stderr, "Hashed successfully\n");
    fprintf(stderr, str);
    //fprintf(stderr, hash);
    fprintf(stderr,"%" PRIu32 "\n", hash.shaint);


  /*  for (int i = 0; i < sizeof(hash); i++)
        fprintf(stderr, "%.3f", hash.shaint[i]);
*/

    return 0;
}
//
// Created by root on 5/6/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <openssl/sha.h>
#include "../lib/openssl/sha.h"

int main()
{
    const unsigned char str[] = "Original String";
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1(str, sizeof(str) -1, hash);

    fprintf(stderr, "Hashed successfully\n");
    fprintf(stderr, str);
    fprintf(stderr, hash);


    return 0;
}
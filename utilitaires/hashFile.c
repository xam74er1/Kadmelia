//
// Created by root on 6/10/20.
//

#include "hashFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <openssl/sha.h>
#include "../lib/openssl/sha.h"
#include <inttypes.h>

#define BUFSIZE 1024*16

unsigned int *hashString(char *str) {
    union mysha1 *hash = malloc(sizeof(union mysha1));

    SHA1(str, strlen(str) , hash->shachar);

    return hash->shaint;
}
//Source code : https://docs.huihoo.com/doxygen/openssl/1.0.1c/sha1_8c_source.html
unsigned int *hashFile(char *path) {
    FILE *f;
    f = fopen(path, "r");
    union mysha1 *hash = malloc(sizeof(union mysha1));

    if (f != NULL) {
        SHA_CTX c;

        int fd;
        int i;
        unsigned char buf[BUFSIZE];

        fd = fileno(f);
        SHA1_Init(&c);
        for (;;) {
            i = read(fd, buf, BUFSIZE);
            if (i <= 0) break;
            SHA1_Update(&c, buf, (unsigned long) i);
        }
        SHA1_Final(&hash->shachar, &c);

     return hash->shaint;

    } else {
        fprintf(stderr, "Cannot open file: %s\n", path);
    }

    return 0;
}
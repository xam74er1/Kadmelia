//
// Created by root on 6/10/20.
//

#ifndef GROUPE7_HASHFILE_H
#define GROUPE7_HASHFILE_H


#include <stdint.h>
#include "../package/node.h"

union mysha1{
    uint32_t shaint[IDLENGTH_INT];
    unsigned char shachar[20];
};

unsigned int * hashString(char * str);
unsigned int *hashFile(char * path);

#endif //GROUPE7_HASHFILE_H

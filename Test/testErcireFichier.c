//
// Created by root on 6/12/20.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
int main(){
    char * str = "ntm";
    FILE *write_ptr;

    write_ptr = fopen("serveur.txt","wb");  // w for write, b for binary

    fwrite(str,strlen(str),1,write_ptr); // write 10 bytes from our buffer
    fwrite(str,strlen(str),1,write_ptr); // write 10 bytes from our buffer
    fwrite(str,strlen(str),1,write_ptr); // write 10 bytes from our buffer
}
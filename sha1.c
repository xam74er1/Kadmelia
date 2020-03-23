//
// Created by xam74 on 19/02/2020.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define h0 0x67452301
#define h1 0xEFCDAB89
#define h2 0x98BADCFE
#define h3 0x10325476
#define h4 0xC3D2E1F0



int rol(int num, int cnt) {
    return (num << cnt) | (num >> (32 - cnt));
}

 void fill(int value, char* arr, int off) {
    arr[off + 0] = (char) ((value >> 24) & 0xff);
    arr[off + 1] = (char) ((value >> 16) & 0xff);
    arr[off + 2] = (char) ((value >> 8) & 0xff);
    arr[off + 3] = (char) ((value >> 0) & 0xff);
}

char* hash(char * tab){

    long length = 42;
   long lengthPading = (((length + 8) >> 6) + 1) * 16;
    int pading[lengthPading];
int i =0;
    for(i = 0; i < length; i++) {
        pading[i >> 2] |= tab[i] << (24 - (i % 4) * 8);
    }


    pading[i >> 2] |= 0x80 << (24 - (i % 4) * 8);

    pading[lengthPading-1] = length * 8;
//Caclule du hash de 160
    int w[80] ;

    int a =  1732584193;
    int b = -271733879;
    int c = -1732584194;
    int d =  271733878;
    int e = -1009589776;

    for(i = 0; i < lengthPading; i += 16) {
        int olda = a;
        int oldb = b;
        int oldc = c;
        int oldd = d;
        int olde = e;

    for(int j = 0; j < 80; j++) {
        w[j] = (j < 16) ? pading[i + j] :
               ( rol(w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16], 1) );

        int t = rol(a, 5) + e + w[j] +
                ( (j < 20) ?  1518500249 + ((b & c) | ((~b) & d))
                           : (j < 40) ?  1859775393 + (b ^ c ^ d)
                                      : (j < 60) ? -1894007588 + ((b & c) | (b & d) | (c & d))
                                                 : -899497514 + (b ^ c ^ d) );
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }

    a = a + olda;
    b = b + oldb;
    c = c + oldc;
    d = d + oldd;
    e = e + olde;
}

// Convert result to a byte array
char * digest = malloc(20);
fill(a, digest, 0);
fill(b, digest, 4);
fill(c, digest, 8);
fill(d, digest, 12);
fill(e, digest, 16);

return digest;
}

int main() {
    char * str = "Hello";

    char * res = hash(str);
    for(int i =0;i<20;i++){
        printf("%x ",res[i]);
    }

    return 0;
}
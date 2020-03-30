//
// Created by xam74 on 19/02/2020.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



debug(char * str){
    printf("%s\n",str);
}




int * hashB(char * msg){

    unsigned int a, b, c, d, e, f, g;
    int nb = 0;
    int buff = 0;
    int i ;

    unsigned int length =  sizeof(msg) / sizeof(msg[0]) ;

    //On ajoute 0x80 a la fin du message

    buff = nb-length-1+448;
//On cesse a savoire combien de 0 on dois rajoute pour avoir
    while(buff%512 != 0)
    {
        nb++;
        buff = nb-length-1+448;
    }

    char tab[length+1+nb];

    for(int i =0;i<length;i++){
        tab[i] = msg[i];
    }

    tab[length] = 0x80;

    for(i=0;i<nb;i++)
    {
        tab[length+1+i] = 0x00;
    }

    length = length+1+nb;
    int n = length/64;
    unsigned int w[80];
    int buff1;

    int h0 = 0x67452301;
    int h1 =0xEFCDAB89;
    int  h2= 0x98BADCFE;
    int h3= 0x10325476;
    int  h4 =0xC3D2E1F0;

    for (i=0;i<=n;i++){
        for (int t=0;t<79;t++){
            if ((t>=0) && (t<=15)) {
                w[t] = tab[i];
            }else{
                if ((t>=16) && (t<=79)){
                    w[t] = ((w[(t-3)]) ^ (w[(t-8)]) ^ (w[(t-14)]) ^ (w[(t-16)])) << 1;
                }
            }

            a = h0;
            b = h1;
            c = h2;
            d = h3;
            e = h4;

            if ((t >= 0) && (t <= 19))
            {
                f = (b & c) ^ ((~b) & d);
                g = 0x5A827999;
            }
            else if ((t >= 20) && (t <= 39))
            {
                f = b ^ c ^ d;
                g = 0x6ED9EBA1;
            }
            else if ((t >= 40) && (t <= 59))
            {
                f = (b & c) ^ (b & d) ^ (c & d);
                g = 0x8F1BBCDC;
            }
            else if ((t >= 60) && (t <= 79))
            {
                f = b ^ c ^ d;
                g = 0xCA62C1D6;
            }

            buff1 = ((a << 5) + f + e + g + w[t]);
            e = d;
            d = c;
            c = b << 30;
            b = a;
            a = buff1;

        }
        //  printf("Buf 1 %d \n",buff1);
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
    }

    int * res = malloc(sizeof(int)*5);

    res[0] = h0;
    res[1] = h1;
    res[2] = h2;
    res[3] = h3;
    res[4] = h4;

    return res;
}

/*
 *
 *
 *
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

    long length =  sizeof(tab) / sizeof(tab[0]) ;
    long lengthPading = (((length + 8) >> 6) + 1) * 16;
    int pading[lengthPading];
    int i =0;
    for(i = 0; i < length; i++) {
        pading[i >> 2] |= tab[i] << (24 - (i % 4) * 8);
    }


    pading[i >> 2] |= 0x80 << (24 - (i % 4) * 8);

    pading[lengthPading-1] = length * 8;
//Caclule du hash de 160
    //int* w = (int *) calloc(80,sizeof(int)) ;
    int w[80];
    for(int i =0;i<80;i++){
        w[i] = 0;
    }

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

        printf(" a : %d \n",a);
        printf(" b : %d \n",b);
        printf(" c : %d \n",c);
        printf(" d : %d \n",d);
        printf(" e : %d \n",e);
        printf("\n");

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

    printf("\n\n");
    printf(" a : %d \n",a);
    printf(" b : %d \n",b);
    printf(" c : %d \n",c);
    printf(" d : %d \n",d);
    printf(" e : %d \n",e);
    printf("\n");

// Convert result to a byte array
    char * digest = malloc(20);
    fill(a, digest, 0);
    fill(b, digest, 4);
    fill(c, digest, 8);
    fill(d, digest, 12);
    fill(e, digest, 16);

    return digest;
}
*/
int xordistanceTableau(char * srcA,char * srcB){
    int min = sizeof(srcA)< sizeof(srcB) ? sizeof(srcB) : sizeof(srcA);
    char * xor = malloc(sizeof(srcA[0])*min);
    for (int i = 0; i <min ; ++i) {
        xor[i] = srcA[i] ^ srcB[i];
    }

    return xor;
}

int xordistance(int a , int b ){
    return a^b;
}

int main() {
    printf("start 4\n");
    char * str = "hello";

    int * res = hashB(str);

    for(int i =0;i<5;i++){
        printf("%x ",res[i]);
    }
    printf("\n");
    char * autre = "hello";
    int * resAutre = hashB(autre);
    for(int i =0;i<5;i++){
        printf("%x ",resAutre[i]);
    }

    printf("\n");

    char * xdistance =  xordistanceTableau(res,resAutre);
    printf("\n");
    for(int i =0;i<20;i++){
        printf("%x ", xdistance[i]);
    }

    printf("\nfin\n");
    return 0;
}
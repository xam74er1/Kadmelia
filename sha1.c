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

int * xordistanceTableau(int * srcA,int * srcB,int length){


    int * xor = malloc(sizeof(srcA[0])*length);
    for (int i = 0; i <length ; ++i) {
        xor[i] = srcA[i] ^ srcB[i];
        printf("%x ^ %x = %x \n ",srcA[i],srcB[i],xor[i]);
    }

    return xor;
}

int xordistance(int a , int b ){
    return a^b;
}

int main() {
    printf("start 4\n");
    char * str = "Hello";

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

    int * xdistance =  xordistanceTableau(res,resAutre,5);
    printf("\n");
    for(int i =0;i<5;i++){
        printf("%x ", xdistance[i]);
    }

    printf("\nfin\n");
    return 0;
}
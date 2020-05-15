//
// Created by root on 5/1/20.
//

int main() {
    int a = 10;


    for(int i = 2;i<20;i++){
        printf(" %d xor %d = %d \n",a,i,(a^i));
    }

    int tmp = -1%2;

printf("\n\n\n");

for(int i = 1;i<6;i++){
    for(int j = 1;j<6;j++){
        printf(" %d xor %d = %d \n",j,i,(j^i));
    }
    printf("\n");
}

    printf(" modulo %d",tmp);
}
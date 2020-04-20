#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define TAILLE_MESSAGE	256

int main(void)
{
    int entreeTube;
    char nomTube[] = "nodespace/essai.fifo";
printf("start\n");
    char chaineAEcrire[TAILLE_MESSAGE] = "Bonjour";
/*
    if(mkfifo(nomTube, 0644) != 0)
    {
        fprintf(stderr, "Impossible de créer le tube nommé.\n");
        exit(EXIT_FAILURE);
    }*/
    printf("b\n");
    if((entreeTube = open(nomTube, O_RDWR)) == -1)
    {
        fprintf(stderr, "Impossible d'ouvrir l'entrée du tube nommé.\n");
        exit(EXIT_FAILURE);
    }
    printf("c");
    write(entreeTube, chaineAEcrire, TAILLE_MESSAGE);


    return EXIT_SUCCESS;
}

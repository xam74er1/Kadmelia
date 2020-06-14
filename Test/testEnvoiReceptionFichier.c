//
// Created by root on 6/14/20.
//

#include "../package/node.h"
#include "../package/fichier.h"
#include "../package/bdd.h"
#include "../package/publish_key.h"
#include "../event/lisent.h"

/*
 * Le but de ce test est de :
 * 1 - enregitre un ficher en bdd
 * 2- publie ce fichier sur le reseau
 * 3-retoruve ce fichier dans le reseau
 * 4-telecharge ce fichier
 */
int main(){
//on cree les 3 node
    Node *stoquage = malloc(sizeof(Node));
    Node *proprieteFichier =malloc(sizeof(Node));
    Node * question =malloc(sizeof(Node));

    iniIDSimple(stoquage,1);

    iniIDSimple(proprieteFichier,2);

    iniIDSimple(question,3);

    addVoisin(proprieteFichier,stoquage);
    addVoisin(question,stoquage);

    Fichier f;

    strcpy(f.nom,"test.txt");
    char * path ="test.txt";


    printf("\n\n\n \033[0;33mEnregistrent en BDD \033[0m \n");
    //On save en BD le chemain
    setlocalfile(stoquage,f.nom,path);


    pthread_t t1,t2,t3;
    pthread_create(&t1, NULL, (void *(*)(void *)) receive_paquette, stoquage);
    sleep(0.1);
    pthread_create(&t2, NULL, (void *(*)(void *)) receive_paquette, proprieteFichier);
    sleep(0.1);
    pthread_create(&t3, NULL, (void *(*)(void *)) receive_paquette, question);
    sleep(0.1);

    printf("\n\n\n\n Apres thread : \n\n\n");

    //on publie le fichier
    publish_key(proprieteFichier,f.nom);



    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

}
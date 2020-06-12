//
// Created by root on 5/20/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../lib/sqlite3.h"
#include <inttypes.h>
#include "../package/node.h"
#include "../package/bdd.h"



int callback(void *, int, char **, char **);


int main(int argc, char* argv[]){

    createDatabase();

    uint32_t id[5] = { 4, 8 ,9 ,10, 110 };
    long ip = 454545;
    int port = 8000;
    int bucket_id = 1 ;

    Node node;
    ini(&node);

    node.id[0] = id[0];
    node.id[1] = id[1];
    node.id[2] = id[2];
    node.id[3] = id[3];
    node.id[4] = id[4];


    Node node2;
    ini(&node2);

    setNode(&node);

    getNode(id,&node2);

    Node node3;
    ini(&node3);

    uint32_t fichier[5] = { 1, 2 ,3 ,4, 5 };
    char nom[6] = { 'm', 'a', 't', 'r', 'i', 'x'};
    int taille = 12;

    SetFile(id, fichier, id, nom, taille);

    findNode(fichier, &node3);

   setlocalfile(nom,nom);

    return 0;
}


//affichage de toutes les lignes des queries
int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}




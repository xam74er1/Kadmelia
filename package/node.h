//
// Created by root on 5/20/20.
//

#ifndef GROUPE7_NODE_H
#define GROUPE7_NODE_H
#include <time.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utilitaires/utilitaire.h"

#include <pthread.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define IDLENGTH_INT 5 //Nombre de int qui compose un id (ici 5*32 = 160 bit)
#define NBVOISIN_MAX 3 //Nomre de voisin maximome corepond au k-bukkets
#define DIRECTORYTEST "nodespace" //Nom du dossie qui contien les test

typedef struct Node{
    int sockfd; //Socket de communcation pour recevoire
    struct sockaddr_in addr_ip; //tout les ip
    uint32_t id[IDLENGTH_INT];//id de la node
    struct Node * voisin[NBVOISIN_MAX]; //list de mes voisin
    int nbVoisin; //nombre de voisin que jai actuellment
    int * idRessu ;//Donne de transition pour les thread qui comminique ici , voir la partie  findClosedNeibourg

    int tabIndex;
}Node;


//Constructeu de la node
void ini(Node * fromNode);

//Met un id a la node qui est juste un int , le reste est cmplet par des 0 .Cela sert a avoir un id de 5 int defini simpemnt (nottament pour la lecture humaine)
void setNodeIdSimple(Node *fromNode, int id);

//serter pour un id
void setNodeId(Node *fromNode, int id[IDLENGTH_INT]);
//Rajoute un voisin dans le tableau des node
void addVoisin(Node *original, Node *voisin);

//set index a la node
void setTabIndex(Node * node, int index);

int iniID(Node * node);

void iniAddr(Node * node);

char *getPipeFromId(int *id);
#endif //GROUPE7_NODE_H

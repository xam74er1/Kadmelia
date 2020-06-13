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
#include "bukket.h"

#include <pthread.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../lib/sqlite3.h"

//COnstante uttile
#define IDLENGTH_INT 5 //Nombre de int qui compose un id (ici 5*32 = 160 bit)
#define IDLENGTH_SIZE IDLENGTH_INT*sizeof(uint32_t)
#define DIRECTORYTEST "nodespace" //Nom du dossie qui contien les test
#define NBBUCKET 160


//Mesage uttilise

#define MSG_UNKNOW -1
#define MSG_PING 2
#define MSG_PONG 3

#define MSG_FIND_NODE 4
#define MSG_FIND_NODE_REP 5

#define MSG_PUBLISH_KEY 6
#define MSG_PUBLISH_KEY_OK 7

#define MSG_FIND_VALUE 8
#define MSG_FIND_VALUE_REP 9

typedef struct Node{
    int sock_udp; //Socket de communcation pour udp
    int sock_tcp; //Socket de communcation pour tcp
    struct sockaddr_in addr_ip; //tout les ip
    uint32_t id[IDLENGTH_INT];//id de la node
    struct Node * buffer ;//Donne de transition pour les thread qui comminique ici , voir la partie  findClosedNeibourg
    struct Bucket * listBucket[NBBUCKET]; //list de tout les bucket disponible
    int tabIndex;
    sqlite3 * db; //pointeur vers la base de donne
}Node;


//Constructeu de la node
void ini(Node * fromNode);
void iniIDSimple(Node * fromNode,int id);

//Met un id a la node qui est juste un int , le reste est cmplet par des 0 .Cela sert a avoir un id de 5 int defini simpemnt (nottament pour la lecture humaine)
void setNodeIdSimple(Node *node, int id);

//serter pour un id
void setNodeId(Node *fromNode, int id[IDLENGTH_INT]);
//Rajoute un voisin dans le tableau des node
void addVoisin(Node *original, Node *voisin);

//set index a la node
void setTabIndex(Node * node, int index);

//Inilise les ID
int iniID(Node * node);

//Inilise les adrese ip
void iniAddr(Node * node);

//Mtode uttilse pour les string
char *getPipeFromId(int *id);

//ajoute une node dans le bon buckette
void * addNodeToBukket(Node * from,Node * toAdd);

//Inilise le folder
void * iniFolder(Node * node);

//Partie comune pour initile les node
void iniCommun(Node * node);
#endif //GROUPE7_NODE_H

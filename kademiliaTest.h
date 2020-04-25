//
// Created by xam74 on 13/04/2020.
//

#ifndef GROUPE7_KADEMILIATEST_H
#define GROUPE7_KADEMILIATEST_H
#include <time.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilitaire.h"

#include <pthread.h>

#define IDLENGTH_INT 5
#define NBVOISIN_MAX 3
#define DIRECTORYTEST "nodespace"

//Definition des id
#define  ASK_ID 0
#define  ASK_ID_REP 1
#define ASK_VOISIN 2
#define REP_VOISIN 3

//Pseudo objet
typedef struct Node{
    long ipAddres;//Adrrse id
    int port;//Port
    u_int32_t id[IDLENGTH_INT];//id de la node
    struct Node * voisin[NBVOISIN_MAX];
    int nbVoisin;

    int tabIndex;
}Node;
void iniIp();

void iniPort();

void ini(Node * fromNode);

iniID();

void setNodeIdSimple(Node *fromNode,int id);
void setNodeId(Node *fromNode,int id[IDLENGTH_INT]);
void addVoisin(Node *original,Node *voisin);

void createFifo(Node *fromNode);
void setTabIndex(Node * node,int index);
char * getPipeFromId(int id[IDLENGTH_INT]);

void send(Node * node , char str[80]);
void receive(Node * node );


void sendVoisin(Node * node,char * dest);
void reciveVoisin(Node * node , int pipe);
void *askVoisin(Node *node,char *dest);

        void *askId(Node *node,char *dest);
void * testSend(Node *node,char *dest,char *str);
void *testReceive(Node * node);

#endif //GROUPE7_KADEMILIATEST_H

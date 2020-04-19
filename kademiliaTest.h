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

#define IDLENGTH_INT 5
#define DIRECTORYTEST "nodespace"

typedef struct Node{
    long ipAddres;//Adrrse id
    int port;//Port
    u_int32_t id[IDLENGTH_INT];//id de la node
    int tabIndex;
}Node;
void iniIp();

void iniPort();

void ini(Node * fromNode);

iniID();

void setNodeIdSimple(Node *fromNode,int id);
void setNodeId(Node *fromNode,int id[IDLENGTH_INT]);

void createFifo(Node *fromNode);
void setTabIndex(Node * node,int index);
char * getPipeFromId(int id[IDLENGTH_INT]);

void send(Node * node , char str[80]);
void receive(Node * node );

#endif //GROUPE7_KADEMILIATEST_H

//
// Created by root on 5/21/20.
//

#ifndef GROUPE7_SEND_UDP_C_H
#define GROUPE7_SEND_UDP_C_H
#include "node.h"
#include "../utilitaires/utilitaire.h"
#define MAXRETURNNODE 32

_Noreturn //Receois un message UDP
void receive_udp(Node * from);


/*
But : envoye une information a une autre node
Parametre :
 Node from : node d'origine
 Node to : node de destination
 char type : type de message (voir les message dans Node.h)
 void * data : donne a transmtre , on le met de type void pour dire que cela est nimporte quelle paratre
 long size : taille des donne a envoyer
 */
void send_udp(Node * from,Node * to,char  type,void * data,long size);
#endif //GROUPE7_SEND_UDP_C_H

//
// Created by bng on 12/06/2020.
//

#ifndef GROUPE7_SENDFILETCP_H
#define GROUPE7_SENDFILETCP_H

#include "node.h"
#define SA struct sockaddr
#define port 8080
#define Nmax 100

void send_tcp_file(Node * from,int sock , char * path);
void write_file(Node *from, int sock, char *path);
void accecpt_to_send_file(Node * from);
void requeste_file(Node * from,Node * to,char * fileName);
void testTCP(Node * from,Node * to);
void testRecoisTCP(Node * from);













#endif //GROUPE7_SENDFILETCP_H

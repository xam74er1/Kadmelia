//
// Created by bng on 12/06/2020.
//

#ifndef GROUPE7_SENDFILETCP_H
#define GROUPE7_SENDFILETCP_H

#include "node.h"
#define SA struct sockaddr
#define port 8080
#define Nmax 100

void send_tcp_file(Node * from,Node * to , char * path);
void write_file(Node *from, char *path);














#endif //GROUPE7_SENDFILETCP_H

//
// Created by root on 5/27/20.
//

#ifndef GROUPE7_FIND_NODE_H
#define GROUPE7_FIND_NODE_H
#include "node.h"


Node * find_node(struct Node *node, int *id);
/*
 * Renvois la node la plus proche de la valleur au sesn xditance
 */
Node * nodeLaPlusProche(Node * node, int * valleur);

void send_find_node(Node * from,Node * to,int * value);

void receive_find_node(Node * from,Node * to,void * buffer);

void receive_closed_node(Node * from,Node * to,void * buffer);

#endif //GROUPE7_FIND_NODE_H

//
// Created by root on 6/12/20.
//

#ifndef GROUPE7_FIND_VALUE_H
#define GROUPE7_FIND_VALUE_H

#include "node.h"

void * find_value(Node * from, Node * to, int * hash);
void * receive_find_value(Node * from,Node * container,void * buffer);
void * receive_find_value_rep(Node * from,Node * container,void * buffer);
void find_file(Node * from,char * fileName);
#endif //GROUPE7_FIND_VALUE_H

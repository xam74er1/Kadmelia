//
// Created by root on 6/6/20.
//

#ifndef GROUPE7_PUBLISH_KEY_H
#define GROUPE7_PUBLISH_KEY_H

#include "node.h"

void * publish_key(Node * node, char * path);
void * receive_publish_key(Node * from,Node * container,void * buffer);
#endif //GROUPE7_PUBLISH_KEY_H

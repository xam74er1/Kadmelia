//
// Created by root on 6/6/20.
//

#include "publish_key.h"
#include "find_node.h"
#include "send_udp.h"

void * publish_key(Node * from,int * hash){
    //on trouve la node ou on publie
    struct Node * toPublish = find_node(from,hash);

    send_udp(from,toPublish,MSG_PUBLISH_KEY,hash,IDLENGTH_SIZE);
}

void * receive_publish_key(Node * from,Node * container,void * buffer){
    uint32_t hash[IDLENGTH_INT];
    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(&hash, buffer + decalage, IDLENGTH_SIZE);


}
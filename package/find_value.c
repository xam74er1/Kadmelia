//
// Created by root on 6/12/20.
//

#include "find_value.h"
#include "node.h"
#include "send_udp.h"

void * find_value(Node * from,Node * to,int * hash){
    send_udp(from,to,MSG_FIND_VALUE,hash,IDLENGTH_SIZE);
}

void * receive_find_value(Node * from,Node * container,void * buffer){
    uint32_t hash[IDLENGTH_INT];
    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(&hash,buffer+decalage,IDLENGTH_SIZE);


}
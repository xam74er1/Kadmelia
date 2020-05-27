#include "ping.h"
#include "send_udp.h"

void ping(Node * from, Node * to){
char hello = 0;

size_t size= 1;

send_udp(from,to,MSG_PING,&hello,size);

}

void pong(Node * from,Node *to){
    char hello = 0;

    size_t size= 1;

    send_udp(from,to,MSG_PONG,&hello,size);
}
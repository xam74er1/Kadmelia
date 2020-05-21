//
// Created by root on 5/21/20.
//
#include "send_udp.h"


void send_udp(Node * from,Node * to){
    printf("send udp\n");
    sendto(from->sockfd, &from->id, sizeof(uint32_t)*IDLENGTH_INT,
           MSG_CONFIRM, (const struct sockaddr *) &to->addr_ip,
           sizeof(to->addr_ip));

    printf("send udp ok\n");
}


void receive_udp(Node * from){
    printf("recefe udp \n");
    uint32_t buffer[IDLENGTH_INT];
    int len;

    // Bind the socket with the server address
    if ( bind(from->sockfd, (const struct sockaddr *)&from->addr_ip,
              sizeof(from->addr_ip)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printNode(from);
    while(1) {
        int n = recvfrom(from->sockfd, buffer, sizeof(uint32_t) * IDLENGTH_INT,
                         MSG_WAITALL, (struct sockaddr *) &from->addr_ip,
                         &len);

        printf("Node recus %s \n", getPipeFromId(buffer));
    }
}
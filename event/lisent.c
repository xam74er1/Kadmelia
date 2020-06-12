//
// Created by root on 6/12/20.
//

#include "lisent.h"
#include "../package/send_udp.h"

_Noreturn void receive_paquette(Node * from){
    fd_set rset;
    //Nbr de donne maximale que le serveur UDP peux recevoire = 255 node + type + id sender
    printf("recefe udp \n");
    uint32_t id[IDLENGTH_INT];
    int max,nready;

    int tmp = bind(from->sock_udp, (const struct sockaddr *) &from->addr_ip,
                   sizeof(from->addr_ip));
    // Bind the socket with the server address
    if ( tmp< 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }else{

        printf("bind ok %d \n");
    }

    printNode((struct Node *) from);

    FD_ZERO(&rset);
    listen(from->sock_tcp, 10);

    max = (from->sock_tcp>from->sock_udp ? from->sock_tcp : from->sock_udp)+1;

    while (1) {



        Node test;

        // set listenfd and udpfd in readset
        FD_SET(from->sock_tcp, &rset);
        FD_SET(from->sock_udp, &rset);

        nready = select(max, &rset, NULL, NULL, NULL);

        //Si on recois de UDP
        if (FD_ISSET(from->sock_udp, &rset)) {
            receive_udp(from);
        }
    }
}
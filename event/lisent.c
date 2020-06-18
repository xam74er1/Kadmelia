//
// Created by root on 6/12/20.
//

#include "lisent.h"
#include <sys/select.h>
#include "../package/send_udp.h"
#include "../package/SendFileTCP.h"


_Noreturn void receive_paquette(Node * from){
    fd_set rset;
    //Nbr de donne maximale que le serveur UDP peux recevoire = 255 node + type + id sender
    printf("receive udp \n");
    uint32_t id[IDLENGTH_INT];
    int max,nready;

    int tmp = bind(from->sock_udp, (const struct sockaddr *) &from->addr_ip,
                   sizeof(from->addr_ip));

    if ( tmp< 0) {

        perror("bind failed UDP");
        exit(EXIT_FAILURE);
    }else{

        printf("bind udp ok %d \n");
    }

     tmp = bind(from->sock_tcp, (const struct sockaddr *) &from->addr_ip,sizeof(from->addr_ip));
    // Bind the socket with the server address
    if ( tmp< 0) {

        perror("bind failed TCP");
        exit(EXIT_FAILURE);
    }else{

        printf("bind tcp ok %d \n");
    }

    printNode((struct Node *) from);

    FD_ZERO(&rset);
    if ( listen(from->sock_tcp, 10)!=0){
        perror("Error listen \n");
    }else{
        printf("listen is ok\n");
    }

    max = (from->sock_tcp>from->sock_udp ? from->sock_tcp : from->sock_udp)+1;

    while (1) {

        Node test;

        // set listenfd and udpfd in readset
        FD_SET(from->sock_tcp, &rset);
        FD_SET(from->sock_udp, &rset);

        nready = select(max, &rset, NULL, NULL, NULL);
printf("après select\n");
        //Si on recois de UDP
        if (FD_ISSET(from->sock_udp, &rset)) {
            receive_udp(from);
        }
        // Si on reçoit du TCP
        if (FD_ISSET(from->sock_tcp, &rset)) {

            accecpt_to_send_file(from);
            //testRecoisTCP(from);
        }
    }
}
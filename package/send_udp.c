//
// Created by root on 5/21/20.
//
#include "send_udp.h"
#include "ping.h"
#include "find_node.h"
#include "publish_key.h"
#include "find_value.h"
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;

void send_udp(Node *from, Node *to, char type, void *data, long size) {
    if(DEBUG==1) {
        printf("send udp\n");
    }
//Cette partie du code est assez technique
//On vas recopie dans une zone memoire toute les donne a envoye en un seul paquet udp

//Pour commence on alloue une zone memoire de la taille corepondant
    void *dest = (void * ) malloc((sizeof(char) + sizeof(uint32_t) * IDLENGTH_INT + size));

//puis on recopie tout dans cette zone memoire
    long lengthcopy = 0;
//le type de message
    memcpy(dest , &type, sizeof(char));
    lengthcopy += sizeof(char);

    //Id de la perssone qui envoie
    memcpy(dest + lengthcopy, from->id, sizeof(uint32_t) * IDLENGTH_INT);
    lengthcopy += sizeof(uint32_t) * IDLENGTH_INT;

    //les donne a envoyer
    memcpy(dest + lengthcopy, data, size);
    lengthcopy += size;

    //On envois les donne cotneus dans la zone memoire
    sendto(from->sock_udp, dest, lengthcopy,
           MSG_CONFIRM, (const struct sockaddr *) &to->addr_ip,
           sizeof(to->addr_ip));

    //on oublie pas de libre la zone emoire
    free(dest);
    if(DEBUG==1) {
        printf("send udp ok to \n");
        printNode((struct Node *) to);
    }

}


void receive_udp(Node *from) {
    int MAXDATA_UDP = 2*MAXRETURNNODE*(IDLENGTH_INT*sizeof(uint32_t)+sizeof(struct sockaddr_in))+sizeof(char)+IDLENGTH_INT*sizeof(uint32_t);
char type ='a';
    struct sockaddr_in fromAddr;
    int len = sizeof(fromAddr);

        void *buffer = malloc(MAXDATA_UDP);
        int n = recvfrom(from->sock_udp, buffer, MAXDATA_UDP,
                         MSG_WAITALL, (struct sockaddr *) &fromAddr,
                         &len);
        Node test ;

            Node * reponce = malloc(sizeof(Node));
        memcpy(&type,buffer,sizeof(char));
        memcpy(&reponce->id,buffer+sizeof(char),IDLENGTH_INT*sizeof(uint32_t));
        reponce->addr_ip =fromAddr;



//Juste de l'affichage pour le debug
    if(DEBUG==1) {
        printf("Node reçue %s \n", getPipeFromId((int *) &reponce->id));
    }

        //On evite de mettre la node tout de suite pour le processuce de bootstrap
        //Si non elle renvois son propre ID vus que le progame la conais deja (et cest pas tres uttille)
        //Pour le find node le voisn est joute a la fin une vois que lon a tout envoye
        if(type!=MSG_FIND_NODE){
            addVoisin(from,reponce);
        }


        char display[16] = {0};
        inet_ntop(AF_INET, &fromAddr.sin_addr.s_addr, display, sizeof display);



        switch (type) {
            case MSG_PING:
                pong(from,reponce);
                break;
            case MSG_PONG:
                printf("message pong \n");
                break;
            case MSG_FIND_NODE:
                    receive_find_node(from,reponce,buffer);
                break;
            case MSG_FIND_NODE_REP:
                receive_closed_node(from,reponce,buffer);
                break;
            case MSG_PUBLISH_KEY:
                receive_publish_key(from,reponce,buffer);
                break;
            case MSG_FIND_VALUE:
                receive_find_value(from,reponce,buffer);
                break;
            case MSG_FIND_VALUE_REP:
                receive_find_value_rep(from,reponce,buffer);
                break;

            default:
                printf("Message inconnu\n");
        }
    if(buffer) {
       // free(&reponce);
        free(buffer);
    }


}
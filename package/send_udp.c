//
// Created by root on 5/21/20.
//
#include "send_udp.h"
#include "ping.h"
#include "find_node.h"
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;

void send_udp(Node *from, Node *to, char type, void *data, long size) {
    printf("send udp\n");
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
    sendto(from->sockfd, dest, lengthcopy,
           MSG_CONFIRM, (const struct sockaddr *) &to->addr_ip,
           sizeof(to->addr_ip));

    //on oublie pas de libre la zone emoire
    free(dest);

    printf("send udp ok to \n");
    printNode((struct Node *) to);
}


_Noreturn void receive_udp(Node *from) {

    //Nbr de donne maximale que le serveur UDP peux recevoire = 255 node + type + id sender
    int MAXDATA_UDP = 2*MAXRETURNNODE*(IDLENGTH_INT*sizeof(uint32_t)+sizeof(struct sockaddr_in))+sizeof(char)+IDLENGTH_INT*sizeof(uint32_t);

    printf("recefe udp \n");
    uint32_t id[IDLENGTH_INT];
    char type="a";
    struct sockaddr_in fromAddr;
    int len = sizeof(fromAddr);

    pthread_mutex_lock(&mutex);
int tmp = bind(from->sockfd, (const struct sockaddr *) &from->addr_ip,
               sizeof(from->addr_ip));
    // Bind the socket with the server address
    if ( tmp< 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }else{
        count++;
        printf("bind ok %d \n",count);
    }
    pthread_mutex_unlock(&mutex);
    printNode((struct Node *) from);
    while (1) {
        void *buffer = malloc(MAXDATA_UDP);
        int n = recvfrom(from->sockfd, buffer, MAXDATA_UDP,
                         MSG_WAITALL, (struct sockaddr *) &fromAddr,
                         &len);


        Node test ;

        Node * reponce = malloc(sizeof(Node));
        memcpy(&type,buffer,sizeof(char));
        memcpy(&reponce->id,buffer+sizeof(char),IDLENGTH_INT*sizeof(uint32_t));
        reponce->addr_ip =fromAddr;



//Juste de l'affichage pour le debug

        printf("Node recus %s \n", getPipeFromId((int *) &reponce->id));

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

                break;
            default:
                printf("Message incunus");
        }
    if(buffer) {
       // free(&reponce);
        free(buffer);
    }

    }
}
//
// Created by root on 6/12/20.
//

#include "find_value.h"
#include "node.h"
#include "send_udp.h"
#include "fichier.h"
#include "bdd.h"
#include <netinet/in.h>

void * find_value(Node * from,Node * to,int * hash){
    send_udp(from,to,MSG_FIND_VALUE,hash,IDLENGTH_SIZE);
}

//Procedure qui recois une une requte find value (savoir si la node possede bien les donne )
//Si
void * receive_find_value(Node * from,Node * container,void * buffer){
    uint32_t hash[IDLENGTH_INT];
    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(&hash,buffer+decalage,IDLENGTH_SIZE);

    Fichier * fichier = malloc(sizeof(fichier));
    Node * node = malloc(sizeof(Node));

    getfichier(from,hash,fichier,node);

    int size = sizeof(char)+ sizeof(Fichier)+sizeof(struct sockaddr_in);
    //Donne qui seron renvoyer
    void * data = calloc(1,size);

    //Si on a des donne (par defaut on dit que non)
    char hasData = 0;

//Si le fichier ou la node exite bien
    if(fichier!=0&&node!=0) {
        hasData = 1;
        decalage = 0;
        memcpy(data+decalage,&hasData,sizeof(Fichier));
        decalage+=1;
        memcpy(data+decalage,fichier,sizeof(Fichier));
        decalage+=sizeof(Fichier);
        memcpy(data+decalage,&node->addr_ip,sizeof(struct sockaddr_in));
        decalage+=sizeof(Fichier);

    }

    //on renvois la reponc en UDP

    send_udp(from,container,MSG_FIND_VALUE_REP,data,size);

}
/*
 * Possible pbr de secutire qui permtrai a nimporte qui de fair telecharge un fichier mais on a pas le temps pour sa.
 * Il faut verfie que les info voulus coreponde bien au fichier demende
 */
void * receive_find_value_rep(Node * from,Node * container,void * buffer){
    int decalage = sizeof(char)+IDLENGTH_SIZE;

    char hashData = 0;
    memcpy(&hashData,buffer+decalage,sizeof(char));
    decalage+=sizeof(char);

    if(hashData){
Fichier * f = malloc(sizeof(Fichier));
Node n ;

        memcpy(f,buffer+decalage,sizeof(Fichier));
        decalage+=sizeof(Fichier);
        memcpy(&n.addr_ip,buffer+decalage,sizeof(struct sockaddr_in));

        for (int i = 0; i <IDLENGTH_INT ; ++i) {
            n.id[i] =f->idnode[i];
        }

    }else{
        //Ne pas remove (cet pas du debug)
        printf("Nous n'avons pas pus trouve les donne corespondate a votre film");
    }


}

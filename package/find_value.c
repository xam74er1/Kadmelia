//
// Created by root on 6/12/20.
//

#include "find_value.h"
#include "node.h"
#include "send_udp.h"
#include "fichier.h"
#include "bdd.h"
#include "SendFileTCP.h"
#include "../utilitaires/hashFile.h"
#include "find_node.h"
#include <netinet/in.h>

void find_file(Node * from,char * fileName){
    uint32_t  * hashName = hashString(fileName);
    //on trouve la node la plus proche
    Node * proche = find_node(from,hashName);
    find_value(from,proche,hashName);
}

void * find_value(Node * from,Node * to,int * hash){
    if(DEBUG==1) {
        printf("find value du hash %s \n", getPipeFromId(hash));
    }
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

    char hasData =   getfichier(from,hash,fichier,node);

    int size = sizeof(char)+ sizeof(Fichier)+sizeof(struct sockaddr_in);
    //Donne qui seron renvoyer
    void * data ;
    data = malloc(size);

    //Si on a des donne (par defaut on dit que non)


//Si le fichier ou la node exite bien
    if(hasData) {
        decalage = 0;
        memcpy(data+decalage,&hasData,sizeof(char));
        decalage+=1;
        memcpy(data+decalage,fichier,sizeof(Fichier));
        decalage+=sizeof(Fichier);
        memcpy(data+decalage,&node->addr_ip,sizeof(struct sockaddr_in));
        decalage+=sizeof(Fichier);

    }else{
        decalage = 0;
        memcpy(data+decalage,&hasData,sizeof(char));
        decalage+=1;
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
        if(DEBUG==1) {
            printf("\033[0;32mclef trouve on commence le dl \n");
        }
        Fichier * f = malloc(sizeof(Fichier));
        Node n ;

        memcpy(f,buffer+decalage,sizeof(Fichier));
        decalage+=sizeof(Fichier);
        memcpy(&n.addr_ip,buffer+decalage,sizeof(struct sockaddr_in));

        for (int i = 0; i <IDLENGTH_INT ; ++i) {
            n.id[i] =f->idnode[i];
        }

        if(DEBUG==1) {
            printf("le fichier a telechage est %s avec une taille %d \n", f->nom, f->taille);
            printf("on tellecharge les donne sur la node : \n");
            printNode(&n);
        }
        requeste_file(from,&n,f->nom);

    }else{
        //Ne pas remove (cet pas du debug)
        printf("\033[1;31mNous n'avons pas pus trouve les donne corespondate a votre film \033[0m\n ");
    }


}

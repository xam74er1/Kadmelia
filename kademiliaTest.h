//
// Created by xam74 on 13/04/2020.
//

#ifndef GROUPE7_KADEMILIATEST_H
#define GROUPE7_KADEMILIATEST_H
#include <time.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilitaires/utilitaire.h"

#include <pthread.h>
#include <stdint.h>

#define IDLENGTH_INT 5 //Nombre de int qui compose un id (ici 5*32 = 160 bit)
#define NBVOISIN_MAX 3 //Nomre de voisin maximome corepond au k-bukkets
#define DIRECTORYTEST "nodespace" //Nom du dossie qui contien les test

/*
 * Lorsque lon envois un message on vas le prefie d'un id pour savoir de quelle type de message il s'agit
 * Cela permet par la suite d'avise
 * ex : si un message commence par un 0 on sais que on vas demedne id d'une node
 * je detaille cette partis dans les rceinve
 */
//Definition des id
#define  ASK_ID 0 //Si le message comemnce par 0 cest que lon demende id de la node
#define  ASK_ID_REP 1 // " 1 si on recois un 1 cest la reponce a id
#define ASK_VOISIN 2 // demende a la node d'envoye la liste de ses voisin
#define REP_VOISIN 3 // reponce a une demende de voisin
#define ASK_SEND_NODE 4 // demende la node la plus proche
#define REP_SEND_NODE 5 // renvois la node la plus proche

//Pseudo objet
/*
 *  Une node a pour but de centralise tout les donne .
 *  Elle est dans l'espris de cree un pesudo objet que on uttilisera
 * Elle comporte une adress ip , un port , son id , la liste de ses voisin et le nombre de voin quelle a.
 *
 * Elle est initialise avec avec ini node qui sert de constucteure
 */
typedef struct Node{
    long ipAddres;//Adrrse id
    int port;//Port
    uint32_t id[IDLENGTH_INT];//id de la node
    struct Node * voisin[NBVOISIN_MAX]; //list de mes voisin
    int nbVoisin; //nombre de voisin que jai actuellment
int * idRessu ;//Donne de transition pour les thread qui comminique ici , voir la partie  findClosedNeibourg

    int tabIndex;
}Node;

//Initiilse IP
void iniIp();

//Initlise le port
void iniPort();

//Constructeu de la node
void ini(Node * fromNode);

//INitilse id
iniID();

//Met un id a la node qui est juste un int , le reste est cmplet par des 0 .Cela sert a avoir un id de 5 int defini simpemnt (nottament pour la lecture humaine)
void setNodeIdSimple(Node *fromNode,int id);

//serter pour un id
void setNodeId(Node *fromNode,int id[IDLENGTH_INT]);
//Rajoute un voisin dans le tableau des node
void addVoisin(Node *original,Node *voisin);

//set index a la node
void setTabIndex(Node * node,int index);

// Gestion des PIPE

//Creation de fifo
void createFifo(Node *fromNode);
//Retoune un tring compose de lendrois ou ce troue la node . cela set a ecrire dans une pipe en ne coniassant que id de la node
char * getPipeFromId(int id[IDLENGTH_INT]);

//Envois une chaine de caratre a une node
/*
 *Input : Node a qui envoye un message , Message a envyer
 */
void send(Node * node , char str[80]);

//Zone qui socupe de recevoir les message envoye par les node
//Elle est nottament uttilise pour les theard
//Cest les oreille de notre node elle est cappable de repondre
void receive(Node * node );
/*
 * Trouve le voisin le plus proche (algo pour le find node )
 */
int find_node(Node * node,int *id);
//Renvois la liste de tout les voidsin de la node
/*Input : Node qui possede les voisin , dest : chemin de la pipe
 *
 */
void sendVoisin(Node * node,int * idDest);
//Metode apple lorsque un voisn est recus
void reciveVoisin(Node * node , int pipe);
//Envois une demende pour savoir tout les voisin .
/*
 * Input : Node qui demende les voidin . Dest : chemin de la pipe
 */
void *askVoisin(Node *node,char *dest);
/*
 * Demende id a la node
 * Input : Node en question , Dest : chemin de la node a qui on demende son id
 * Elle sert princiapllment pour les test
 */
        void *askId(Node *node,char *dest);
        /*
         * Aissai pour envoye une caine de caratere a une node
         */
void * testSend(Node *node,char *dest,char *str);
/*
 * Renvois la node la plus proche de la valleur au sesn xditance
 */
Node * nodeLaPlusProche(Node * node,int * valleur);
/*
 * Meme chose que recinve .
 * Cest ici que je test les differente fonction de recust de message
 *
 */
void *testReceive(Node * node);

/*
 * Envois une demende pour savoir quelle est la node la plus proche
 * @Input node qui fait la demende , adresse de la destination , valleur a demende
 */
void send_find_node(Node *node,char *dest,int * value);

/*
 * Action lors que lon demende de recevoir une node
 *
 */
void receive_send_node(Node * node,int pipe);

#endif //GROUPE7_KADEMILIATEST_H

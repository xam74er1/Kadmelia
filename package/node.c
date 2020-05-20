#include "node.h"

void ini(Node *node) {
iniID(node);
    node->nbVoisin=0;
    iniID(node);
    iniAddr(node);
}

//inilise id
int iniID(Node * node) {

    for (int i = 0; i < IDLENGTH_INT; ++i) {
        node->id[i] = rand();
    }
}

//Set id d'une node
void setNodeId(Node *fromNode, int id[IDLENGTH_INT]){
    for (int i = 0; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = id[i];
    }
}


//Met une un id simple au node , uttilise pour les test
void setNodeIdSimple(Node *fromNode, int id){
    fromNode->id[0] =id;
    for (int i = 1; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = 0;
    }
}

//Ajoute un voisin a une node
void addVoisin(Node *original, Node *voisin){
    int pos = original->nbVoisin;
    original->voisin[pos] = voisin;
    original->nbVoisin++;
}

void iniAddr(Node * node){
    node->addr_ip.sin_family    = AF_INET; // IPv4
    node->addr_ip.sin_addr.s_addr = INADDR_ANY;
    node->addr_ip.sin_port = 0; //On le set a 0 pour lui dire de prendre un port par defaut pour la communication
}
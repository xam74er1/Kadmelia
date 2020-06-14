//
// Created by bng on 12/06/2020.
//

#include "SendFileTCP.h"
#include "bdd.h"

void send_tcp_file(Node * from,Node * to , char * path){
    //int sendto(int socket, char *buffer, int length, int flags,struct sockaddr *address, int address_len);
    //ssize_t send(int s, const void *buf, size_t len, int flags);
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *f=NULL;
    f=fopen(path,"r");


    if (f != NULL) {
        while ((bytesRead = fread(buff, 1, Nmax, f)) > 0) {
            write(to->sock_tcp, buff, Nmax);
        }
    }
}
//int accept(int sockfd, struct sockaddr *adresse, socklen_t *longueur);
void write_file(Node *from, int confd,char *path){
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *fp=NULL;
    fp=fopen(path,"wb");
    int retread;
    int count = 0;


    while ( (retread=read(confd,buff,Nmax)) > 0){
        fwrite(buff,retread,1,fp);
        count++;
    }
    printf("the file was received successfully \n");
    printf("the new file created is add1.txt \n");
    close(fp);

    if(count!=0){
        printf("Fichier recus ");

    }else{
        printf("Aucun fichier recus ");
    }


}

void accecpt_to_send_file(Node * from){
    //on accepte la conncetion
    int confd=accept(from->sock_tcp,(SA*)&from->addr_ip,&from->addr_ip);
    int retread;

 char * buff[255];

    if(confd==-1){
        perror("Erreur lors de la connextion... ");
     //   exit(1);
    }else{

        //on as lire les donne envoyer
        retread=read(confd,buff,255);
        //si on a bien lus les donne
        if(retread!=0){
            char * path = getfilepath(from,buff);
            //on verifie que le chemain existe bien
            if(path!=0){
                write_file(from,confd,path);
            }else{
                //Si non on ferme la connextion
                close(from->sock_tcp);
            }

        }
    }

}

void requeste_file(Node * from,Node * to,char * fileName){

    //on commence par ce connexte au pair qui possede la donne
    int connexion=connect(from->sock_tcp,(SA*)&to->addr_ip,sizeof(to->addr_ip));

    if(connexion==-1){
        perror("Erreur de connexion...");
    }

    int size = strlen(fileName)+1;
//Je luis envois le chemin
    write(to->sock_tcp, fileName, size);

    char * loc = getPipeFromId(from->id);

    char * tmp = concat(loc,"/");

    char * path = concat(tmp,fileName);

    write_file(from,from->sock_tcp,path);



}
//
// Created by bng on 12/06/2020.
//

#include "SendFileTCP.h"
#include "bdd.h"
#include "../utilitaires/console_color.h"

void send_tcp_file(Node * from,int sock, char * path){
    if(DEBUG==1) {
        printf("Send tcp file\n");
    }
    //int sendto(int socket, char *buffer, int length, int flags,struct sockaddr *address, int address_len);
    //ssize_t send(int s, const void *buf, size_t len, int flags);
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *f=NULL;
    f=fopen(path,"rb");

    if (f != NULL) {
        while ((bytesRead = fread(buff, 1, Nmax, f)) > 0) {
            write(sock, buff, bytesRead);
        }
    }
    close(sock);
    fclose(f);
}
//int accept(int sockfd, struct sockaddr *adresse, socklen_t *longueur);
void write_file(Node *from, int sock, char *path){
    if(DEBUG==1) {
        printf("\nwrite file\n");
    }

    clr_Magenta();
    printf("Debut de l'ecriture du fichier\n");
    clr_reset();

    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *fp=NULL;
    fp=fopen(path,"wb");
    int retread;
    int count = 0;


    while ((retread=read(sock, buff, Nmax)) > 0){
        if(DEBUG==1) {
            printf("%d data recus \n", retread);
        }

      int nbw =  fwrite(buff,retread,1,fp);
        if(DEBUG==1) {
            printf("nbw %d\n", nbw);
        }
        count++;
    }

    fclose(fp);
close(sock);



    if(count!=0){
        clr_green();
        printf("Fichier reçu , il est disponible dans %s \n",path);
        clr_reset();

    }else{
        clr_Red();
        printf("Aucun fichier reçu \n");
        clr_reset();
    }


}

void accecpt_to_send_file(Node * from){
    if(DEBUG==1) {
        printf("accept send file\n");
    }
    struct sockaddr_in cli;
    int length = sizeof(from->addr_ip);
    //on accepte la conncetion
    int confd=accept(from->sock_tcp,(SA*)&cli,&length);
    int retread;

 char * buff[255];

    if(confd==-1){
        perror("Erreur lors de la connexion B... \n");
     //   exit(1);
    }else{
        if(DEBUG==1) {
            printf("connexion ok \n");
        }
        //on as lire les donne envoyer
        retread=read(confd,buff,255);
                if(DEBUG==1) {
                    printf("data reçue\n");
                }
        //si on a bien lus les donne
        if(retread!=0){
            char * str ;

            strcpy(str,buff);

            if(DEBUG==1) {
                printf("fichier voulus %s \n",str);
            }
            char * path = getfilepath(from,buff);
            //on verifie que le chemain existe bien
            if(path!=0){
            send_tcp_file(from,confd,path);
            }else{
                //Si non on ferme la connextion
                close(from->sock_tcp);
            }

        }
    }

}

void requeste_file(Node * from,Node * to,char * fileName){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(DEBUG==1) {
        printf("requete file\n");
    }
    //on commence par ce connexte au pair qui possede la donne
    int connexion=connect(sockfd,&to->addr_ip,sizeof(to->addr_ip));

    if(connexion==-1){
        perror("Erreur de connexion...\n");
    }else {
        if(DEBUG==1) {
            printf("connection success : file request\n");
        }

        sleep(1);
        int size = strlen(fileName) + 1;
//Je luis envois le chemin
        if(DEBUG==1) {
            printf("end sleep\n");
        }

    write(sockfd, fileName, size);


        if(DEBUG==1) {
            printf("tcp envoyé\n");
        }
        char *loc = getPipeFromId(from->id);

        char *tmp = concat(loc, "/");

        char *path = concat(tmp, fileName);
        sleep(1);
        write_file(from, sockfd, path);

    }

}

void testTCP(Node * from,Node * to){
    sleep(0.1);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(DEBUG) {
        printf("requête file\n");
    }
    printNode(to);
    //on commence par ce connexte au pair qui possede la donne
    int connexion=connect(sockfd,&to->addr_ip,sizeof(to->addr_ip));

    if(connexion==-1) {
        perror("Erreur de connexion A...\n");
    }else{

        printf("success\n");
        char * str = "hello world";
        int size = strlen(str)+1;
        printf("beforewrite\n");
        sleep(0.1);
        write(sockfd, str, size);
        printf("ned \n");
     //   close(sockfd);
    }
}
#define Nbuff 255
void testRecoisTCP(Node * from){
    unsigned char buffer[Nbuff];
    int retread;
    struct sockaddr_in servaddr,cliaddr;
    int client,connfd;
    client=sizeof(cliaddr);
    connfd=accept(from->sock_tcp,(SA*)&cliaddr,&client);
    retread=read(connfd,buffer,Nbuff);
    printf("nb bit read : %d\n",retread);
}
//
// Created by bng on 12/06/2020.
//

#include "SendFileTCP.h"

void send_tcp_file(Node * from,Node * to , char * path){
    //int sendto(int socket, char *buffer, int length, int flags,struct sockaddr *address, int address_len);
    //ssize_t send(int s, const void *buf, size_t len, int flags);
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *f=NULL;
    f=fopen(path,"r");
    int connexion=connect(from->sock_tcp,(SA*)&to->addr_ip,sizeof(to->addr_ip));
    if(connexion==-1){
        perror("Erreur de connexion...");
    }
    if (f != NULL) {
        while ((bytesRead = fread(buff, 1, Nmax, f)) > 0) {
            write(to->sock_tcp, buff, Nmax);
        }
    }
}
//int accept(int sockfd, struct sockaddr *adresse, socklen_t *longueur);
void write_file(Node *from, char *path){
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *fp=NULL;
    fp=fopen(path,"wb");
    int retread;
    int confd=accept(from->sock_tcp,(SA*)&from->addr_ip,&from->addr_ip);

    if(confd==-1){
        perror("Erreur... ");
        exit(1);
    }
    while ( (retread=read(confd,buff,Nmax)) > 0){
        fwrite(buff,retread,1,fp);
    }
    printf("the file was received successfully \n");
    printf("the new file created is add1.txt \n");
    close(fp);

}
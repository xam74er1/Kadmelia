//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include <getopt.h>
#include "string.h"
#include "package/node.h"
#include "package/find_node.h"
#include "event/lisent.h"
#include "utilitaires/console_color.h"
#include "package/bdd.h"
#include "package/publish_key.h"
#include "package/find_value.h"
#include <stdlib.h>
#include <stdbool.h>

char ** splitStr(char * str,char * delimiteur){
    char ** res = calloc(255,20);

    int i =0;
    char * strToken = strtok ( str, delimiteur );
    while ( strToken != NULL ) {
        res[i] =strToken;
        strToken = strtok ( NULL, delimiteur );
        i++;
    }

    return res;
}

char * lastStr(char * str,char *delimiteur){
    char * res = malloc(255);

    char * strToken = strtok ( str, delimiteur );
    while ( strToken != NULL ) {
        res =strToken;
        strToken = strtok ( NULL, delimiteur );
    }

    return res;
}

/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main(int argc, char **argv) {
    int c;
    char str [255];
    int nbChar = 0;
    int count = 0;
    bool isEnd = false;
    srand(time(NULL));   // Initialization, should only be called once.

    Node node;
//Premiere connetion a un voisin
    Node * firstConn = calloc(sizeof(node),1);


    ini(&node);


    ///////////////
    ///Arguments///
    ///////////////


    while (1)
    {
        static struct option long_options[] =
                {
                        {"ip",  required_argument, 0, 'i'},
                        {"port",  required_argument, 0, 'p'},
                        {"querryPort",  optional_argument, 0, 'q'},
                        {"myip",  optional_argument, 0, 'm'},
                        {"simpleid",  optional_argument, 0, 's'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "i:p:q:m:s:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 'i':
                firstConn->addr_ip.sin_addr.s_addr =inet_addr(optarg);
                count++;
                break;

            case 'p':
                firstConn->addr_ip.sin_port = htons(atoi(optarg));
                count++;
                break;
            case 'q':
                node.addr_ip.sin_port = htons(atoi(optarg));

                break;

            case 'm':
                node.addr_ip.sin_addr.s_addr =inet_addr(optarg);

                break;

            case 's':
                    iniIDSimple(&node,atoi(optarg));
                break;

            default:
            //   fprintf(stderr,"Argument non reconus %s\n",optarg);
                break;
        }


    }



    char cpy[255] ;
    char otherPart[255];
    pthread_t t1;
    pthread_create(&t1, NULL, (void *(*)(void *)) receive_paquette, &node);
    sleep(2);

    //si on a recus au moin un argument pour ce connecte
    if(count>0) {
        //on envois une information pour recupere une node , cela nous permet d'ajoute l'id de la node connus au bucket
        //on envoie un paquet unique
        send_find_node(&node, firstConn, node.id);
        //Processuce d'insertion dans l'arbre
        find_node(&node,node.id);
    }else{
clr_Red();
printf("Attention vus n'est connecte a aucun noeud du reseau , il est possbile que le programe ne marche pas dans que vous n'avez pas ete contacte par une node");
clr_reset();
    }
        while(!isEnd){
            sleep(0.1);
            clr_blue();
            printf("Selectione votre action (add | find | exit ) : \n");
            clr_reset();
            scanf(" %254[^\n]%n", str, &nbChar);

            strcpy(cpy,str);

          char ** result =  splitStr(str," ");
    char * firtEllem = result[0];
    int length = strlen(cpy);
    int flength = strlen(firtEllem)+1;
    int sublength = length-flength+1;//on enlve l'espace et le caratre de fin

    memcpy(otherPart,cpy+flength,sublength);



            if(strcmp(firtEllem, "add") == 0){
printf(" add + %s \n",otherPart);
                char * path = realpath(otherPart,NULL);

                if(path!=NULL) {
                    char *fname = lastStr(otherPart, "/\\");

                    printf("file name %s , reald path %s \n", fname, path);
                     setlocalfile(&node,fname,path);
                       publish_key(&node,fname);

                }else{
                    clr_Red();
                    printf("Impossible de trouve le fichier %s ",otherPart);
                    clr_reset();
                }
            }else if(strcmp(firtEllem, "find") == 0){
                find_file(&node,otherPart);
            }else if(strcmp(firtEllem, "exit") == 0){
                pthread_cancel(t1);
                isEnd =true;
                break;
            }else{
                clr_Red();
                printf("Argument \"%s\" invalide \n",firtEllem);
                clr_reset();

            }

            free(result);
        }



    pthread_join(t1,NULL);
    return 0;
}

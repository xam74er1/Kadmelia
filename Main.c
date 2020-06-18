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


char **splitStr(char *str, char *delimiteur) {
    char **res = calloc(255, 20);

    int i = 0;
    char *strToken = strtok(str, delimiteur);
    while (strToken != NULL) {
        res[i] = strToken;
        strToken = strtok(NULL, delimiteur);
        i++;
    }

    return res;
}

char *lastStr(char *str, char *delimiteur) {
    char *res = malloc(255);

    char *strToken = strtok(str, delimiteur);
    while (strToken != NULL) {
        res = strToken;
        strToken = strtok(NULL, delimiteur);
    }

    return res;
}

/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main(int argc, char **argv) {
    int c;
    int port = -1;
    char str[255];
    int nbChar = 0;
    int count = 0;
    bool isEnd = false;
    srand(time(NULL));   // Initialization, should only be called once.

    Node node;
//Premiere connetion a un voisin
    Node *firstConn = calloc(sizeof(node), 1);


    ini(&node);


    ///////////////
    ///Arguments///
    ///////////////


    while (1) {
        static struct option long_options[] =
                {
                        {"ip",         required_argument, 0, 'i'},
                        {"port",       required_argument, 0, 'p'},
                        {"querryPort", optional_argument, 0, 'q'},
                        {"myip",       optional_argument, 0, 'm'},
                        {"simpleid",   optional_argument, 0, 's'},
                        {0, 0,                            0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "i:p:q:m:s:",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
            case 'i':
                firstConn->addr_ip.sin_addr.s_addr = inet_addr(optarg);
                count++;
                break;

            case 'p':
                firstConn->addr_ip.sin_port = htons(atoi(optarg));
                count++;
                break;
            case 'q':
                port = atoi(optarg);


                break;

            case 'm':
                node.addr_ip.sin_addr.s_addr = inet_addr(optarg);

                break;

            case 's':
                iniIDSimple(&node, atoi(optarg));
                break;

            default:
                //   fprintf(stderr,"Argument non reconus %s\n",optarg);
                break;
        }


    }


    if (port != -1) {
        node.addr_ip.sin_port = htons(port);
    }

    char cpy[255];
    char otherPart[255];
    pthread_t t1;
    pthread_create(&t1, NULL, (void *(*)(void *)) receive_paquette, &node);
    sleep(2);

    //si on a recus au moin un argument pour ce connecte
    if (count > 0) {
        //on envois une information pour recupere une node , cela nous permet d'ajoute l'id de la node connus au bucket
        //on envoie un paquet unique
        send_find_node(&node, firstConn, node.id);
        //Processuce d'insertion dans l'arbre
        find_node(&node, node.id);
    } else {
        clr_Red();
        printf("Attention vous n'êtes connecté à aucun noeud réseau. Il est possible que le programme ne marche pas tant que vous n'avez pas été contacté par une node\n");
        clr_reset();
    }

    clr_Yellow();
    printf("Votre node a l'id : %s \n",getPipeFromId(node.id));
    printNode(&node);

    clr_reset();

    while (!isEnd) {
        sleep(0.1);
        clr_blue();
        printf("\nSelectionner votre action (add | find | exit ) : \n");
        clr_reset();
        scanf(" %254[^\n]%n", str, &nbChar);

        strcpy(cpy, str);

        char **result = splitStr(str, " ");
        char *firtEllem = result[0];
        int length = strlen(cpy);
        int flength = strlen(firtEllem) + 1;
        int sublength = length - flength + 1;//on enlve l'espace et le caratre de fin

        memcpy(otherPart, cpy + flength, sublength);


        if (strcmp(firtEllem, "add") == 0) {

            char *path = realpath(otherPart, NULL);

            if (path != NULL) {
                char *fname = lastStr(otherPart, "/\\");


                setlocalfile(&node, fname, path);
                publish_key(&node, fname);

            } else {
                clr_Red();
                printf("Impossible de trouver le fichier %s \n\n", otherPart);
                clr_reset();
            }
        } else if (strcmp(firtEllem, "find") == 0) {
            find_file(&node, otherPart);
        } else if (strcmp(firtEllem, "exit") == 0) {
            pthread_cancel(t1);
            isEnd = true;
            break;
        } else {
            clr_Red();
            printf("Argument \"%s\" est invalide \n", firtEllem);
            clr_reset();

        }

        free(result);
    }


    pthread_join(t1, NULL);
    return 0;
}

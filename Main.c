//
// Created by xam74 on 13/04/2020.
//

#include <stdio.h>
#include <getopt.h>
#include "string.h"
#include "package/node.h"
#include "package/find_node.h"
#include "event/lisent.h"
#include <stdlib.h>



/*
 * Cette fonction me permet de fair mes test , elle est pas uen fonction propre
 *
 */
int main(int argc, char **argv) {
    int c;
    int count = 0;
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
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "i:p:q:m:",
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

            default:
            //   fprintf(stderr,"Argument non reconus %s\n",optarg);
                break;
        }


    }




    pthread_t t1;
    pthread_create(&t1, NULL, (void *(*)(void *)) receive_paquette, &node);
    sleep(2);

    if(count>0) {

      //  addVoisin(&node,&firstConn);

        send_find_node(&node, firstConn, node.id);
        printBukket(&node);
    }else{
        printf("c is null \n");
    }

    pthread_join(t1,NULL);
    return 0;
}

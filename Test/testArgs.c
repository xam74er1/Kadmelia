#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int
main (int argc, char **argv)
{
    int c;

    while (1)
    {
        static struct option long_options[] =
                {
                        {"ip",  required_argument, 0, 'i'},
                        {"port",  required_argument, 0, 'p'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "i:p:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 'i':
                printf ("option -i: `%s'\n", optarg);
                break;

            case 'p':
                printf ("option -p: `%s'\n", optarg);
                break;

            default:
                abort ();
        }
    }


    exit (0);
}
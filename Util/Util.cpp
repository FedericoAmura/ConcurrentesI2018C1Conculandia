#include <cstdlib>
#include <getopt.h>

#include "./Util.h"

using namespace std;

t_parametros Util::tomarParametros(int argc,char* argv[]) {
    int c;
    bool pendingParams = true;
    t_parametros params;
    params.cantVentanillas = 0;
    params.cantSellos = 0;

    while (pendingParams)
    {
        static struct option long_options[] =
            {
                    {"ventanillas",  required_argument, 0, 'v'},
                    {"sellos",  required_argument, 0, 's'},
                    {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "v:s:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {

            case 'v':
                params.cantVentanillas = atoi(optarg);
                break;
            case 's':
                params.cantSellos = atoi(optarg);
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                pendingParams = false;
        }
    }

    return params;
}
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
    params.debug = false;

    while (pendingParams)
    {
        static struct option long_options[] =
            {
                    {"ventanillas",  required_argument, nullptr, 'v'},
                    {"sellos",  required_argument, nullptr, 's'},
                    {"debug",  no_argument, nullptr, 'd'},
                    {0, 0, 0, 0}
            };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "v:s:d",
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
            case 'd':
                params.debug = true;
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

string Util::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)  {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool Util::esNumerico(const string& str){

    int len = str.length();
    for (int i = 0; i < len; i++) {
        if (int(str[i])<48 || int(str[i]) > 57) {
            return false;
        }
    }

    return true;
}
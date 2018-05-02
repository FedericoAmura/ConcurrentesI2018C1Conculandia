#ifndef CONCULANDIA_UTIL_H
#define CONCULANDIA_UTIL_H

#include <string>
using namespace std;
typedef struct parametros {
    int cantVentanillas;
    int cantSellos;
    bool debug;
} t_parametros;

class Util {

public:
    static t_parametros tomarParametros(int argc,char* argv[]);

    static string trim(const string& str);

    static bool esNumerico(const string& str);

    static int validarParametros(t_parametros parametros);

    static string obtenerMensajeError(int codigoMensaje);

};


#endif //CONCULANDIA_UTIL_H

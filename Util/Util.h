#ifndef CONCULANDIA_UTIL_H
#define CONCULANDIA_UTIL_H

typedef struct parametros {
    int cantVentanillas;
    int cantSellos;
} t_parametros;

class Util {

public:
    static t_parametros tomarParametros(int argc,char* argv[]);

};


#endif //CONCULANDIA_UTIL_H

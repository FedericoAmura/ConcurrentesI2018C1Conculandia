#ifndef CONCULANDIA_PRINTER_H
#define CONCULANDIA_PRINTER_H

#include "../ProcesoHijo/ProcesoHijo.h"

using namespace std;

class Printer : public ProcesoHijo {

public:
    explicit Printer(Logger& logger);
    ~Printer();

    pid_t ejecutar();
};


#endif // CONCULANDIA_PRINTER_H

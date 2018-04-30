#ifndef CONCULANDIA_PRINTER_H
#define CONCULANDIA_PRINTER_H

#include "../ProcesoHijo/ProcesoHijo.h"

using namespace std;

class Printer : public ProcesoHijo {

public:
    explicit Printer(Logger& logger);
    ~Printer() override;

    pid_t ejecutar() override;
};


#endif // CONCULANDIA_PRINTER_H

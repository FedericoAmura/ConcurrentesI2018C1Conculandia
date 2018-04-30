#ifndef TP1_CONCULANDIA_VENTANILLA_H
#define TP1_CONCULANDIA_VENTANILLA_H

#include "../Fifos/FifoLectura.h"
#include "../PortaSellos/PortaSellos.h"
#include "../ProcesoHijo/ProcesoHijo.h"

class Ventanilla : public ProcesoHijo {

public:
    explicit Ventanilla(Logger& logger, FifoLectura& canalLectura, PortaSellos& portaSellos);
    ~Ventanilla() override;

    pid_t ejecutar() override;
    ssize_t leerSiguientePersona(char *buffer);

private:
    FifoLectura canalLectura;
    LockFile lockExclusivo;
    PortaSellos portaSellos;

};

#endif //TP1_CONCULANDIA_VENTANILLA_H

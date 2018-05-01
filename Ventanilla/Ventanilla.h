#ifndef TP1_CONCULANDIA_VENTANILLA_H
#define TP1_CONCULANDIA_VENTANILLA_H

#include "../Fifos/FifoLectura.h"
#include "../PortaSellos/PortaSellos.h"
#include "../ProcesoHijo/ProcesoHijo.h"
#include "../ContadorPersonas/ContadorPersonas.h"

class Ventanilla : public ProcesoHijo {

public:
    Ventanilla(Logger& logger, FifoLectura& canalLectura, PortaSellos& portaSellos);
    ~Ventanilla() override;

    int getFileDescriptor();
    pid_t ejecutar() override;
    ssize_t leerSiguientePersona(char *buffer);

private:
    FifoLectura canalLectura;
    LockFile lockExclusivo;
    PortaSellos portaSellos;
    ContadorPersonas contadorPersonas;

    void iniciarAtencion();

};

#endif //TP1_CONCULANDIA_VENTANILLA_H

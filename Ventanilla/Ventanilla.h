#ifndef TP1_CONCULANDIA_VENTANILLA_H
#define TP1_CONCULANDIA_VENTANILLA_H

#include "../Fifos/FifoLectura.h"
#include "../PortaSellos/PortaSellos.h"
#include "../ProcesoHijo/ProcesoHijo.h"
#include "../ContadorPersonas/ContadorPersonas.h"
#include "../Lock/LockReadFile.h"

class Ventanilla : public ProcesoHijo {

public:
    Ventanilla(Logger& logger, FifoLectura& canalLectura, PortaSellos& portaSellos);
    ~Ventanilla() override;

    int getFileDescriptor();
    pid_t ejecutar() override;

private:
    FifoLectura canalLectura;
    LockFile lockExclusivo;
    PortaSellos portaSellos;
    ContadorPersonas contadorPersonas;

    void iniciarAtencion();
    bool examinar(Persona persona);
    void noIngresa(Persona persona);
    Persona leerPersona(char* buffer);

    bool buscarRiesgo(string riesgo);

    void ingresa(Persona persona);
};

#endif //TP1_CONCULANDIA_VENTANILLA_H

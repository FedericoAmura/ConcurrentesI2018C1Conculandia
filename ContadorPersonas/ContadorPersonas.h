#ifndef ADUANACONCULANDIA_CONTADORPERSONAS_H
#define ADUANACONCULANDIA_CONTADORPERSONAS_H

#include "../Lock/LockFile.h"
#include "../MemoriaCompartida/MemoriaCompartida.h"

typedef struct {
    int extranjerosDeportados;
    int extranjerosIngresados;
    int residentesIngresados;
    int residentesOficinaPolicia;
} contadorPersonasStruct;

class ContadorPersonas {

public:
    void inicializar();
    int getFileDescriptor();
    void liberarMemoria();

    contadorPersonasStruct getContadores();
    void agregarExtranjeroDeportado();
    void agregarExtranjeroIngresado();
    void agregarResidenteIngresado();
    void agregarResidenteOficinaPolicia();

    ContadorPersonas();
    ~ContadorPersonas();

private:
    LockFile lock;
    MemoriaCompartida<contadorPersonasStruct> contador;

};


#endif //ADUANACONCULANDIA_CONTADORPERSONAS_H

//
// Created by lucas on 30/04/18.
//

#ifndef ADUANACONCULANDIA_CONTADORPERSONAS_H
#define ADUANACONCULANDIA_CONTADORPERSONAS_H


#include "../MemoriaCompartida/MemoriaCompartida.h"
#include "../Lock/LockFile.h"

typedef struct {
    int extranjerosDeportados;
    int extranjerosIngresados;
    int residentesIngresados;
    int residentesOficinaPolicia;
} contadorPersonasStruct;

class ContadorPersonas {
    private:
        LockFile lock;
        MemoriaCompartida<contadorPersonasStruct> contador;
    public:
        ContadorPersonas();
        void inicializar();
        int getFileDescriptor();
        contadorPersonasStruct getContadores();
        void agregarExtranjeroDeportado();
        void agregarExtranjeroIngresado();
        void agregarResidenteIngresado();
        void agregarResidenteOficinaPolicia();
        ~ContadorPersonas();
};


#endif //ADUANACONCULANDIA_CONTADORPERSONAS_H

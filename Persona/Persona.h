#ifndef TP1_CONCULANDIA_PERSONA_H
#define TP1_CONCULANDIA_PERSONA_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include "../Util/Util.h"

class Persona {

public:
    static int TAMANIO_SERIALIZADO;

    Persona();
    explicit Persona(char * buffer);
    Persona(int tipoPersona, int numeroDocumento, string caracteristica);

    string serializar();
    void deserializar(const char * buffer);

    int getTipoPersona() const;
    void setTipoPersona(int tipoPersona);

    int getNumeroDocumento() const;
    void setNumeroDocumento(int numeroDocumento);

    string getCaracteristica();
    void setCaracteristica(const string &caracteristica);

private:
    int tipoPersona;
    int numeroDocumento;
    string caracteristica;

};

#endif //TP1_CONCULANDIA_PERSONA_H

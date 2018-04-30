//
// Created by nestor on 22/04/18.
//

#ifndef TP1_CONCULANDIA_PERSONA_H
#define TP1_CONCULANDIA_PERSONA_H

#include <iostream>
#include <string>

using namespace std;

class Persona {
private:
    int tipoPersona;
    int numeroDocumento;
    string caracteristica;

public:

    Persona();

    Persona(char * buffer);

    Persona(int tipoPersona, int numeroDocumento);

    static int TAMANIO_SERIALIZADO;

    const void * serializar();

    void deserializar(const char * buffer);


    int getTipoPersona() const;

    void setTipoPersona(int tipoPersona);

    int getNumeroDocumento() const;

    void setNumeroDocumento(int numeroDocumento);

    const string &getCaracteristica() const;

    void setCaracteristica(const string &caracteristica);
};


#endif //TP1_CONCULANDIA_PERSONA_H

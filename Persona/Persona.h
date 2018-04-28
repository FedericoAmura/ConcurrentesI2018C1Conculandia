//
// Created by nestor on 22/04/18.
//

#ifndef TP1_CONCULANDIA_PERSONA_H
#define TP1_CONCULANDIA_PERSONA_H


class Persona {
private:
    int tipoPersona;
    int numeroDocumento;

public:

    Persona();

    Persona(int tipoPersona, int numeroDocumento);

    static int TAMANIO_SERIALIZADO;

    const void * serializar();

    void deserializar(const char * buffer);


    int getTipoPersona() const;

    void setTipoPersona(int tipoPersona);

    int getNumeroDocumento() const;

    void setNumeroDocumento(int numeroDocumento);


};


#endif //TP1_CONCULANDIA_PERSONA_H

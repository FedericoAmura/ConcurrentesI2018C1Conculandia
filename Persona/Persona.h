#ifndef TP1_CONCULANDIA_PERSONA_H
#define TP1_CONCULANDIA_PERSONA_H

class Persona {

public:
    static int TAMANIO_SERIALIZADO;

    Persona();
    explicit Persona(char * buffer);
    Persona(int tipoPersona, int numeroDocumento);

    const void* serializar();
    void deserializar(const char * buffer);

    int getTipoPersona() const;
    void setTipoPersona(int tipoPersona);

    int getNumeroDocumento() const;
    void setNumeroDocumento(int numeroDocumento);

private:
    int tipoPersona;
    int numeroDocumento;

};

#endif //TP1_CONCULANDIA_PERSONA_H

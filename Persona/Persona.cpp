#include <iomanip>
#include <iostream>
#include <sstream>

#include "./Persona.h"

using namespace std;

int Persona::TAMANIO_SERIALIZADO = 60;

const void* Persona::serializar() {
    stringstream serializado;
    serializado << setw(4) << this->getTipoPersona() << setw(11) << this->getNumeroDocumento()<< setw(45)<<this->getCaracteristica();
    return static_cast<const void*>(serializado.str().c_str());
}

void Persona::deserializar(const char * buffer) {
    string persona = buffer;
    this->setTipoPersona(atoi(persona.substr(0,4).c_str()));
    this->setNumeroDocumento(atoi(persona.substr(4,11).c_str()));
    this->setCaracteristica(persona.substr(11,45).c_str());
}

int Persona::getTipoPersona() const {
    return tipoPersona;
}

void Persona::setTipoPersona(int tipoPersona) {
    this->tipoPersona = tipoPersona;
}

int Persona::getNumeroDocumento() const {
    return numeroDocumento;
}

void Persona::setNumeroDocumento(int numeroDocumento) {
    this->numeroDocumento = numeroDocumento;
}

Persona::Persona(int tipoPersona, int numeroDocumento, char * caracteristica) : tipoPersona(tipoPersona), numeroDocumento(numeroDocumento), caracteristica(caracteristica) {}
Persona::Persona(char * buffer) {
    deserializar(buffer);
}

const string &Persona::getCaracteristica() const {
    return caracteristica;
}

void Persona::setCaracteristica(const string &caracteristica) {
    Persona::caracteristica = caracteristica;
}

Persona::Persona() = default;

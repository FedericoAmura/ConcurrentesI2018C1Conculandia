//
// Created by nestor on 22/04/18.
//

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Persona.h"

using namespace std;

int Persona::TAMANIO_SERIALIZADO = 15;

const void* Persona::serializar() {
    stringstream serializado;
    serializado << setw(4) << this->getTipoPersona() << setw(11) << this->getNumeroDocumento();
    return static_cast<const void*>(serializado.str().c_str());
}

void Persona::deserializar(const char * buffer) {
    string persona = buffer;
    this->setTipoPersona(atoi(persona.substr(0,4).c_str()));
    this->setNumeroDocumento(atoi(persona.substr(4,11).c_str()));
}

int Persona::getTipoPersona() const {
    return tipoPersona;
}

void Persona::setTipoPersona(int tipoPersona) {
    Persona::tipoPersona = tipoPersona;
}

int Persona::getNumeroDocumento() const {
    return numeroDocumento;
}

void Persona::setNumeroDocumento(int numeroDocumento) {
    Persona::numeroDocumento = numeroDocumento;
}

Persona::Persona(int tipoPersona, int numeroDocumento) : tipoPersona(tipoPersona), numeroDocumento(numeroDocumento) {}
Persona::Persona(char * buffer) {
    deserializar(buffer);
}

Persona::Persona() = default;

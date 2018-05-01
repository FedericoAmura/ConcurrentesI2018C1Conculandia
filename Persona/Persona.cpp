#include <iomanip>
#include <iostream>
#include <sstream>

#include "./Persona.h"

using namespace std;

int Persona::TAMANIO_SERIALIZADO = 115;

string Persona::serializar() {
    stringstream serializado;
    serializado << setw(4) << this->getTipoPersona() << setw(11) << this->getNumeroDocumento()<<setw(100)<<this->getCaracteristica();
    return serializado.str();
}

void Persona::deserializar(const char * buffer) {
    string persona = buffer;
    this->setTipoPersona(atoi(persona.substr(0,4).c_str()));
    this->setNumeroDocumento(atoi(persona.substr(4,11).c_str()));
    this->setCaracteristica(Util::trim(persona.substr(15,100)));

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

Persona::Persona(int tipoPersona, int numeroDocumento, string caracteristica) : tipoPersona(tipoPersona), numeroDocumento(numeroDocumento), caracteristica(caracteristica) {}
Persona::Persona(char * buffer) {
    deserializar(buffer);
}

string Persona::getCaracteristica() {
    return caracteristica;
}

void Persona::setCaracteristica(const string &caracteristica) {
    this->caracteristica = caracteristica;
}

Persona::Persona() = default;

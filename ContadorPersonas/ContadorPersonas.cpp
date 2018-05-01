//
// Created by lucas on 30/04/18.
//

#define FILE_LOCK "/bin/bash"
#define FILE_MEM "/bin/cat"



#include "ContadorPersonas.h"

void ContadorPersonas::agregarExtranjeroDeportado() {
    contadorPersonasStruct c;

    lock.tomarLock();
    c = contador.leer();
    c.extranjerosDeportados++;
    contador.escribir(c);
    lock.liberarLock();
}

void ContadorPersonas::agregarExtranjeroIngresado() {
    contadorPersonasStruct c;

    lock.tomarLock();
    c = contador.leer();
    c.extranjerosIngresados++;
    contador.escribir(c);
    lock.liberarLock();
}

void ContadorPersonas::agregarResidenteIngresado() {
    contadorPersonasStruct c;

    lock.tomarLock();
    c = contador.leer();
    c.residentesIngresados++;
    contador.escribir(c);
    lock.liberarLock();
}

void ContadorPersonas::agregarResidenteOficinaPolicia() {
    contadorPersonasStruct c;

    lock.tomarLock();
    c = contador.leer();
    c.residentesOficinaPolicia++;
    contador.escribir(c);
    lock.liberarLock();
}

ContadorPersonas::ContadorPersonas():
        lock(FILE_LOCK),
        contador(FILE_MEM, 'R') {
}

contadorPersonasStruct ContadorPersonas::getContadores() {
    contadorPersonasStruct c;

    lock.tomarLock();
    c = contador.leer();
    lock.liberarLock();

    return c;
}
void ContadorPersonas::inicializar() {
    contadorPersonasStruct c;

    c.residentesOficinaPolicia = 0;
    c.residentesIngresados = 0;
    c.extranjerosDeportados = 0;
    c.extranjerosIngresados = 0;
}

int ContadorPersonas::getFileDescriptor() {
    return lock.getFileDescriptor();
}

ContadorPersonas::~ContadorPersonas() = default;
#include "./PortaSellos.h"

Sello PortaSellos::sello = Sello();

PortaSellos::PortaSellos(Logger& logger, const int cantSellos) :
    logger(logger),
    semaforo("PortaSellos.cpp", cantSellos) {
    logger.log("Portasellos creado");
}

Sello& PortaSellos::getSello() {
    semaforo.p();
    return sello;
}

void PortaSellos::putSello(Sello& sello) {
    semaforo.v();
}

PortaSellos::~PortaSellos() {
    logger.log("Portasellos Destruido");
}

void PortaSellos::terminar() {
    semaforo.eliminar();
}

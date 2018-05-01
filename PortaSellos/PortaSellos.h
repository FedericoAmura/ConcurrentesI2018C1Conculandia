#ifndef ADUANACONCULANDIA_PORTASELLOS_H
#define ADUANACONCULANDIA_PORTASELLOS_H

#include "../Logger/Logger.h"
#include "../Sello/Sello.h"
#include "../Semaforo/Semaforo.h"

class PortaSellos {

private:
    Semaforo semaforo;
    Logger& logger;
    static Sello sello;

public:
    PortaSellos(Logger& logger, int cantSellos);
    ~PortaSellos();

    Sello& getSello();
    void putSello(Sello& sello);
    void terminar();

};

#endif //ADUANACONCULANDIA_PORTASELLOS_H

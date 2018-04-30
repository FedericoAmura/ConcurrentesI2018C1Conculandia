//
// Created by lucas on 28/04/18.
//

#ifndef ADUANACONCULANDIA_PORTASELLOS_H
#define ADUANACONCULANDIA_PORTASELLOS_H

#include "../Semaforo/Semaforo.h"
#include "../Logger/Logger.h"
#include "../Sello/Sello.h"

class PortaSellos {
private:
    Semaforo semaforo;
    Logger& logger;
    static Sello sello;


public:
    explicit PortaSellos(Logger& logger, int cantSellos);
    Sello& getSello();
    void putSello(Sello& sello);
    void terminar();
    ~PortaSellos();

};


#endif //ADUANACONCULANDIA_PORTASELLOS_H

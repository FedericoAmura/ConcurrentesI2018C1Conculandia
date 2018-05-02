#ifndef ADUANACONCULANDIA_SELLO_H
#define ADUANACONCULANDIA_SELLO_H

#include "../Persona/Persona.h"
#include "../ContadorPersonas/ContadorPersonas.h"

class Sello {

    public:
        void sellar(Persona persona);
        Sello();

    private:
        ContadorPersonas contadorPersonas;

};


#endif //ADUANACONCULANDIA_SELLO_H

#ifndef ADUANACONCULANDIA_MENU_H
#define ADUANACONCULANDIA_MENU_H

#include <iostream>
#include <string>

#include "../MinistroSeguridad/MinistroSeguridad.h"

class Menu {

private:
    MinistroSeguridad ministroSeguridad;

public:
    explicit Menu(MinistroSeguridad &ministroSeguridad);

    /**
     * Inicia el menu interactivo para el usuario.
     */
    void iniciar();
};


#endif //ADUANACONCULANDIA_MENU_H

//
// Created by nestor on 30/04/18.
//

#ifndef ADUANACONCULANDIA_MENU_H
#define ADUANACONCULANDIA_MENU_H

#include "../MinistroSeguridad/MinistroSeguridad.h"
#include <iostream>
#include <string>

class Menu {

private:
    MinistroSeguridad ministroSeguridad;

public:
    Menu(MinistroSeguridad &ministroSeguridad);

    /**
     * Inicia el menu interactivo para el usuario.
     */
    void iniciar();
};


#endif //ADUANACONCULANDIA_MENU_H

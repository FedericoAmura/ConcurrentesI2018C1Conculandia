#ifndef ADUANACONCULANDIA_MENU_H
#define ADUANACONCULANDIA_MENU_H

#include <iostream>
#include <string>

#include "../MinistroSeguridad/MinistroSeguridad.h"

class Menu {

public:
    Menu(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu);
    /**
     * Inicia el menu interactivo para el usuario.
     */
    void iniciar();

private:

    Logger& logger;
    Pipe canalMenuMinistro;
    Pipe canalMinistroMenu;

    /***
     * Permite al usuario consultar el listado de personas de riesgo.
     * @return ventor<string> Listado de caracteristicas
     */
    vector<string> consultarPersonasRiesgoAMinistro();

    /**
     * Permite al usuario dar de alta una caracteristica
     * @param caracteristica
     */
    int altaUsuarioCaracteristica(string caracteristica);

    /**
     * Permite al usuario dar de baja una caracteristica
     * @param numeroRegistroCaracteristica
     * @return
     */
    int bajaUsuarioCaracteristica(int numeroRegistroCaracteristica);

    void enviarAMinistro(int accion, const string &dato);
};


#endif //ADUANACONCULANDIA_MENU_H

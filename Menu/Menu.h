#ifndef ADUANACONCULANDIA_MENU_H
#define ADUANACONCULANDIA_MENU_H

#include <iostream>
#include <string>

#include "../MinistroSeguridad/MinistroSeguridad.h"
#include "../ContadorPersonas/ContadorPersonas.h"

class Menu {

public:
    Menu(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu, ContadorPersonas& contadorPersonas);
    /**
     * Inicia el menu interactivo para el usuario.
     */
    void iniciar();

private:

    Logger& logger;
    Pipe canalMenuMinistro;
    Pipe canalMinistroMenu;
    ContadorPersonas& contadorPersonas;

    /***
     * Permite al usuario consultar el listado de personas de riesgo.
     * @return ventor<string> Listado de caracteristicas
     */
    vector<string> consultarPersonasRiesgoAMinistro();

    /**
     * Permite al usuario dar de alta una caracteristica
     * @param caracteristica
     */
    void altaUsuarioCaracteristica(string caracteristica);

    /**
     * Permite al usuario dar de baja una caracteristica
     * @param numeroRegistroCaracteristica
     * @return
     */
    void bajaUsuarioCaracteristica(int numeroRegistroCaracteristica);

    /**
     * Envia una accion al Ministro de Seguridad
     * @param accion
     * @param dato
     */
    void enviarAMinistro(int accion, const string &dato);
};


#endif //ADUANACONCULANDIA_MENU_H

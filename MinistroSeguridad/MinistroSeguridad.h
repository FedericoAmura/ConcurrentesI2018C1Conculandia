//
// Created by nestor on 30/04/18.
//

#ifndef ADUANACONCULANDIA_MINISTROSEGURIDAD_H
#define ADUANACONCULANDIA_MINISTROSEGURIDAD_H

#include "../ProcesoHijo/ProcesoHijo.h"
#include "../Signal/SignalHandler.h"
#include "../Signal/SIGINT_Handler.h"
#include <vector>

class MinistroSeguridad : public ProcesoHijo {
private:

public:
    explicit MinistroSeguridad(Logger& logger);
    ~MinistroSeguridad();

    pid_t ejecutar();

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

    /***
     * Permite al usuario consultar el listado de caracteristicas.
     * @return ventor<string> Listado de caracteristicas
     */
    std::vector<string> consultaUsuarioCaracteristicas();

};


#endif //ADUANACONCULANDIA_MINISTROSEGURIDAD_H

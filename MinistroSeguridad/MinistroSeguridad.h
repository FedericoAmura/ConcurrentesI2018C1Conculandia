#ifndef ADUANACONCULANDIA_MINISTROSEGURIDAD_H
#define ADUANACONCULANDIA_MINISTROSEGURIDAD_H

#include <vector>

#include "../ProcesoHijo/ProcesoHijo.h"

class MinistroSeguridad : public ProcesoHijo {

public:
    explicit MinistroSeguridad(Logger& logger);
    ~MinistroSeguridad() override;

    pid_t ejecutar() override;

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
    vector<string> consultaUsuarioCaracteristicas();

};

#endif //ADUANACONCULANDIA_MINISTROSEGURIDAD_H

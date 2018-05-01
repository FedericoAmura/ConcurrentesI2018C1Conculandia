#ifndef ADUANACONCULANDIA_MINISTROSEGURIDAD_H
#define ADUANACONCULANDIA_MINISTROSEGURIDAD_H

#include "../ProcesoHijo/ProcesoHijo.h"
#include "../Signal/SignalHandler.h"
#include "../Signal/SIGINT_Handler.h"
#include "../Lock/LockReadFile.h"
#include "../Pipes/Pipe.h"
#include <vector>

#include "../ProcesoHijo/ProcesoHijo.h"

class MinistroSeguridad : public ProcesoHijo {

private:
    LockReadFile archivoRiesgoLectura;
    Pipe canalMenuMinistro;
    Pipe canalMinistroMenu;

public:
    explicit MinistroSeguridad(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu);
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

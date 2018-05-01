#ifndef ADUANACONCULANDIA_MINISTROSEGURIDAD_H
#define ADUANACONCULANDIA_MINISTROSEGURIDAD_H

#include "../ProcesoHijo/ProcesoHijo.h"
#include "../Signal/SignalHandler.h"
#include "../Signal/SIGINT_Handler.h"
#include "../Lock/LockReadFile.h"
#include "../Pipes/Pipe.h"
#include "../Util/Util.h"
#include <vector>
#include <iomanip>
#include <sstream>

class MinistroSeguridad : public ProcesoHijo {

public:

    static const int BUFFERSIZE_MENU_MINISTRO;
    static const int BUFFERSIZE_MINISTRO_MENU;

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


private:

    LockReadFile archivoRiesgoLectura;
    Pipe canalMenuMinistro;
    Pipe canalMinistroMenu;

    void leerTodoArchivoRiesgo(vector<string> &caracteristicas) const;

    void iniciar();

    void informarAMenuCantidadRegistros(vector<string> &caracteristicas);

    void informarAMenuPersonasRiesgo(vector<string> &caracteristicas);

    void informarAMenuAccionIncorrecta();

    static const int ACCION_CONSULTA;
    static const int ACCION_ALTA;
    static const int ACCION_BAJA;
};

#endif //ADUANACONCULANDIA_MINISTROSEGURIDAD_H

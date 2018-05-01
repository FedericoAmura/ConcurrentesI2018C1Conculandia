#include <iostream>
#include <string>

#include "./FilaEspera/FilaEspera.h"
#include "./Logger/Logger.h"
#include "./PortaSellos/PortaSellos.h"
#include "./Printer/Printer.h"
#include "./Util/Util.h"
#include "./Ventanilla/Ventanilla.h"
#include "./Pipes/Pipe.h"
#include "./MinistroSeguridad/MinistroSeguridad.h"
#include "./Menu/Menu.h"

void terminarVentanillas(const t_parametros &params, vector<Ventanilla *> &ventanillas);

using namespace std;

int main(int argc, char* argv[]) {
    t_parametros params = Util::tomarParametros(argc, argv);

    Logger logger("log.txt", true); // TODO hacer que el debugging se active cuando lo corres con parametro -d
    logger.log("Cargando oficina de aduanas de conculandia");

    logger.log("Oficina inicializada con "+to_string(params.cantSellos)+" sellos");
    static const string ARCHIVO_FIFO = "/tmp/archivo_fifo";
    FifoLectura canalLectura(ARCHIVO_FIFO);
    FifoEscritura canalEscritura(ARCHIVO_FIFO);

    FilaEspera filaEspera(logger, canalEscritura);
    filaEspera.ejecutar();

    PortaSellos portaSellos(logger, params.cantSellos);

    vector<Ventanilla*> ventanillas;
    for (int i = 0; i < params.cantVentanillas; ++i) {
        Ventanilla* ventanilla = new Ventanilla(logger, canalLectura, portaSellos);
        ventanillas.push_back(ventanilla);
        ventanilla->ejecutar();
    }
    logger.log("Oficina inicializada con "+to_string(params.cantVentanillas)+" ventanillas");

    Pipe canalIda;
    Pipe canalVuelta;
    MinistroSeguridad ministroSeguridad(logger, canalIda, canalVuelta);
    //ministroSeguridad.ejecutar();
    logger.log("Ministro de seguridad inicializado");


    Menu menu(ministroSeguridad);
    menu.iniciar();

    filaEspera.terminar();
    terminarVentanillas(params, ventanillas);
    portaSellos.terminar();
    //ministroSeguridad.terminar();
    logger.log("Finalizando oficina de aduanas de conculandia");
    return 0;
}

void terminarVentanillas(const t_parametros &params, vector<Ventanilla *> &ventanillas) {
    for (int i = 0; i < params.cantVentanillas; ++i) {
        Ventanilla* ventanilla = ventanillas.at(i);
        ventanilla->terminar();
        delete(ventanilla);
    }
}


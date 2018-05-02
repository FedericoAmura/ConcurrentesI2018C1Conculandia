#include <iostream>
#include <string>

#include "./ContadorPersonas/ContadorPersonas.h"
#include "./FilaEspera/FilaEspera.h"
#include "./Logger/Logger.h"
#include "./Menu/Menu.h"
#include "./MinistroSeguridad/MinistroSeguridad.h"
#include "./Pipes/Pipe.h"
#include "./PortaSellos/PortaSellos.h"
#include "./Printer/Printer.h"
#include "./Status/Status.h"
#include "./Util/Util.h"
#include "./Ventanilla/Ventanilla.h"

void terminarVentanillas(const t_parametros &params, vector<Ventanilla *> &ventanillas);

using namespace std;

int main(int argc, char* argv[]) {
    atexit(Status::CloseFileDescriptors);

    t_parametros params = Util::tomarParametros(argc, argv);
    int codigoValidacion = Util::validarParametros(params);
    if (codigoValidacion != 0) {
        cout << Util::obtenerMensajeError(codigoValidacion) << endl;
        return 0;
    }

    Logger logger("log.txt", params.debug);
    Status::AddFileDescriptor(logger.getFileDescriptor());
    logger.log("Cargando oficina de aduanas de conculandia");

    logger.log("Oficina inicializada con "+to_string(params.cantSellos)+" sellos");
    static const string ARCHIVO_FIFO = "/tmp/archivo_fifo";
    FifoLectura canalLectura(ARCHIVO_FIFO);
    Status::AddFileDescriptor(canalLectura.getFileDescriptor());
    FifoEscritura canalEscritura(ARCHIVO_FIFO);
    Status::AddFileDescriptor(canalEscritura.getFileDescriptor());

    FilaEspera filaEspera(logger, canalEscritura);
    Status::AddFileDescriptor(filaEspera.getFileDescriptor());
    filaEspera.ejecutar();


    PortaSellos portaSellos(logger, params.cantSellos);
    ContadorPersonas contadorPersonas;
    Status::AddFileDescriptor(contadorPersonas.getFileDescriptor());
    contadorPersonas.inicializar();

    vector<Ventanilla*> ventanillas;
    for (int i = 0; i < params.cantVentanillas; ++i) {
        Ventanilla* ventanilla = new Ventanilla(logger, canalLectura, portaSellos);
        ventanillas.push_back(ventanilla);
        Status::AddFileDescriptor(ventanilla->getFileDescriptor());
        ventanilla->ejecutar();
    }
    logger.log("Oficina inicializada con "+to_string(params.cantVentanillas)+" ventanillas");

    Pipe canalIda;
    Status::AddFileDescriptor(canalIda.getFdLectura());
    Status::AddFileDescriptor(canalIda.getFdEscritura());
    Pipe canalVuelta;
    Status::AddFileDescriptor(canalVuelta.getFdLectura());
    Status::AddFileDescriptor(canalVuelta.getFdEscritura());
    MinistroSeguridad ministroSeguridad(logger, canalIda, canalVuelta);
    ministroSeguridad.ejecutar();
    logger.log("Ministro de seguridad inicializado");


    Menu menu(logger, canalIda, canalVuelta, contadorPersonas);
    menu.iniciar();

    filaEspera.terminar();
    terminarVentanillas(params, ventanillas);
    portaSellos.terminar();
    ministroSeguridad.terminar();
    canalIda.cerrar();
    canalVuelta.cerrar();
    canalLectura.cerrar();
    canalEscritura.cerrar();
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


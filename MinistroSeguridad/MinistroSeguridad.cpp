#include "MinistroSeguridad.h"


pid_t MinistroSeguridad::ejecutar(){
    logger.log("Ejecutamos el ministro de seguridad");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ministro, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como ministro y tengo el pid: "+to_string(getpid()));

    logger.log("Ministro seguridad cerrandose");
    SignalHandler::destruir();

    exit(0);
}

int MinistroSeguridad::altaUsuarioCaracteristica(string caracteristica) {
}

int MinistroSeguridad::bajaUsuarioCaracteristica(int numeroRegistroCaracteristica) {
}

std::vector<string> MinistroSeguridad::consultaUsuarioCaracteristicas() {

}

MinistroSeguridad::MinistroSeguridad(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu) :
        ProcesoHijo(logger), archivoRiesgoLectura("personasriesgo.txt"), canalMenuMinistro(canalMenuMinistro), canalMinistroMenu(canalMinistroMenu) {}

MinistroSeguridad::~MinistroSeguridad() = default;




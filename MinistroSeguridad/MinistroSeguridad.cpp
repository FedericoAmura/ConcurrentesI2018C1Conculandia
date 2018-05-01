//
// Created by nestor on 30/04/18.
//

#include "MinistroSeguridad.h"


MinistroSeguridad::MinistroSeguridad(Logger& logger)
        : ProcesoHijo(logger), archivoRiesgoLectura("personasriesgo.txt"){
}

MinistroSeguridad::~MinistroSeguridad(){
}

pid_t MinistroSeguridad::ejecutar(){
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ministro, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler (SIGINT, &sigint_handler);

    logger.log("Naci como ministro y tengo el pid: "+to_string(getpid()));
    while (sigint_handler.getGracefulQuit() == 0) {
        logger.log("Soy el ministro y estoy vivo");
        sleep(3);
    }

    logger.log("Ministro seguridad cerrandose");
    SignalHandler::destruir();

    exit(0);
}



int MinistroSeguridad::altaUsuarioCaracteristica(string caracteristica){

}

int MinistroSeguridad::bajaUsuarioCaracteristica(int numeroRegistroCaracteristica){

}

std::vector<string> MinistroSeguridad::consultaUsuarioCaracteristicas(){

}
#include <iostream>

#include "./Printer.h"
#include "../Signal/SignalHandler.h"

pid_t Printer::ejecutar() {
    logger.log("Ejecutamos el printer");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo printer, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler (SIGINT, &sigint_handler);

    logger.log("Naci como printer y tengo el pid: "+to_string(getpid()));
    while (sigint_handler.getGracefulQuit() == 0) {
        logger.log("Soy el printer y estoy vivo");
        sleep(3);
    }

    logger.log("Printer cerrandose");
    SignalHandler::destruir();

    exit(0);
}

Printer::Printer(Logger& logger) : ProcesoHijo(logger) {
    logger.log("Printer creado");
};

Printer::~Printer() {
    logger.log("Printer destruido");
};
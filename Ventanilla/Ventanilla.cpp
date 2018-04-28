//
// Created by nestor on 22/04/18.
//

#include "Ventanilla.h"

using namespace std;

pid_t Ventanilla::ejecutar() {
    logger.log("Ejecutamos el printer");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo printer, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler (SIGINT, &sigint_handler);

    logger.log("Naci como Ventanilla y tengo el pid: "+to_string(getProcessId()));

    iniciarAtencion(0);

    logger.log("Printer cerrandose");
    SignalHandler::destruir();

    exit(0);
}

/**
 * Inicia la atension de una ventanilla de aduana para recibir personas.
 * @param cantidadSellos
 */
void Ventanilla::iniciarAtencion(int cantidadSellos) {

    char buffer[Persona::TAMANIO_SERIALIZADO];
    static const string ARCHIVO_FIFO = "/tmp/archivo_fifo";
    FifoLectura canal ( ARCHIVO_FIFO );
    canal.abrir();
    ssize_t bytesleidos = canal.leer(static_cast<void*>(buffer), Persona::TAMANIO_SERIALIZADO);

    while (bytesleidos > 0 && sigint_handler.getGracefulQuit() == 0) {
        if (bytesleidos == Persona::TAMANIO_SERIALIZADO) {
            string mensaje = buffer;
            Persona persona;
            persona.deserializar(buffer);
            logger.log("Atendiendo a DNI: " + persona.getNumeroDocumento());
        } else if (bytesleidos > 0){
            logger.log("La cantidad de bytes leidos no coincide ");
        }
        bytesleidos = canal.leer(static_cast<void*>(buffer), Persona::TAMANIO_SERIALIZADO);
    }
    if (bytesleidos == -1) {
        if (errno == EINTR) {
            string mensajeError = strerror(errno);
            logger.log("Se interrumpio la atencion: " + mensajeError);
        } else {
            string mensajeError = strerror(errno);
            logger.log("Error al atender personas: " + mensajeError);
        }
    }

    canal.cerrar();

}


Ventanilla::Ventanilla(Logger& logger) : ProcesoHijo(logger) {
    logger.log("Printer creado");
};

Ventanilla::~Ventanilla() {
    logger.log("Printer destruido");
};
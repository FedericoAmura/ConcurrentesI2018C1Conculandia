//
// Created by nestor on 22/04/18.
//

#include "Ventanilla.h"

using namespace std;

pid_t Ventanilla::ejecutar() {
    pid = fork();
    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo printer, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler (SIGINT, &sigint_handler);

    logger.log("Naci como Ventanilla y tengo el pid: "+to_string(getpid()));

    iniciarAtencion(0);

    logger.log("Termino la tarea de la ventanilla ");
    SignalHandler::destruir();

    exit(0);
}

/**
 * Inicia la atension de una ventanilla de aduana para recibir personas.
 * @param cantidadSellos
 */
void Ventanilla::iniciarAtencion(int cantidadSellos) {

    char buffer[Persona::TAMANIO_SERIALIZADO];

    canalLectura.abrir();

    ssize_t bytesleidos = leerSiguientePersona(buffer);

    while (bytesleidos > 0 && sigint_handler.getGracefulQuit() == 0) {
        if (bytesleidos == Persona::TAMANIO_SERIALIZADO) {
            Persona persona(buffer);
            logger.log("Atendiendo a DNI: " + to_string(persona.getNumeroDocumento()));
        } else if (bytesleidos > 0){
            logger.log("La cantidad de bytes leidos no coincide ");
        }
        ssize_t bytesleidos = leerSiguientePersona(buffer);
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

    canalLectura.cerrar();

}

ssize_t Ventanilla::leerSiguientePersona( char *buffer) {
    lockExclusivo.tomarLock();
    ssize_t bytesleidos = canalLectura.leer(static_cast<void*>(buffer), Persona::TAMANIO_SERIALIZADO);
    lockExclusivo.liberarLock();
    return bytesleidos;
}


Ventanilla::Ventanilla(Logger& logger, FifoLectura &canal)
        : ProcesoHijo(logger), canalLectura(canal), lockExclusivo("/tmp/lockExclusivoFifo") {
    logger.log("Ventanilla creado");
};

Ventanilla::~Ventanilla() {
    logger.log("Ventanilla destruido");
};
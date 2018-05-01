#include "../Persona/Persona.h"
#include "../Signal/SignalHandler.h"
#include "./Ventanilla.h"

using namespace std;

pid_t Ventanilla::ejecutar() {
    logger.log("Ejecutamos una ventanilla");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ventanilla, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como Ventanilla y tengo el pid: "+to_string(getpid()));

    logger.log("Pido un sello");
    Sello& sello = portaSellos.getSello();
    logger.log("Me dieron un sello");
    sello.sellar();
    logger.log("Voy a devolver el sello");
    portaSellos.putSello(sello);
    logger.log("Devolvi el sello");
    this->iniciarAtencion();

    logger.log("Termino la tarea de la ventanilla");
    SignalHandler::destruir();

    exit(0);
}

/**
 * Inicia la atencion de una ventanilla de aduana para recibir personas.
 */
void Ventanilla::iniciarAtencion() {

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
        bytesleidos = leerSiguientePersona(buffer);
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

ssize_t Ventanilla::leerSiguientePersona(char *buffer) {
    lockExclusivo.tomarLock();
    logger.log("TomoLock");
    ssize_t bytesleidos = canalLectura.leer(static_cast<void*>(buffer), Persona::TAMANIO_SERIALIZADO);
    logger.log("leei");
    lockExclusivo.liberarLock();
    return bytesleidos;
}

Ventanilla::Ventanilla(Logger& logger, FifoLectura &canal,PortaSellos& portaSellos) :
    ProcesoHijo(logger),
    canalLectura(canal),
    lockExclusivo("/tmp/lockExclusivoFifo"),
    portaSellos(portaSellos) {
    logger.log("Ventanilla creada");
};

Ventanilla::~Ventanilla() {
    logger.log("Ventanilla destruida");
};
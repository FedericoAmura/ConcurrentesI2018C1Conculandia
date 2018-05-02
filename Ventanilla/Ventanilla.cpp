#include "../ContadorPersonas/ContadorPersonas.h"
#include "../Persona/Persona.h"
#include "../Signal/SignalHandler.h"
#include "./Ventanilla.h"

#define ARCHIVO_RIESGOS "personasriesgo.txt"

using namespace std;

int Ventanilla::getFileDescriptor() {
    return lockExclusivo.getFileDescriptor();
}

pid_t Ventanilla::ejecutar() {
    logger.log("Ejecutamos una ventanilla");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ventanilla, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como Ventanilla y tengo el pid: "+to_string(getpid()));

    this->iniciarAtencion();
    logger.log("Termino la tarea de la ventanilla");
    SignalHandler::destruir();

    exit(0);
}

/**
 * Inicia la atencion de una ventanilla de aduana para recibir personas.
 */
void Ventanilla::iniciarAtencion() {
    Sello sello;

    char buffer[Persona::TAMANIO_SERIALIZADO];
    Persona persona;

    canalLectura.abrir();

    while (sigint_handler.getGracefulQuit() == 0) {
        try {
            persona = leerPersona(buffer);
            logger.log("Atendiendo a DNI: " + to_string(persona.getNumeroDocumento()) + " Caracteristica: " +
                       persona.getCaracteristica());
            if (examinar(persona)) {
                logger.log(to_string(persona.getNumeroDocumento()) + " puede ingresar a Conculandia");
                ingresa(persona);
            }
            else {
                logger.log("PELIGRO: " + to_string(persona.getNumeroDocumento()) + " es una persona de riesgo.");
                noIngresa(persona);
            }
        }
        catch (std::string &error) {
            logger.log("Error atendiendo personas: " + error);
            break;
        }
    }

    canalLectura.cerrar();
}


Persona Ventanilla::leerPersona(char *buffer) {
    string mensajeError;

    lockExclusivo.tomarLock();
    ssize_t bytesleidos = canalLectura.leer(static_cast<void*>(buffer), Persona::TAMANIO_SERIALIZADO);
    lockExclusivo.liberarLock();
    if (bytesleidos != Persona::TAMANIO_SERIALIZADO) {
        if (bytesleidos == -1)
            mensajeError = strerror(errno);
        else
            mensajeError = "Error al leer la siguiente persona en la fifo";
        throw(std::string(mensajeError));
    }
    Persona personaAtendida(buffer);
    return personaAtendida;
};

Ventanilla::Ventanilla(Logger& logger, FifoLectura &canal,PortaSellos& portaSellos) :
    ProcesoHijo(logger),
    canalLectura(canal),
    lockExclusivo("/tmp/lockExclusivoFifo"),
    portaSellos(portaSellos),
    contadorPersonas() {
    logger.log("Ventanilla creada");
};

Ventanilla::~Ventanilla() {
    logger.log("Ventanilla destruida");
}

void Ventanilla::noIngresa(Persona persona) {
    if (persona.getTipoPersona() == 1) {
        logger.log("Residente con DNI " + to_string(persona.getNumeroDocumento()) + " ha sido enviado a la oficina de Policia.");
        contadorPersonas.agregarResidenteOficinaPolicia();
    }
    else if(persona.getTipoPersona() == 2) {
        logger.log("Extranjero con pasaporte " + to_string(persona.getNumeroDocumento()) + " ha sido deportado.");
        contadorPersonas.agregarExtranjeroDeportado();
    }
}

bool Ventanilla::examinar(Persona persona) {
    bool riesgo;
    if (persona.getTipoPersona() == 1) {
        logger.log("Es residente.");
        riesgo = buscarRiesgo(std::to_string(persona.getNumeroDocumento()));
    }
    else {
        logger.log("Es extranjero.");
        riesgo = buscarRiesgo(persona.getCaracteristica());
    }
    return !riesgo;
}

bool Ventanilla::buscarRiesgo(string riesgo) {
    LockReadFile lockLectura(ARCHIVO_RIESGOS);
    bool ret = false;
    ssize_t bytesLeidos;
    int BUFFSIZE_REGISTRO = 100;
    char bufferRegistro[BUFFSIZE_REGISTRO];
    string caracteristica;
    int i = 0;

    logger.log("Buscando en riesgos: " + riesgo);
    lockLectura.rebobinar();

    do {
        lockLectura.tomarLock();
        bytesLeidos = lockLectura.leer(&bufferRegistro[i], 1);
        lockLectura.liberarLock();
        if ((bytesLeidos) && (bufferRegistro[i] == '\n' || bufferRegistro[i] == 0x0)) {
            bufferRegistro[i] = 0;
            caracteristica = bufferRegistro;
            if (caracteristica == riesgo) {
                ret = true;
                break;
            }
            i = 0;
            continue;
        }
        i++;
    } while (bytesLeidos == 1);
    return ret;
}

void Ventanilla::ingresa(Persona persona) {
    Sello sello;

    if (persona.getTipoPersona() == 1) {
        logger.log("Feliz regreso a Conculandia!");
        contadorPersonas.agregarResidenteIngresado();
    }
    else if (persona.getTipoPersona() == 2) {
        logger.log("Busco un sello");
        sello = portaSellos.getSello();
        logger.log("Agarro un sello");
        sello.sellar(persona);
        contadorPersonas.agregarExtranjeroIngresado();
        portaSellos.putSello(sello);
        logger.log("Devuelvo el sello");
        logger.log("Disfrute su estadia en Conculandia.");
    }

};
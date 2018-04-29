//
// Created by nestor on 22/04/18.
//

#include "FilaEspera.h"

using namespace std;

pid_t FilaEspera::ejecutar() {
    logger.log("Ejecutamos el printer");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo printer, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler (SIGINT, &sigint_handler);

    logger.log("Naci como Fila de Espera y tengo el pid: "+to_string(getProcessId()));

    inicializar();

    logger.log("Termino la tarea de la fila espera");
    SignalHandler::destruir();

    exit(0);
}


vector<Persona> FilaEspera::obtenerPersonas() {
    vector<Persona> personas;
    FILE *fp;
    int numeroDocumento;
    int tipoDocumento;

    fp = fopen("personas.txt", "r");
    if (fp != NULL) {
        while( fscanf(fp, "%d,%d\n", &tipoDocumento, &numeroDocumento) != EOF ) {
            Persona persona(tipoDocumento, numeroDocumento);
            personas.push_back(persona);
        }
        fclose(fp);
    } else {
        logger.log("Error abriendo archivo de clientes\n");
    }

    return personas;
}


void FilaEspera::inicializar() {
    vector<Persona> personas = obtenerPersonas();

    static const string ARCHIVO_FIFO = "/tmp/archivo_fifo";

    FifoEscritura canal ( ARCHIVO_FIFO );
    canal.abrir();

    for (Persona persona : personas) {
        sleep(2);
        canal.escribir(persona.serializar(), Persona::TAMANIO_SERIALIZADO);
        if (sigint_handler.getGracefulQuit() == 1) {
            break;
        }
    }

    canal.cerrar();
    canal.eliminar();
}

FilaEspera::FilaEspera(Logger& logger) : ProcesoHijo(logger) {
    logger.log("FilaEspera creado");
};

FilaEspera::~FilaEspera() {
    logger.log("FilaEspera destruido");
};
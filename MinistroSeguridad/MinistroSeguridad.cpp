#include "MinistroSeguridad.h"


pid_t MinistroSeguridad::ejecutar(){
    logger.log("Ejecutamos el ministro de seguridad");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ministro, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como ministro y tengo el pid: "+to_string(getpid()));
    int BUFFSIZE = 50;
    char buffer[BUFFSIZE];
    ssize_t bytesLeidos = canalMenuMinistro.leer ( static_cast<void*>(buffer),BUFFSIZE );
    logger.log("Ministro: Me llego una operacion desde el menu.");

    while (sigint_handler.getGracefulQuit() == 0) {
        string mensaje = buffer;
        if (bytesLeidos > 0) {
            ssize_t bytesLeidos;
            int BUFFSIZE_REGISTRO = 50;
            char bufferRegistro[BUFFSIZE_REGISTRO];
            if (mensaje == "consultar") { //enviamos listado al menu.
                logger.log("Ministro: Me llego operacion consulta.");
                while ( (bytesLeidos = archivoRiesgoLectura.leer(bufferRegistro, 50) > 0) ) {
                    logger.log("Ministro: escribo.");
                    canalMinistroMenu.escribir(bufferRegistro, BUFFSIZE_REGISTRO);
                }
                if (bytesLeidos < -1) {
                    logger.log("Ministro: Hubo un error leyendo archivo de riesgo de personas.");
                }
            } else if (mensaje == "alta") {
                logger.log("Alta.");
            } else if (mensaje == "baja") {
                logger.log("Baja.");
            } else {
                logger.log("Operacion incorrecta con el ministro de seguridad.");
            }
        }
        logger.log("Ministro: Vuelvo a leer desde el menu.");
        ssize_t bytesLeidos = canalMenuMinistro.leer ( static_cast<void*>(buffer),BUFFSIZE );
    }

    logger.log("Ministro seguridad cerrandose");
    SignalHandler::destruir();

    exit(0);
}

int MinistroSeguridad::altaUsuarioCaracteristica(string caracteristica) {
}

int MinistroSeguridad::bajaUsuarioCaracteristica(int numeroRegistroCaracteristica) {
}

std::vector<string> MinistroSeguridad::consultaUsuarioCaracteristicas() {
    int BUFFSIZE = 50;
    char buffer[BUFFSIZE];
    vector<string> caracteristicas;
    std::string dato = "consultar";

    canalMenuMinistro.escribir ( static_cast<const void*>(dato.c_str()),dato.size() );
    logger.log("Menu: mandamos una operacion al ministro.");


    // Recibimos el listado del ministro.
    ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(buffer),BUFFSIZE );
    logger.log("Menu: Recibimos del menu.");

    while (bytesLeidos > 0) {
        string caracteristica = buffer;
        caracteristicas.push_back(caracteristica);
        ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(buffer),BUFFSIZE );
    }
    return caracteristicas;
}

MinistroSeguridad::MinistroSeguridad(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu) :
        ProcesoHijo(logger), archivoRiesgoLectura("personasriesgo.txt"), canalMenuMinistro(canalMenuMinistro), canalMinistroMenu(canalMinistroMenu) {}

MinistroSeguridad::~MinistroSeguridad() = default;




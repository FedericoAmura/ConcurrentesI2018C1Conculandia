#include "./MinistroSeguridad.h"
/***
 * Tamaño para el buffer del pipe menu a ministro
 * Operacion(1) + Caracteristica(100)
 **/
const int MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO = 101;
/***
 * Tamaño para el buffer del pipe ministro a menu.
 * Caracteristica(100)
 **/
const int MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU = 100;


const int MinistroSeguridad::ACCION_CONSULTA = 1;
const int MinistroSeguridad::ACCION_ALTA = 2;
const int MinistroSeguridad::ACCION_BAJA = 3;



pid_t MinistroSeguridad::ejecutar(){
    logger.log("Ejecutamos el ministro de seguridad");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo ministro, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como ministro y tengo el pid: "+to_string(getpid()));

    iniciar();

    logger.log("Ministro seguridad cerrandose");
    SignalHandler::destruir();
    canalMinistroMenu.cerrar();
    canalMenuMinistro.cerrar();
    exit(0);
}

void MinistroSeguridad::iniciar() {
    char buffer[BUFFERSIZE_MENU_MINISTRO];
    ssize_t bytesLeidos = canalMenuMinistro.leer (static_cast<void*>(buffer), BUFFERSIZE_MENU_MINISTRO );

    while (sigint_handler.getGracefulQuit() == 0) {
        string mensaje = buffer;
        if (bytesLeidos > 0) {

            int accionRecibida = atoi(mensaje.substr(0,1).c_str());
            if (accionRecibida == ACCION_CONSULTA) { //enviamos listado al menu.
                logger.log("Ministro: CONSULTA listado de personas de riesgo ");

                vector<string> caracteristicas;
                leerTodoArchivoRiesgo(caracteristicas);

                informarAMenuCantidadRegistros(caracteristicas);

                informarAMenuPersonasRiesgo(caracteristicas);

            } else if (accionRecibida == ACCION_ALTA) {
                logger.log("Ministro: ALTA nueva caracteristica de riesgo " + Util::trim(mensaje.substr(1,100)));
                this->escribirNuevaCaracteristica(Util::trim(mensaje.substr(1,100)));
            } else if (accionRecibida == ACCION_BAJA) {
                logger.log("Ministro: BAJA caracteristica de riesgo " + Util::trim(mensaje.substr(1,100)));
                this->eliminarCaracteristica(Util::trim(mensaje.substr(1,100)));
            } else {
                informarAMenuAccionIncorrecta();
            }
        }
        logger.log("Ministro: Espero acciones del menu.");
        ssize_t bytesLeidos = canalMenuMinistro.leer (static_cast<void*>(buffer), BUFFERSIZE_MENU_MINISTRO );
        if (bytesLeidos == -1) {
            logger.log("Ministro: Se termino de leer desde el pipe");
        }
    }
}

void MinistroSeguridad::informarAMenuAccionIncorrecta() {
    char bufferRespuesta[BUFFERSIZE_MINISTRO_MENU];
    logger.log("Operacion incorrecta con el ministro de seguridad.");
    stringstream respuesta;
    respuesta<<setw(BUFFERSIZE_MINISTRO_MENU)<<"0";
    strcpy(bufferRespuesta, respuesta.str().c_str());
    canalMinistroMenu.escribir(bufferRespuesta, BUFFERSIZE_MINISTRO_MENU);
}

void MinistroSeguridad::informarAMenuPersonasRiesgo(vector<string> &caracteristicas) {
    char bufferRespuesta[BUFFERSIZE_MINISTRO_MENU];
    for ( int i = 0; i < caracteristicas.size(); i++ ) {
        logger.log("Ministro: informo el listado de riesgos al menu.");
        stringstream respuesta;
        respuesta<<setw(BUFFERSIZE_MINISTRO_MENU)<<caracteristicas.at(i);
        strcpy(bufferRespuesta, respuesta.str().c_str());
        canalMinistroMenu.escribir(static_cast<const void*>(bufferRespuesta), BUFFERSIZE_MINISTRO_MENU);
    }
}

void MinistroSeguridad::informarAMenuCantidadRegistros(vector<string> &caracteristicas) {
    char bufferRespuesta[BUFFERSIZE_MINISTRO_MENU];
    logger.log("Ministro: informo cantidad de caracteristicas en el listado.");
    stringstream cantidadRegistros;
    cantidadRegistros<<setw(BUFFERSIZE_MINISTRO_MENU)<<caracteristicas.size();
    strcpy(bufferRespuesta, cantidadRegistros.str().c_str());
    canalMinistroMenu.escribir(static_cast<const void*>(bufferRespuesta), BUFFERSIZE_MINISTRO_MENU);
}

void MinistroSeguridad::leerTodoArchivoRiesgo(vector<string> &caracteristicas) {
    ssize_t bytesLeidos;
    int BUFFSIZE_REGISTRO = 100;
    char bufferRegistro[BUFFSIZE_REGISTRO];
    string caracteristica;
    int i=0;
    archivoRiesgoLectura.rebobinar();
    archivoRiesgoLectura.tomarLock();
    while ( (bytesLeidos = archivoRiesgoLectura.leer(&bufferRegistro[i], 1) == 1) ) {
        if (bufferRegistro[i] == '\n' || bufferRegistro[i] == 0x0) {
            bufferRegistro[i] = 0;
            caracteristica = bufferRegistro;
            caracteristicas.push_back(caracteristica);
            i = 0;
            continue;
        }
        i++;
    }
    archivoRiesgoLectura.liberarLock();
    if (bytesLeidos < -1) {
        logger.log("Ministro: Hubo un error leyendo archivo de riesgo de personas.");
    }
}

void MinistroSeguridad::escribirNuevaCaracteristica(string caracteristica) {
    ssize_t bytesEscritos;
    archivoRiesgoEscritura.tomarLock();
    caracteristica = caracteristica + "\n";
    bytesEscritos = archivoRiesgoEscritura.escribir(caracteristica.c_str(), caracteristica.length());
    if (bytesEscritos == -1) {
        logger.log("Ministro: ERROR escribiendo en el archivo de riesgo de personas");
    }
    archivoRiesgoEscritura.liberarLock();
}

void MinistroSeguridad::eliminarCaracteristica(string nroCaracteristica) {
    logger.log("Ministro: Eliminando numero de caracteristia" + nroCaracteristica);

    int registroAEliminar = atoi(nroCaracteristica.c_str());
    int contadorRegistro = 0;
    vector<string> caracteristicas;
    leerTodoArchivoRiesgo(caracteristicas);
    archivoRiesgoEscritura.tomarLock();
    ftruncate(archivoRiesgoEscritura.getFileDescriptor(), 0);
    for (auto &&caracteristica : caracteristicas) {
        if (contadorRegistro != registroAEliminar) {
            caracteristica = caracteristica + "\n";
            ssize_t bytesEscritos = archivoRiesgoEscritura.escribir(caracteristica.c_str(), caracteristica.length());
            if (bytesEscritos == -1) {
                logger.log("Ministro: ERROR escribiendo en el archivo de riesgo de personas");
            }
        }
        contadorRegistro++;
    }
    archivoRiesgoEscritura.liberarLock();
}



MinistroSeguridad::MinistroSeguridad(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu) :
        ProcesoHijo(logger),
        archivoRiesgoLectura("personasriesgo.txt"),
        archivoRiesgoEscritura("personasriesgo.txt", false),
        canalMenuMinistro(canalMenuMinistro),
        canalMinistroMenu(canalMinistroMenu) {}

MinistroSeguridad::~MinistroSeguridad() = default;




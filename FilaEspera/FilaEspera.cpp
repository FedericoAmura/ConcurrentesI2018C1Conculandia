#include <random>

#include "./FilaEspera.h"
#include "../Signal/SignalHandler.h"

using namespace std;

int FilaEspera::getFileDescriptor() {
    return this->canalEscritura.getFileDescriptor();
}

pid_t FilaEspera::ejecutar() {
    logger.log("Ejecutamos la fila de espera");
    pid = fork();

    // en el padre devuelvo el process id
    if (pid != 0) return pid;

    // siendo fila de espera, me seteo y ejecuto lo que quiero
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    logger.log("Naci como Fila de Espera y tengo el pid: "+to_string(getpid()));

    inicializar();

    logger.log("Termino la tarea de la fila espera");
    SignalHandler::destruir();

    exit(0);
}

vector<Persona> FilaEspera::obtenerPersonas() {
    vector<Persona> personas;
    FILE* fp;
    char buffer[100];
    fp = fopen("personas.csv", "r");
    if (fp != nullptr) {
        while(fgets(buffer, 100, fp) != nullptr) {
            string linea= buffer;
            vector<string> campos;
            this->parsearLinea(linea, campos);
            Persona persona(stoi(campos.at(0)), stoi(campos.at(1)), campos.at(2));
            personas.push_back(persona);
            if (feof(fp)) {
                break;
            }
        }
        fclose(fp);
    } else {
        logger.log("Error abriendo archivo de clientes");
    }

    return personas;
}

void FilaEspera::parsearLinea(string& linea, vector<string>& campos) const {
    string delimiter = ",";
    size_t pos = 0;
    string token;
    while ((pos = linea.find(delimiter)) != std::string::npos) {
        token = linea.substr(0, pos);
        campos.push_back(token);
        linea.erase(0, pos + delimiter.length());
    }
    linea = Util::eliminarFinLinea(linea);
    campos.push_back(linea);
}


void FilaEspera::inicializar() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<unsigned int> dis;
    unsigned int espera = 0;

    vector<Persona> personas = obtenerPersonas();
    canalEscritura.abrir();
    for (Persona persona : personas) {
        char buffer[Persona::TAMANIO_SERIALIZADO];
        strcpy(buffer, persona.serializar().c_str());
        canalEscritura.escribir(static_cast<const void *>(buffer), Persona::TAMANIO_SERIALIZADO);
        if (sigint_handler.getGracefulQuit() == 1) {
            break;
        }
        espera = 2+dis(gen)%3;
        logger.log("Espero "+to_string(espera)+" segundos para atender el proximo cliente de la lista de espera");
        sleep(espera); // Unicamente para simular la entrada de personas.
    }
    canalEscritura.cerrar();
}

FilaEspera::FilaEspera(Logger& logger, FifoEscritura& canalEscritura) :
    ProcesoHijo(logger),
    canalEscritura(canalEscritura) {
    logger.log("FilaEspera creada");
};

FilaEspera::~FilaEspera() {
    logger.log("FilaEspera destruida");
};
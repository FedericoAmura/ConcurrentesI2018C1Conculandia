#include "Menu.h"

void Menu::iniciar() {
    char input = 'a';
    while (input != '0') {
        cout << endl << "------- MENU -------" << endl;
        cout << "0: Salir" << endl;
        cout << "1: Consultar caracteristicas personas de riesgos" << endl;
        cout << "2: Alta de caracteristica de personas de riesgos" << endl;
        cout << "3: Eliminar caracteristica de personas de riesgos" << endl;
        cout << "Seleccione una opcion: ";
        cin >> input;

        switch (input) {
            case '0':
                cout << "Se procedera a cerrar la oficina de aduanas" << endl;
                break;
            case '1':
            {
                cout << "Listado de caracteristicas" << endl;
                vector<string> listado = this->consultarPersonasRiesgoAMinistro();
                if ( listado.size() > 0 ) {
                    int contador = 0;
                    for (auto &&caracteristica  : listado) {
                        cout << contador <<" " << caracteristica << endl;
                        contador++;
                    }
                } else {
                    cout << "Listado de riesgo de personas vacio." << endl;
                }
                break;
            }
            case '2': {
                string caracteristica;
                bool ingregoCorrecto = false;
                while (!ingregoCorrecto) {

                    cout << "Alta de caracteristica de Personas de Riesgos" << endl;
                    cout << "=============================================" << endl;
                    cout << "Describa una caracteristica y presione Enter" << endl;

                    cin.ignore();
                    getline(cin, caracteristica, '\n');

                    if (caracteristica.size() > 100) {
                        cout << "La longitud del nuevo riesgo es muy largo. Ingrese otro riesgo mas corto" << endl;
                        ingregoCorrecto = false;
                    } else {
                        ingregoCorrecto = true;
                    }
                }

                this->altaUsuarioCaracteristica(caracteristica);
                break;
            }

            case '3': {
                string nroCaracteristica;
                bool ingregoCorrecto = false;
                while (!ingregoCorrecto) {
                    cout << "Baja de caracteristica de Personas de Riesgos" << endl;
                    cout << "=============================================" << endl;
                    cout << "Ingrese un nro de caracteristica y presione Enter" << endl;
                    cin.ignore();
                    getline(cin, nroCaracteristica, '\n');

                    if (nroCaracteristica.size() > 100) {
                        cout << "El numero de caracterisiticas es muy grande" << endl;
                        ingregoCorrecto = false;
                    } else if (!Util::esNumerico(nroCaracteristica)) {
                        cout << "El valor ingresado no es numerico" << endl;
                        ingregoCorrecto = false;
                    } else {
                        ingregoCorrecto = true;
                    }
                }
                this->bajaUsuarioCaracteristica(atoi(nroCaracteristica.c_str()));
                break;
            }
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }
    }
}

vector<string> Menu::consultarPersonasRiesgoAMinistro() {

    vector<string> caracteristicas;
    string itemCaracteristica;
    char bufferVuelta[MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU];

    this->enviarAMinistro(MinistroSeguridad::ACCION_CONSULTA, "");

    // Recibimos el listado del ministro.
    ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(bufferVuelta), MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU );
    if (bytesLeidos > 0) {
        string cantidadRegistros = bufferVuelta;
        logger.log("Menu: Recibimos del ministro cant registros: " + Util::trim(cantidadRegistros.substr(0,MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU)));
        int cantidad = atoi(Util::trim(cantidadRegistros).c_str());
        if ( cantidad > 0 ) {
            for (int i = 0; i < cantidad; i++) {
                string caracteristica = bufferVuelta;
                ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(bufferVuelta), MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU );

                itemCaracteristica = bufferVuelta;
                itemCaracteristica = Util::trim(itemCaracteristica.substr(0, MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU));
                logger.log("Menu: Recibimos del ministro : " + itemCaracteristica);
                caracteristicas.push_back(itemCaracteristica);
            }
        }
    }

    return caracteristicas;
}

void Menu::enviarAMinistro(int accion, const string &dato) {
    char bufferEnvio[MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO];
    stringstream serializado;
    serializado <<setw(1)<< accion << setw(MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO-1) << dato << endl;
    strcpy(bufferEnvio, serializado.str().c_str());
    canalMenuMinistro.escribir (static_cast<const void*>(bufferEnvio), MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO );
}

/**
 * Permite al usuario dar de alta una caracteristica
 * @param caracteristica
 */
int Menu::altaUsuarioCaracteristica(string caracteristica) {
    this->enviarAMinistro(MinistroSeguridad::ACCION_ALTA, caracteristica);
}

/**
 * Permite al usuario dar de baja una caracteristica
 * @param numeroRegistroCaracteristica
 * @return
 */
int Menu::bajaUsuarioCaracteristica(int numeroRegistroCaracteristica) {
    this->enviarAMinistro(MinistroSeguridad::ACCION_BAJA, to_string(numeroRegistroCaracteristica));
}

Menu::Menu(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu) :
        logger(logger),
        canalMenuMinistro(canalMenuMinistro),
        canalMinistroMenu(canalMinistroMenu) {}

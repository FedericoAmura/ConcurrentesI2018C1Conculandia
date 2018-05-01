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
                cout << "Alta de caracteristica de Personas de Riesgos" << endl;
                cout << "=============================================" << endl;
                cout << "Describa una caracteristica y presione Enter" << endl;
                cin >> caracteristica;

                break;
            }

            case '3':
                cout << "Baja de caracteristica de Personas de Riesgos" << endl;
                cout << "=============================================" << endl;
                cout << "Ingrese un nro de caracteristica y presione Enter" << endl;
                cin >> input;
                break;
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }
    }
}

vector<string> Menu::consultarPersonasRiesgoAMinistro() {
    string itemCaracteristica;
    char bufferEnvio[MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO];
    char bufferVuelta[MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU];
    vector<string> caracteristicas;
    stringstream serializado;
    serializado<<1<<setw(MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO)<<endl;
    strcpy(bufferEnvio, serializado.str().c_str());

    canalMenuMinistro.escribir ( static_cast<const void*>(bufferEnvio), MinistroSeguridad::BUFFERSIZE_MENU_MINISTRO );

    // Recibimos el listado del ministro.
    ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(bufferVuelta), MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU );
    if (bytesLeidos > 0) {
        string cantidadRegistros = bufferVuelta;
        logger.log("Menu: Recibimos del ministro cant registros: " + Util::trim(cantidadRegistros));
        int cantidad = atoi(Util::trim(cantidadRegistros).c_str());
        if ( cantidad > 0 ) {
            for (int i = 0; i < cantidad; i++) {
                string caracteristica = bufferVuelta;
                ssize_t bytesLeidos = canalMinistroMenu.leer ( static_cast<void*>(bufferVuelta), MinistroSeguridad::BUFFERSIZE_MINISTRO_MENU );
                itemCaracteristica = Util::trim(bufferVuelta);
                logger.log("Menu: Recibimos del ministro : " + itemCaracteristica);
                caracteristicas.push_back(itemCaracteristica);
            }
        }
    }

    return caracteristicas;
}

/**
 * Permite al usuario dar de alta una caracteristica
 * @param caracteristica
 */
int Menu::altaUsuarioCaracteristica(string caracteristica) {

}

/**
 * Permite al usuario dar de baja una caracteristica
 * @param numeroRegistroCaracteristica
 * @return
 */
int Menu::bajaUsuarioCaracteristica(int numeroRegistroCaracteristica) {

}

Menu::Menu(Logger& logger, Pipe& canalMenuMinistro, Pipe& canalMinistroMenu) :
        logger(logger),
        canalMenuMinistro(canalMenuMinistro),
        canalMinistroMenu(canalMinistroMenu) {}

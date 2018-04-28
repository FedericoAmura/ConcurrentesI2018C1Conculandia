#include <iostream>
#include <string>

#include "./Logger/Logger.h"
#include "./Util/Util.h"

using namespace std;

int main(int argc, char* argv[]) {
    t_parametros params = Util::tomarParametros(argc, argv);

    Logger logger("log.txt", true); // TODO hacer que el debugging se active cuando lo corres con parametro -d
    logger.log("Cargando oficina de aduanas de conculandia");

    logger.log("Oficina inicializada con "+to_string(params.cantSellos)+" sellos");
    logger.log("Oficina inicializada con "+to_string(params.cantVentanillas)+" ventanillas");

    // imprimo y loopeo sobre el menu
    char input = 'a';
    while (input != '0') {
        cout << endl << "------- MENU -------" << endl;
        cout << "0: Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> input;

        switch (input) {
            case '0':
                cout << "Se procedera a cerrar la oficina de aduanas" << endl;
                break;
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }
    }

    logger.log("Finalizando oficina de aduanas de conculandia");
    return 0;
}
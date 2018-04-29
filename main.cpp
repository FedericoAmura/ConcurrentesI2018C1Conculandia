#include <iostream>
#include <string>

#include "./Logger/Logger.h"
#include "./Printer/Printer.h"
#include "./Util/Util.h"
#include "Ventanilla/Ventanilla.h"
#include "FilaEspera/FilaEspera.h"

using namespace std;

int main(int argc, char* argv[]) {
    t_parametros params = Util::tomarParametros(argc, argv);

    Logger logger("log.txt", true); // TODO hacer que el debugging se active cuando lo corres con parametro -d
    logger.log("Cargando oficina de aduanas de conculandia");

    logger.log("Oficina inicializada con "+to_string(params.cantSellos)+" sellos");

    FilaEspera filaEspera(logger);
    filaEspera.ejecutar();

    vector<Ventanilla*> ventanillas;
    for (int i = 0; i < params.cantVentanillas; ++i) {
        Ventanilla* ventanilla = new Ventanilla(logger);
        ventanillas.push_back(ventanilla);
        ventanilla->ejecutar();
    }

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


    filaEspera.terminar();
    for (int i = 0; i < params.cantVentanillas; ++i) {
        Ventanilla* ventanilla = ventanillas.at(i);
        ventanilla->terminar();
        delete(ventanilla);
    }

    logger.log("Finalizando oficina de aduanas de conculandia");
    return 0;
}
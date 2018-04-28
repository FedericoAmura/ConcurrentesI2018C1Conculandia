#include <iostream>

#include "./Util/Util.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Cargando oficina de aduanas de conculandia (pid: " << getpid() << ")" << endl;

    t_parametros params = Util::tomarParametros(argc, argv);

    cout << "Oficina inicializada con " << params.cantSellos << " sellos" << endl;
    cout << "Oficina inicializada con " << params.cantVentanillas << " ventanillas" << endl;

    // imprimo y loopeo sobre el menu
    char input;
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

    cout << endl << "Finalizando oficina de aduanas de conculandia (pid: " << getpid() << ")" << endl;
    return 0;
}
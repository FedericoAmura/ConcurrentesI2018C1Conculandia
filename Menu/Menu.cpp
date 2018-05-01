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
                vector<string> listado = ministroSeguridad.consultaUsuarioCaracteristicas();
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

Menu::Menu(MinistroSeguridad &ministroSeguridad) :
        ministroSeguridad(ministroSeguridad) {}

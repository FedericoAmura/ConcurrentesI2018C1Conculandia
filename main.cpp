#include <iostream>

#include "./Util/Util.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Cargando oficina de aduanas de conculandia con pid: " << getpid() << "..." << endl;

    t_parametros params = Util::tomarParametros(argc, argv);

    cout << "Vamos a correr con " << params.cantSellos << " sellos" << endl;
    cout << "Vamos a correr con " << params.cantVentanillas << " ventanillas" << endl;

    cout << "Finalizando oficina de aduanas de conculandia con pid: " << getpid() << "..." << endl;
    return 0;
}
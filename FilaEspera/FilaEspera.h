#ifndef TP1_CONCULANDIA_FILAESPERA_H
#define TP1_CONCULANDIA_FILAESPERA_H

#include <vector>

#include "../Fifos/FifoEscritura.h"
#include "../Persona/Persona.h"
#include "../ProcesoHijo/ProcesoHijo.h"

class FilaEspera : public ProcesoHijo {

private:
    std::vector<Persona> obtenerPersonas();
    FifoEscritura canalEscritura;

public:
    explicit FilaEspera(Logger& logger, FifoEscritura& canalEscritura);
    ~FilaEspera() override;

    int getFileDescriptor();
    pid_t ejecutar() override;
    void inicializar();

    void parsearLinea(string &linea, vector<string> &campos) const;
};

#endif //TP1_CONCULANDIA_FILAESPERA_H

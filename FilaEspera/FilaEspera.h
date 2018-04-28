//
// Created by nestor on 22/04/18.
//

#ifndef TP1_CONCULANDIA_FILAESPERA_H
#define TP1_CONCULANDIA_FILAESPERA_H

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cerrno>
#include <cstring>



#include "../Util/Util.h"
#include "../Fifos/FifoEscritura.h"
#include "../Fifos/FifoLectura.h"
#include "../Persona/Persona.h"
#include <stdio.h>
#include <stdlib.h>


#include "../Signal/SignalHandler.h"
#include "../Signal/SIGINT_Handler.h"
#include "../ProcesoHijo/ProcesoHijo.h"



class FilaEspera : public ProcesoHijo{
private:
    std::vector<Persona> obtenerPersonas();
public:
    explicit FilaEspera(Logger& logger);
    ~FilaEspera();

    pid_t ejecutar();
    void inicializar();
};


#endif //TP1_CONCULANDIA_FILAESPERA_H

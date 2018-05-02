#include <unistd.h>

#include "./Sello.h"

void Sello::sellar(Persona persona) {
    if (persona.getTipoPersona() == 1)
        contadorPersonas.agregarResidenteIngresado();
    else if (persona.getTipoPersona() == 2)
        contadorPersonas.agregarExtranjeroIngresado();
    else
        throw("Error: Tipo de persona erroneo.");
}

Sello::Sello() = default;

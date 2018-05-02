#include <unistd.h>

#include "./Sello.h"

void Sello::sellar(Persona persona) {
   if (persona.getTipoPersona() != 2)
        throw("Error: Tipo de persona erroneo.");
}

Sello::Sello() = default;

Sello::~Sello() = default;

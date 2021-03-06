#include "Fifo.h"

Fifo::Fifo(const std::string nombre) : nombre(nombre), fd(-1) {
	mknod ( static_cast<const char*>(nombre.c_str()),S_IFIFO|0666,0 );
}

Fifo::~Fifo() {
}

int Fifo::getFileDescriptor() {
	return this->fd;
}

void Fifo::cerrar() {
	close ( fd );
	fd = -1;
}

void Fifo::eliminar() const {
	unlink ( nombre.c_str() );
}

const std::string &Fifo::getNombre() const {
    return nombre;
}

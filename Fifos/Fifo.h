#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Fifo {
public:
	Fifo(const std::string nombre);
	virtual ~Fifo();
	virtual void abrir() = 0;
	int getFileDescriptor();
	void cerrar();
	void eliminar() const;

	const std::string &getNombre() const;

protected:
	std::string nombre;
	int fd;
};

#endif /* FIFO_H_ */

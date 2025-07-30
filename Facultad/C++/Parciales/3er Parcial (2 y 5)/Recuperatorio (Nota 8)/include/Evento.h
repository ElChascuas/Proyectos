#ifndef EVENTO_H
#define EVENTO_H

#include <string>
#include "rubro_t.h"
#include "Expositor.h"

class Evento
{
    private:
        std::string nombre;
        unsigned int fecha;
        Expositor * stands[100];

    public:
        Evento(std::string unNombre, unsigned int unaFecha);
        ~Evento();
        std::string getNombre();
        unsigned int getFecha();
        void setFecha(unsigned int unaFecha);
        Expositor * inscribirExpositor(std::string unNombre, rubro_t unRubro);
        bool desinscribirExpositor(Expositor & unExpositor);
        Expositor * operator[](unsigned int numeroStand);
        unsigned int cantidadExpositores();
        unsigned int cantidadRubros();
};

#endif // EVENTO_H

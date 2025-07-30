#ifndef EXPOSITOR_H
#define EXPOSITOR_H

#include <string>
#include "rubro_t.h"

class Expositor
{
    private:
        std::string nombre;
        rubro_t rubro;
    public:
        Expositor(std::string unNombre, rubro_t unRubro);
        std::string getNombre();
        rubro_t getRubro();
        void setRubro(rubro_t unRubro);
};

#endif // EXPOSITOR_H

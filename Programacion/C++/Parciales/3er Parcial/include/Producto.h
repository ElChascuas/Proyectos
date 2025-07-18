#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto
{
    private:
        std::string nombre;
        double importe;

    public:
        Producto (std::string unNombre, double unImporte);
        std::string getNombre();
        double getImporte();
        void setImporte(double unImporte);
};

#endif // PRODUCTO_H

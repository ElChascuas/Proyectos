#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "Item.h"
#include <string>

class Producto: public Item
{
    private:
        double precio;
    public:
        Producto(std::string unNombre, double unPrecio);
        double const getPrecio();
};

#endif // PRODUCTO_H

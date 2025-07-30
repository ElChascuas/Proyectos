#include "Producto.h"

Producto::Producto(std::string unNombre, double unPrecio) : Item(unNombre)
{
    // El precio del producto nunca puede ser negativo. Si se recibe un parámetro negativo, asignar 0.
    if(unPrecio < 0)
    {
        this->precio = 0;
    }
    else
    {
        this->precio = unPrecio;
    }
}

double const Producto::getPrecio()
{
    // Retornar el precio del Producto. Simple, nada raro.
    return this->precio;
}

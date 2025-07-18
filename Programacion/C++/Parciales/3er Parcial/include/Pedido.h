#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>
#include "Producto.h"

class Pedido
{
    private:
        std::string proveedor;
        unsigned int fechaEntrega;
        unsigned int cupoProductos;
        Producto  ** productos;

    public:
        Pedido (std::string unProveedor, unsigned int unaFechaEntrega, unsigned int unCupoProductos);
        ~Pedido ();
        std::string getProveedor ();
        unsigned int getFechaEntrega ();
        void setFechaEntrega (unsigned int unaFechaEntrega);
        bool operator+ (Producto & unProducto);
        bool operator- (Producto & unProducto);
        double importeTotal();
        unsigned int cantidadProductos();
};

#endif // PEDIDO_H

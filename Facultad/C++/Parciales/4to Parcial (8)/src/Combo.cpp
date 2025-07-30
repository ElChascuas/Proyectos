#include "Combo.h"
#include <stdexcept>

Combo::Combo(std::string unNombre, double unPorcentajeDescuento) : Item(unNombre)
{
     /*
        porcentajeDescuento siempre debe contener un número de 0.0 a 100.0.
        Valores menores a 0, asignar 0.
        Valores mayores a 100, asignar 100.
    */
    if (unPorcentajeDescuento < 0)
    {
        this->porcentajeDescuento = 0;
    }
    else if (unPorcentajeDescuento > 100)
    {
        this->porcentajeDescuento = 100;
    }
    else
    {
        this->porcentajeDescuento = unPorcentajeDescuento;
    }
}

void Combo::setPorcentajeDescuento(double unPorcentajeDescuento)
{
    /*
        porcentajeDescuento siempre debe contener un número de 0.0 a 100.0.
        Valores menores a 0, asignar 0.
        Valores mayores a 100, asignar 100.
    */
    if (unPorcentajeDescuento < 0)
    {
        this->porcentajeDescuento = 0;
    }
    else if (unPorcentajeDescuento > 100)
    {
        this->porcentajeDescuento = 100;
    }
    else
    {
        this->porcentajeDescuento = unPorcentajeDescuento;
    }
}

void Combo::agregarItem(Item & unItem)
{
    // Incorpora unItem a la lista. Puede haber repeticiones del mismo item (Ej un combo 2x1)
    this->items.push_back(&unItem);
}

void Combo::eliminarItem(Item & unItem)
{
    // Elimina la primera aparición de unItem que encuentre en la lista. Lanza excepción con texto si no lo encuentra.
    for(auto it = this->items.begin(); it != this->items.end(); ++it)
    {
        if (*it == &unItem)
        {
            this->items.erase(it);
            return;
        }
    }

    throw ("Elemento no encontrado en la lista."); //Correccion: Throw esperado

}

double const Combo::getPrecio()
{
    double total = 0;
    // suma el precio de todos los ítems de la lista aplicando el porcentaje de descuento al total obtenido.
    for(auto it = this->items.begin(); it != this->items.end(); ++it)
    {
        total += (*it)->getPrecio();
    }
    total = total * (1 - (porcentajeDescuento / 100));
    return total;
}

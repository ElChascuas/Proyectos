#ifndef COMBO_H
#define COMBO_H

#include "Item.h"
#include <string>
#include <list>

class Combo: public Item
{
    private:
        double porcentajeDescuento;
        std::list<Item *> items;
    public:
        Combo(std::string unNombre, double unPorcentajeDescuento);
        double getPorcentajeDescuento() {return this->porcentajeDescuento;}
        void setPorcentajeDescuento(double unPorcentajeDescuento);
        void agregarItem(Item & unItem);
        void eliminarItem(Item & unItem);
        double const getPrecio();
};

#endif // COMBO_H

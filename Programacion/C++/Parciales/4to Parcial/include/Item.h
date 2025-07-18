#ifndef ITEM_H
#define ITEM_H
#include<string>

class Item
{
    private:
        std::string nombre;
    public:
        Item(std::string unNombre);
        std::string const getNombre() {return this->nombre; }
        double virtual const getPrecio() = 0;
};

#endif // ITEM_H

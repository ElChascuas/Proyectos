#include "Corredor.h"

Corredor::Corredor (std::string unNombre, std::string unaEscuderia) : nombre(unNombre) , escuderia(unaEscuderia)
{
}

std::string Corredor::getNombre()
{
    return this->nombre;
}

std::string Corredor::getEscuderia()
{
    return this->escuderia;
}

void Corredor::setEscuderia(std::string unaEscuderia)
{
    this->escuderia = unaEscuderia;
}

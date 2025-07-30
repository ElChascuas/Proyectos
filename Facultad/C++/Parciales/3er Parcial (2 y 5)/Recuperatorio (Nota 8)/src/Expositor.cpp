#include "Expositor.h"

Expositor::Expositor(std::string unNombre, rubro_t unRubro) : nombre(unNombre), rubro(unRubro)
{
}

std::string Expositor::getNombre()
{
    return this->nombre;
}

rubro_t Expositor::getRubro()
{
    return this->rubro;
}

void Expositor::setRubro(rubro_t unRubro)
{
    this->rubro = unRubro;
}

#include "Evento.h"

Evento::Evento(std::string unNombre, unsigned int unaFecha) : nombre(unNombre), fecha(unaFecha)
{
    for(unsigned int i = 0; i < 100; i++)
    {
        this->stands[i] = nullptr;
    }
}

Evento::~Evento()
{
    for (unsigned int i = 0; i < 100; i++)
    {
        delete stands[i];
    }
}

std::string Evento::getNombre()
{
    return this->nombre;
}

unsigned int Evento::getFecha()
{
   return this->fecha;
}

void Evento::setFecha(unsigned int unaFecha)
{
    this->fecha = unaFecha;
}

Expositor * Evento::inscribirExpositor(std::string unNombre, rubro_t unRubro)
{
    // Corrección: se elimina comparación por nombre y rubro.
    for(unsigned int i = 0; i < 100; i++)
    {
        if(this->stands[i] == nullptr)
        {
            this->stands[i] = new Expositor(unNombre, unRubro);
            return this->stands[i];
        }
    }
    return nullptr;
}

bool Evento::desinscribirExpositor(Expositor & unExpositor)
{
    for(unsigned int i = 0; i < 100; i++)
    {
        if(this->stands[i] != nullptr && this->stands[i] == &unExpositor)
        {
            delete this->stands[i];
            this->stands[i] = nullptr;
            return true;
        }
    }
    return false;
}

Expositor * Evento::operator[](unsigned int numeroStand)
{
    // Corrección: el número de stand va de 1 a 100, por lo tanto restamos 1
    if (numeroStand == 0 || numeroStand > 100) // Validacion
    {
        return nullptr;
    }
    return stands[numeroStand - 1]; // Indice esperado
}

unsigned int Evento::cantidadExpositores()
{
    unsigned int j = 0;
    for(unsigned int i = 0; i < 100; i++)
    {
        if(this->stands[i] != nullptr)
        {
            j++;
        }
    }
    return j;
}

unsigned int Evento::cantidadRubros()
{
    unsigned int j = 0;
    rubro_t lista[6] = {OTROS, OTROS, OTROS, OTROS, OTROS, OTROS};
    for (unsigned int i = 0; i < 100; ++i)
    {
        if (this->stands[i] != nullptr)
        {
            rubro_t rubroActual = this->stands[i]->getRubro();
            bool encontrada = false;
            for (unsigned int k = 0; k < j; k++)
            {
                if (lista[k] == rubroActual)
                {
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada)
            {
                if (j < 6)
                {
                    lista[j] = rubroActual;
                    j++;
                }
            }
        }
    }
    return j;
}

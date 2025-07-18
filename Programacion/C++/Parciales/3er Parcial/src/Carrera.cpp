#include "Carrera.h"

Carrera::Carrera(std::string unaCiudad, unsigned int unaFecha) : ciudad(unaCiudad), fecha(unaFecha)
{
    for(unsigned int i = 0; i < 3; i++)
    {
        this->grillaPartida[i] = nullptr;
    }
}

Carrera::~Carrera()
{
}

std::string Carrera::getCiudad()
{
    return this->ciudad;
}

unsigned int Carrera::getFecha()
{
    return this->fecha;
}

void Carrera::setFecha(unsigned int unaFecha)
{
    this->fecha = unaFecha;
}

Corredor * Carrera::inscribirCorredor(std::string unNombre, std::string unaEscuderia)
{
    for(unsigned int i = 0; i < 3; i++)
    {
        if(this->grillaPartida[i] == nullptr)
        {
            this->grillaPartida[i] = new Corredor(unNombre, unaEscuderia);
            return this->grillaPartida[i];
        }
    }
    return nullptr;
}

bool Carrera::desinscribirCorredor(Corredor &unCorredor)
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        if (this->grillaPartida[i] == &unCorredor)
        {
            delete this->grillaPartida[i];
            this->grillaPartida[i] = nullptr;
            return true;
        }
    }
    return false;
}

Corredor * Carrera::operator[](unsigned int posicion)
{
    if (((posicion > 0) && posicion <= 3) && this->grillaPartida[posicion-1] != nullptr)
    {
        return this->grillaPartida[posicion-1];
    }
    else
    {
        return nullptr;
    }
}

unsigned int Carrera::cantidadCorredores()
{
    unsigned int j = 0;
    for (unsigned int i = 0; i < 3; ++i)
    {
        if (this->grillaPartida[i] != nullptr)
        {
            j++;
        }
    }
    return j;
}

unsigned int Carrera::cantidadEscuderias()
{
    unsigned int j = 0;
    std::string lista[3];
    for(unsigned int k = 0; k < 3; k++)
    {
        lista[k] = "000";
    }
    for (unsigned int i = 0; i < 3; ++i)
    {
        if (this->grillaPartida[i] != nullptr)
        {
            std::string escuderiaActual = this->grillaPartida[i]->getEscuderia();
            bool encontrada = false;
            for(unsigned int k = 0; k < 3; k++)
            {
                if (lista[k] == escuderiaActual)
                {
                    encontrada = true;
                }
            }
            if (!encontrada)
            {
                j++;
                for(unsigned int k = 0; k < 3; k++)
                {
                    if (lista[k] == "000")
                    {
                        lista[k] = escuderiaActual;
                    }
                }
            }
        }
    }
    return j;
}




#ifndef CARRERA_H
#define CARRERA_H

#include<string>
#include"Corredor.h"

class Carrera
{
    private:
        std::string ciudad;
        unsigned int fecha;
        Corredor * grillaPartida[50];
    public:
        Carrera(std::string unaCiudad, unsigned int unaFecha);
        ~Carrera();
        std::string getCiudad();
        unsigned int getFecha();
        void setFecha(unsigned int unaFecha);
        Corredor * inscribirCorredor(std::string unNombre, std::string unaEscuderia);
        bool desinscribirCorredor(Corredor & unCorredor);
        Corredor * operator[](unsigned int posicion);
        unsigned int cantidadCorredores();
        unsigned int cantidadEscuderias();
};

#endif // CARRERA_H

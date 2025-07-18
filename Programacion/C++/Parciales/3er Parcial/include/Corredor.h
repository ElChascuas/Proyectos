#ifndef CORREDOR_H
#define CORREDOR_H

#include<string>

class Corredor
{
    private:
        std::string nombre;
        std::string escuderia;

    public:
        Corredor (std::string unNombre, std::string unaEscuderia);
        std::string getNombre();
        std::string getEscuderia();
        void setEscuderia(std::string unaEscuderia);
};

#endif // CORREDOR_H

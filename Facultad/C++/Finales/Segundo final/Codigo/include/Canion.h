#ifndef CANION_H
#define CANION_H

#include <Torreta.h>


class Canion : public Torreta
{
    private:

    public:
        Canion(CasillaTrt& cBase, const sf::Texture& tileset, unsigned int tTipo);
};

#endif // CANION_H

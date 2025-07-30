#ifndef CASILLAINV_H
#define CASILLAINV_H

#include <Casilla.h>

class CasillaInv : public Casilla {
public:
    CasillaEspecial(sf::Vector2f pos, const sf::Texture& tex, sf::IntRect textureRect, int valor);
    virtual ~Casilla();
};

#endif // CASILLAINV_H

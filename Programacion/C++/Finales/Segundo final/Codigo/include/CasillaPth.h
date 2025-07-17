#ifndef CASILLAPTH_H
#define CASILLAPTH_H

#include "Casilla.h"

enum class Direccion {
    DERECHA_IZQUIERDA, ABAJO_ARRIBA, ARRIBA_DERECHA, IZQUIERDA_ARRIBA, ABAJO_DERECHA, IZQUIERDA_ABAJO, NINGUNA
};

class CasillaPth : public Casilla {
private:
    Direccion direccion;
    unsigned int ctipo;

public:
    CasillaPth( sf::Vector2f pos, const sf::Texture& tileset, unsigned int ctipo);
    Direccion getDireccion() const;
    void draw(sf::RenderWindow& ventana);
};

#endif

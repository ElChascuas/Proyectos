#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>
#include "CasillaPth.h"

class Enemigo {
private:
    sf::Sprite sprite;
    sf::Vector2f posicion;
    unsigned int velocidad;
    unsigned int vida;
    unsigned int dmg;
    unsigned int puntoActual = 0;
    unsigned int tipo;
    const sf::Texture& texture;

public:
    Enemigo(const sf::Texture& textura, unsigned int eTipo);
    virtual ~Enemigo();
    void draw(sf::RenderWindow& ventana);
    sf::Vector2f getPosicion() const;
    bool actualizar();
    void recibirDmg(unsigned int dmg);
    unsigned int getVida();
};

#endif

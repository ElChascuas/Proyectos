#include "CasillaPth.h"

CasillaPth::CasillaPth(sf::Vector2f pos, const sf::Texture& tileset, unsigned int ctipo)
    : Casilla(pos, tileset, ctipo) {
    sprite.setTextureRect(sf::IntRect((ctipo - 1) * 51, 0, 51, 51));
}

Direccion CasillaPth::getDireccion() const {
    return direccion;
}

void CasillaPth::draw(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

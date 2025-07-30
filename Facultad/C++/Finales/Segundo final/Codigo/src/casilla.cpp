#include "Casilla.h"


Casilla::Casilla(sf::Vector2f pos, const sf::Texture& tileset,  unsigned int tipo) : ctipo(tipo)
{
    shape.setSize(sf::Vector2f(51, 51));
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Transparent);
    sprite.setTexture(tileset);
    sprite.setPosition(shape.getPosition());
    switch (ctipo)
    {
        case 1: sprite.setTextureRect(sf::IntRect(0, 0, 51, 51)); break;
        case 2: sprite.setTextureRect(sf::IntRect(51, 0, 51, 51)); break;
        case 3: sprite.setTextureRect(sf::IntRect(102, 0, 51, 51)); break;
        case 4: sprite.setTextureRect(sf::IntRect(153, 0, 51, 51)); break;
        case 5: sprite.setTextureRect(sf::IntRect(204, 0, 51, 51)); break;
        case 6: sprite.setTextureRect(sf::IntRect(255, 0, 51, 51)); break;
        case 7: sprite.setTextureRect(sf::IntRect(306, 0, 51, 51)); break;
        case 8: sprite.setTextureRect(sf::IntRect(357, 0, 51, 51)); break;
        case 9: sprite.setTextureRect(sf::IntRect(408, 0, 51, 51)); break;
        case 10: sprite.setTextureRect(sf::IntRect(459, 0, 51, 51)); break;
        case 11: sprite.setTextureRect(sf::IntRect(510, 0, 51, 51)); break;
        default: sprite.setTextureRect(sf::IntRect(357, 510, 51, 51)); break;
    }
}

Casilla::~Casilla() {}

sf::Vector2f Casilla::getCentro() {
    return shape.getPosition() + sf::Vector2f((shape.getSize().x / 2) - 0.5, (shape.getSize().y / 2) - 0.5);
}

sf::Vector2f Casilla::getPos() {
    return shape.getPosition();
}

unsigned int Casilla::getTipo() {
    return ctipo;
}

sf::Sprite& Casilla::getSp() {
    return sprite; // Devuelve una referencia al sprite original
}

void Casilla::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
    window.draw(sprite);
}

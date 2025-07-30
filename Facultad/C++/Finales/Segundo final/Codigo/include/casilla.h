#ifndef CASILLA_H
#define CASILLA_H

#include <SFML/Graphics.hpp>


class Casilla {
protected:
    unsigned int ctipo; // 11 = Torreta, 1-6 Camino y 7-10 decoracion
    sf::RectangleShape shape;
    sf::Sprite sprite;

public:
    Casilla(sf::Vector2f pos, const sf::Texture& tileset, unsigned int tipo);
    virtual ~Casilla();
    sf::Vector2f getCentro();
    sf::Vector2f getPos();
    unsigned int getTipo();
    sf::Sprite& getSp();
    virtual void draw(sf::RenderWindow& window) const;
};

#endif // CASILLA_H

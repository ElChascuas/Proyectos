#ifndef BOTON_H
#define BOTON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "CasillaTrt.h"

class Boton {
private:
    sf::Sprite sprite;
    sf::RectangleShape shape;
    const sf::Texture& texture;
    unsigned int tipo;
    unsigned int rectY;
    bool hovered = false;
    bool pressed = false;
    bool maintained = false;
    CasillaTrt* currentHovered = nullptr;
    static Boton* botonActivo; // Variable estática para el botón activo

public:
    Boton(const sf::Texture& tex, unsigned int bTipo);
    void hover(const sf::Vector2f& mousePos);
    void hoverTrt(const sf::Vector2f& mousePos, const std::vector<CasillaTrt*>& casillasTrt);
    void press();
    void release(const sf::Event& evento, const sf::Texture& tileset);
    bool getPressed();
    bool getMaintained();
    CasillaTrt* getCurrentHovered();
    void setMaintained(bool m);
    void draw(sf::RenderWindow& ventana);
    static void desactivarOtrosBotones(Boton* boton); // Función para desactivar otros botones
};

#endif

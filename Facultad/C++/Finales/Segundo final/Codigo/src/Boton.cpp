#include "Boton.h"
#include <iostream>

Boton::Boton(const sf::Texture& tex, unsigned int bTipo)
    : tipo(bTipo), texture(tex)
{

    this->rectY = 225 * tipo;
    this->shape.setSize(sf::Vector2f(165, 75));
    this->shape.setPosition(sf::Vector2f(780, (15 + (90 * (tipo - 1)))));

    this->sprite.setTexture(texture);
    this->sprite.setPosition(shape.getPosition());

    // Inicializa con la textura base
    this->sprite.setTextureRect(sf::IntRect(0, rectY - 225, 165, 75));
}

// Detecta si el mouse está sobre el botón
void Boton::hover(const sf::Vector2f& mousePos)
{
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        hovered = true;
        if (!pressed)    // Cambia la textura solo si no está presionado
        {
            this->sprite.setTextureRect(sf::IntRect(0, rectY - 150, 165, 75));
        }
    }
    else
    {
        hovered = false;
        if (!pressed)    // Vuelve a la textura normal si no está presionado
        {
            this->sprite.setTextureRect(sf::IntRect(0, rectY - 225, 165, 75));
        }
    }
}

void Boton::hoverTrt(const sf::Vector2f& mousePos, const std::vector<CasillaTrt*>& casillasTrt)
{
    static CasillaTrt* lastHovered = nullptr;  // Última casilla sobre la que estuvo el mouse

    if (this->pressed)
    {
        CasillaTrt* newHovered = nullptr;

        for (CasillaTrt* casillaTrt : casillasTrt)
        {
            if (casillaTrt->getSp().getGlobalBounds().contains(mousePos))
            {
                // Cambiar la textura solo de la casilla actual
                casillaTrt->getSp().setTextureRect(sf::IntRect(408, 510, 51, 51));
                newHovered = casillaTrt;
                break;
            }
        }

        // Restaurar la textura de la casilla anterior si cambia
        if (lastHovered && lastHovered != newHovered)
        {
            lastHovered->getSp().setTextureRect(sf::IntRect(510, 0, 51, 51));
        }

        //  Aquí está el cambio: ahora actualiza el atributo de la clase
        this->currentHovered = newHovered;
        lastHovered = newHovered;
    }
}


// Se ejecuta cuando se hace clic en el botón
void Boton::press()
{
    if (this->hovered && !this->maintained)    // Solo se activa si no estaba presionado antes
    {
        this->pressed = !pressed;
        this->maintained = true;  // Se mantiene hasta que se suelte el clic
        if (this->pressed)
        {
            this->sprite.setTextureRect(sf::IntRect(0, rectY - 75, 165, 75));
        }
        else
        {
            this->sprite.setTextureRect(sf::IntRect(0, rectY - 225, 165, 75));
        }
    }
}

// Se ejecuta cuando se suelta el clic
void Boton::release(const sf::Event& evento, const sf::Texture& tileset)
{
    if (evento.type == sf::Event::MouseButtonPressed && !maintained)
    {
        this->pressed = false;
        sprite.setTextureRect(sf::IntRect(0, this->rectY - 225, 165, 75)); // Vuelve a la textura inicial
        if (this->currentHovered)
        {
            this->currentHovered->setTrt(tileset, this->tipo);
            this->currentHovered->getSp().setTextureRect(sf::IntRect(510, 0, 51, 51));
            this->currentHovered = nullptr;
        }

        //cuando descomento esta linea ocurre un fallo total al hacer click y no se porque, como si press fallase
    }
}


bool Boton::getPressed()
{
    return this->pressed;
}

bool Boton::getMaintained()
{
    return this->maintained;
}

CasillaTrt* Boton::getCurrentHovered()
{
    return currentHovered;
}

void Boton::setMaintained(bool m)
{
    this->maintained = m;
}

void Boton::draw(sf::RenderWindow& ventana)
{
    ventana.draw(this->sprite);
}

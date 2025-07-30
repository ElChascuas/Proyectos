#include <cmath>
#include <iostream>
#include "Torreta.h"
#include "CasillaTrt.h"

Torreta::Torreta(CasillaTrt& cBase, const sf::Texture& tileset, unsigned int tTipo)
    : base(&cBase), texture(tileset), tipo(tTipo), relojDisparo(0)
{
    this->sprite.setTexture(this->texture);

    switch(tipo)
    {
    case 1:
        this->rango = 102;
        this->dmg = 10;
        this->cadencia = 90;
        this->sprite.setTextureRect(sf::IntRect(0, 51, 51, 51));
        break;
    case 2:
        this->rango = 255;
        this->dmg = 25;
        this->cadencia = 180;
        this->sprite.setTextureRect(sf::IntRect(153, 102, 51, 51));
        break;
    case 3:
        this->rango = 102;
        this->dmg = 50;
        this->cadencia = 420;
        this->sprite.setTextureRect(sf::IntRect(459, 153, 51, 51));
        break;
    }

    sf::FloatRect bounds = this->sprite.getLocalBounds();
    this->sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    sf::Vector2f basePos = this->base->getPos();
    this->sprite.setPosition(basePos + sf::Vector2f(25.5, 25.5));
}

Torreta::~Torreta() {}

void Torreta::draw(sf::RenderWindow& ventana)
{
    ventana.draw(this->sprite);
}

void Torreta::actualizar(std::list<Enemigo*>& enemigos)
{
    if (this->objetivo && (!this->estaEnRango(this->objetivo) || this->objetivo->getVida() <= 0))
    {
        this->objetivo = nullptr;
    }

    if (!this->objetivo)
    {
        this->objetivo = this->buscarEnemigoEnRango(enemigos);
    }

    if (this->objetivo)
    {
        sf::Vector2f direccion = this->objetivo->getPosicion() - this->sprite.getPosition();
        float angulo = std::atan2(direccion.y, direccion.x) * 180.f / M_PI;
        this->sprite.setRotation(angulo + 90.f);
        disparar();

    }
}

Enemigo* Torreta::buscarEnemigoEnRango(std::list<Enemigo*>& enemigos)
{
    Enemigo* enemigoMasCercano = nullptr;
    float distanciaMinima = this->rango;

    for (Enemigo* enemigo : enemigos)
    {
        if (this->estaEnRango(enemigo))
        {
            float distancia = std::sqrt(std::pow(enemigo->getPosicion().x - this->sprite.getPosition().x, 2) +
                                        std::pow(enemigo->getPosicion().y - this->sprite.getPosition().y, 2));
            if (distancia < distanciaMinima)
            {
                distanciaMinima = distancia;
                enemigoMasCercano = enemigo;
            }
        }
    }

    return enemigoMasCercano;
}

bool Torreta::estaEnRango(Enemigo* enemigo)
{
    float distancia = std::sqrt(std::pow(enemigo->getPosicion().x - this->sprite.getPosition().x, 2) +
                                std::pow(enemigo->getPosicion().y - this->sprite.getPosition().y, 2));
    return distancia <= this->rango;
}

void Torreta::disparar()
{
    if (relojDisparo >= this->cadencia)
    {
        if (this->objetivo)
        {
            this->objetivo->recibirDmg(this->dmg);
        }
        relojDisparo = 0;
    }
    relojDisparo++;
}


/*
void Torreta::apuntarHaciaMouse(const sf::RenderWindow& ventana) {
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(ventana);
    sf::Vector2f mousePosWorld = ventana.mapPixelToCoords(mousePosWindow);

    sf::Vector2f torretaPos = sprite.getPosition();
    sf::Vector2f diferencia = mousePosWorld - torretaPos;

    // Convertir radianes a grados (asegúrate de usar M_PI de <cmath>)
    float angulo = std::atan2(diferencia.y, diferencia.x) * 180.f / M_PI;

    sprite.setRotation(angulo);
}
*/

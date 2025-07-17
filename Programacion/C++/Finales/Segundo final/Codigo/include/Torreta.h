#ifndef TORRETA_H
#define TORRETA_H

#include <SFML/Graphics.hpp>

#include <list>

#include "Enemigo.h"

class CasillaTrt; // Declaración adelantada

class Torreta
{
    private:
        unsigned int dmg;
        unsigned int cadencia;
        unsigned int rango;
        unsigned int lvl = 1;
        unsigned int tipo;
        sf::Sprite sprite;
        const sf::Texture& texture;
        CasillaTrt* base = nullptr;
        Enemigo* objetivo = nullptr;
        unsigned int relojDisparo;

    public:
        Torreta(CasillaTrt& cBase, const sf::Texture& tileset, unsigned int tTipo);
        ~Torreta();
        void draw(sf::RenderWindow& ventana);
        virtual void actualizar(std::list<Enemigo*>& enemigos);

    private:
        virtual Enemigo* buscarEnemigoEnRango(std::list<Enemigo*>& enemigos);
        virtual bool estaEnRango(Enemigo* enemigo);
        void disparar();
};

#endif // TORRETA_H

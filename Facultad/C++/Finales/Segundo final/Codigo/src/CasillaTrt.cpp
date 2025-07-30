#include "CasillaTrt.h"
#include <iostream>


CasillaTrt::CasillaTrt(sf::Vector2f pos, const sf::Texture& tileset, unsigned int tipo)
    : Casilla(pos, tileset, tipo), trtActiva(false) {}

bool CasillaTrt::tieneTorreta() { return this->trtActiva; }
Torreta* CasillaTrt::getTorreta() { return this->trt; }

void CasillaTrt::setTrt(const sf::Texture& torretaTexture, unsigned int tTipo) {
    if (this->trt == nullptr) {
        this->trt = new Torreta(*this, torretaTexture, tTipo);
        this->trtActiva = true;
    }
}

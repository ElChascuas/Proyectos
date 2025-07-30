#ifndef CASILLATRT_H
#define CASILLATRT_H

#include <Casilla.h>
#include <Torreta.h>

class CasillaTrt : public Casilla {
private:
    bool trtActiva;
    Torreta* trt = nullptr;

public:
    CasillaTrt(sf::Vector2f pos, const sf::Texture& tileset, unsigned int tipo);
    bool tieneTorreta();
    void setTrt(const sf::Texture& torretaTexture, unsigned int tTipo);
    Torreta* getTorreta();
};

#endif // CASILLATRT_H

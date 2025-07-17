#include "Enemigo.h"
#include <cmath>
#include <iostream>

Enemigo::Enemigo(const sf::Texture& textura, unsigned int eTipo)
    : posicion(0.0f, 499.0f), texture(textura), tipo(eTipo)    // Corregido el literal
{
    this->sprite.setTexture(textura);

    switch(tipo) {
        case 1:
            this->sprite.setTextureRect(sf::IntRect(510, 255, 51, 51));
            this->velocidad = 15;
            this->vida = 25;
            this->dmg = 5;
            break;
        case 2:
            this->sprite.setTextureRect(sf::IntRect(102, 306, 51, 51));
            this->velocidad = 30;
            this->vida = 25;
            this->dmg = 10;
            break;
        case 3:
            this->sprite.setTextureRect(sf::IntRect(459, 306, 51, 51));
            this->velocidad = 5;
            this->vida = 50;
            this->dmg = 25;
            break;
    }

    this->sprite.setOrigin(25.5f, 25.5f);
    this->sprite.setPosition(posicion);
}

Enemigo::~Enemigo() {}

sf::Vector2f Enemigo::getPosicion() const
{
    return this->posicion;
}


void Enemigo::draw(sf::RenderWindow& ventana)
{
    ventana.draw(this->sprite);
}

bool Enemigo::actualizar() {
    sf::Vector2f ruta[] = {
        {112.f, 499.f}, // Derecha 2 casillas
        {127.f, 483.f}, // Curva 1 (Derecha a Arriba)
        {127.f, 158.f}, // Arriba 6 casillas
        {143.f, 143.f}, // Curva 2 (Arriba a Derecha)
        {315.f, 143.f}, // Derecha 3 casillas
        {331.f, 158.f}, // Curva 3 (Derecha a Abajo)
        {331.f, 330.f}, // Abajo 3 casillas
        {315.f, 346.f}, // Curva 4 (Abajo a Izquierda)
        {296.f, 346.f}, // Curva 5 (Izquierda a Abajo)
        {280.f, 362.f}, // Abajo 1 casilla
        {280.f, 432.f}, // Curva 6 (Abajo a Derecha)
        {296.f, 448.f}, // Derecha 3 casillas
        {468.f, 448.f}, // Curva 7 (Derecha a Arriba)
        {484.f, 432.f}, // Arriba 5 casillas
        {484.f, 158.f}, // Curva 8 (Arriba a Derecha)
        {500.f, 142.f}, // Derecha 3 casillas
        {672.f, 142.f}, // Curva 9 (Derecha a Abajo)
        {688.f, 158.f},  // Abajo 4 casillas
        {688.f, 390.f}  // final
    };

    if (puntoActual < sizeof(ruta) / sizeof(ruta[0])) {
        sf::Vector2f destino = ruta[puntoActual];
        sf::Vector2f direccion = destino - posicion;
        float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if (distancia > 1.0f) {
            direccion /= distancia;
            posicion += direccion * (velocidad / 60.f);
            sprite.setPosition(posicion);

            float angulo = std::atan2(direccion.y, direccion.x);
            angulo = angulo * 180.0f / 3.14159265f;
            sprite.setRotation(angulo + 90.0f);
        } else {
            puntoActual++;
        }
    } else {
        return true;
    }

    return false;
}

void Enemigo::recibirDmg(unsigned int dmg) {
    std::cout << "Recibiendo daño... Vida actual: " << this->vida << ", Daño recibido: " << dmg << std::endl; // Depuración
    if (this->vida > dmg) {
        this->vida -= dmg;
        std::cout << "Vida reducida a: " << this->vida << std::endl; // Depuración
    } else {
        this->vida = 0;
        std::cout << "¡Enemigo eliminado!" << std::endl; // Depuración
    }
}

unsigned int Enemigo::getVida() {
    return this->vida;
}



/*
CasillaPth* Enemigo::getCailla()
{
    return this->casillaActual;
}

void Enemigo::actualizar(float deltaTime) {
    // Calcular el movimiento en función de la dirección actual
    sf::Vector2f movimiento;
    switch (direccionActual) {
        case Direccion::DERECHA_IZQUIERDA:
            movimiento.x = velocidad * deltaTime;
            sprite.setRotation(90);
            break;

        case Direccion::ABAJO_ARRIBA:
            movimiento.y = invertirEjeY ? velocidad * deltaTime : -velocidad * deltaTime;
            sprite.setRotation(invertirEjeY ? 180 : 0);
            break;

        case Direccion::ARRIBA_DERECHA:
            if (distanciaRecorrida < 10) {
                movimiento.y = -velocidad * deltaTime;
                sprite.setRotation(0);
            } else if (distanciaRecorrida < 28) {
                float diagVel = velocidad * deltaTime / std::sqrt(2);
                movimiento = {diagVel, -diagVel};
                sprite.setRotation(45);
            } else {
                movimiento.x = velocidad * deltaTime;
                sprite.setRotation(90);
            }
            break;

        case Direccion::IZQUIERDA_ABAJO:
            if (distanciaRecorrida < 10) {
                movimiento.x = -velocidad * deltaTime;
                sprite.setRotation(270);
            } else if (distanciaRecorrida < 28) {
                float diagVel = velocidad * deltaTime / std::sqrt(2);
                movimiento = {-diagVel, diagVel};
                sprite.setRotation(135);
            } else {
                movimiento.y = velocidad * deltaTime;
                sprite.setRotation(180);
            }
            break;

        case Direccion::ABAJO_DERECHA:
            if (distanciaRecorrida < 10) {
                movimiento.y = velocidad * deltaTime;
                sprite.setRotation(180);
            } else if (distanciaRecorrida < 28) {
                float diagVel = velocidad * deltaTime / std::sqrt(2);
                movimiento = {diagVel, diagVel};
                sprite.setRotation(135);
            } else {
                movimiento.x = velocidad * deltaTime;
                sprite.setRotation(90);
            }
            break;

        case Direccion::IZQUIERDA_ARRIBA:
            if (distanciaRecorrida < 10) {
                movimiento.x = -velocidad * deltaTime;
                sprite.setRotation(270);
            } else if (distanciaRecorrida < 28) {
                float diagVel = velocidad * deltaTime / std::sqrt(2);
                movimiento = {-diagVel, -diagVel};
                sprite.setRotation(225);
            } else {
                movimiento.y = -velocidad * deltaTime;
                sprite.setRotation(0);
            }
            break;

        default:
            break;
    }

    // Mover el sprite y actualizar distancia recorrida
    sprite.move(movimiento);
    distanciaRecorrida += std::sqrt(movimiento.x * movimiento.x + movimiento.y * movimiento.y);

    // Revisar si se debe cambiar de casilla
    int ctipo = casillaActual->getTipo();
    int distanciaLimite = (ctipo >= 4 && ctipo <= 6) ? 38 : 51;

    if (distanciaRecorrida >= distanciaLimite) {
        distanciaRecorrida = 0;
        CasillaPth* siguienteCasilla = obtenerSiguienteCasilla(casillasPth); // asumiendo que casillasPth es un vector global o de clase
        if (siguienteCasilla) {
            casillaActual = siguienteCasilla;
            direccionActual = casillaActual->getDireccion();
        } else {
            // El enemigo se detiene si no hay siguiente casilla
            movimiento = {0, 0};
        }
    }
}





CasillaPth* Enemigo::obtenerSiguienteCasilla(const std::vector<CasillaPth*>& casillasPth) {
    // Posición actual de la casilla
    sf::Vector2f pos = casillaActual->getPos();
    float desplazamiento = 51.0f;

    // Calcular el desplazamiento según la dirección
    sf::Vector2f offset(0.f, 0.f);

    switch (direccionActual) {
        case Direccion::DERECHA_IZQUIERDA: offset.x = desplazamiento; break;
        case Direccion::ABAJO_ARRIBA:
            offset.y = invertirEjeY ? desplazamiento : -desplazamiento;
            break;
        case Direccion::ARRIBA_DERECHA:  offset.x = desplazamiento; offset.y = -desplazamiento; break;
        case Direccion::IZQUIERDA_ARRIBA: offset.x = -desplazamiento; offset.y = -desplazamiento; break;
        case Direccion::ABAJO_DERECHA: offset.x = desplazamiento; offset.y = desplazamiento; break;
        case Direccion::IZQUIERDA_ABAJO: offset.x = -desplazamiento; offset.y = desplazamiento; break;
        default: return nullptr;
    }

    // Calcular nueva posición
    sf::Vector2f nuevaPos = pos + offset;

    // Buscar la casilla que coincida con esa posición
    for (CasillaPth* casilla : casillasPth) {
        sf::Vector2f cPos = casilla->getPos();
        if (cPos == nuevaPos) {
            return casilla;
        }
    }

    return nullptr;
}

void Enemigo::setCasilla(CasillaPth* nuevaCasilla) {
    casillaActual = nuevaCasilla;
    if (casillaActual) {
        direccionActual = casillaActual->getDireccion();
    }
}
*/

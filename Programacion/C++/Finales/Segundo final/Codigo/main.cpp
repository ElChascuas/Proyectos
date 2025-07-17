#include <SFML/Graphics.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Casilla.h"
#include "CasillaTrt.h"
#include "CasillaPth.h"
#include "Boton.h"
#include "Torreta.h"
#include "Enemigo.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(960, 540), "Tower Defense");

    sf::Texture tileset, bgTexture, storeTexture, pcTexture, btTexture, ptsTexture;
    if (!tileset.loadFromFile("C:/Users/Capitan_CP/Desktop/tileset.png"))
    {
        std::cerr << "Error: No se pudo cargar tileset.png" << std::endl;
        return -1;
    }
    if (!bgTexture.loadFromFile("C:/Users/Capitan_CP/Desktop/bg.png"))
    {
        std::cerr << "Error: No se pudo cargar bg.png" << std::endl;
        return -1;
    }
    if (!storeTexture.loadFromFile("C:/Users/Capitan_CP/Desktop/store.png"))
    {
        std::cerr << "Error: No se pudo cargar store.png" << std::endl;
        return -1;
    }
    if (!pcTexture.loadFromFile("C:/Users/Capitan_CP/Desktop/pc.png"))
    {
        std::cerr << "Error: No se pudo cargar pc.png" << std::endl;
        return -1;
    }
    if (!btTexture.loadFromFile("C:/Users/Capitan_CP/Desktop/bt.png"))
    {
        std::cerr << "Error: No se pudo cargar bt.png" << std::endl;
        return -1;
    }
    if (!ptsTexture.loadFromFile("C:/Users/Capitan_CP/Desktop/pts.png"))
    {
        std::cerr << "Error: No se pudo cargar pts.png" << std::endl;
        return -1;
    }

    sf::RectangleShape background(sf::Vector2f(765, 540));
    background.setTexture(&bgTexture);

    sf::RectangleShape processor(sf::Vector2f(153, 153));
    processor.setTexture(&pcTexture);
    processor.setTextureRect(sf::IntRect(0, 0, 153, 153));
    processor.setPosition(612, 372);

    sf::RectangleShape store(sf::Vector2f(195, 540));
    store.setTexture(&storeTexture);
    store.setPosition(765, 0);

    std::vector<std::vector<unsigned int>> mapa =
    {
        {10, 0, 8, 0, 11, 0, 7, 0, 8, 0, 11, 0, 9, 0, 11},
        {0, 11, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 10, 8, 0},
        {7, 0, 5, 1, 1, 1, 6, 11, 11, 5, 1, 1, 1, 6, 11},
        {8, 0, 2, 0, 11, 11, 2, 0, 0, 2, 8, 0, 0, 2, 0},
        {0, 9, 2, 11, 0, 0, 2, 10, 11, 2, 0, 11, 0, 2, 10},
        {11, 0, 2, 0, 7, 11, 2, 11, 0, 2, 0, 7, 11, 2, 11},
        {9, 0, 2, 0, 0, 5, 4, 0, 7, 2, 0, 0, 0, 2, 0},
        {7, 0, 2, 8, 11, 2, 0, 11, 0, 2, 11, 10, 0, 2, 0},
        {0, 11, 2, 10, 0, 3, 1, 1, 1, 4, 0, 0, 0, 0, 0},
        {1, 1, 4, 11, 0, 9, 0, 11, 0, 9, 0, 11, 0, 0, 0},
    };

    std::vector<Casilla*> casillas;
    std::vector<CasillaTrt*> casillasTrt;
    std::vector<CasillaPth*> casillasPth;
    const unsigned int cellSize = 51;
    const unsigned int marginY = 15;

    for (int j = 0; j < 10; ++j)
    {
        for (int i = 0; i < 15; ++i)
        {

            sf::IntRect textureRect;
            sf::Vector2f posc(i * cellSize, marginY + j * cellSize);
            Casilla* c = nullptr;
            CasillaTrt* cTrt = nullptr;
            CasillaPth* cPth = nullptr;

            if(mapa[j][i] == 11)
            {
                cTrt = new CasillaTrt(posc, tileset, mapa[j][i]);
                casillas.push_back(cTrt);
                casillasTrt.push_back(cTrt);
            }
            else if(mapa[j][i] > 0 && mapa[j][i] < 7)
            {
                cPth = new CasillaPth(posc, tileset, mapa[j][i]);
                casillas.push_back(cPth);
                casillasPth.push_back(cPth);
            }
            else
            {
                c = new Casilla(posc, tileset, mapa[j][i]);
                casillas.push_back(c);
            }
        }
    }


    Boton b1(btTexture, 1);
    Boton b2(btTexture, 2);
    Boton b3(btTexture, 3);
    Boton b4(btTexture, 4);

    std::list<Enemigo*> enemigos;
    sf::Clock clock; // Reloj para controlar la velocidad de fotogramas
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // 60 FPS
    sf::Clock spawnClock;
    srand(time(0));
    unsigned int randomType = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                for (Casilla* casilla : casillas)
                {
                    delete casilla;
                }

                for (Enemigo* enemigo : enemigos)
                {
                    delete enemigo;
                }

                casillas.clear();
                window.close();
            }

            // Detectar clic y soltado dentro del bucle de eventos
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                b1.press();
                b2.press();
                b3.press();
                b4.press();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                b1.setMaintained(false);
                b2.setMaintained(false);
                b3.setMaintained(false);
                b4.setMaintained(false);
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                b1.release(event, tileset);
                b2.release(event, tileset);
                b3.release(event, tileset);
                b4.release(event, tileset);
            }
        }



        window.clear();

        window.draw(background);
        window.draw(store);

        sf::Time elapsed = clock.restart();
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Llamar a hover constantemente
        b1.hover(mousePos);

        b1.hoverTrt(mousePos, casillasTrt);

        b2.hover(mousePos);

        b2.hoverTrt(mousePos, casillasTrt);

        b3.hover(mousePos);

        b3.hoverTrt(mousePos, casillasTrt);

        b4.hover(mousePos);

        b4.hoverTrt(mousePos, casillasTrt);

        // Dibujar botones
        b1.draw(window);
        b2.draw(window);
        b3.draw(window);
        b4.draw(window);

        for (const auto& casilla : casillas)
        {
            casilla->draw(window);
        }
        for (const auto& casillaPth : casillasPth)
        {
            casillaPth->draw(window);
        }

        for (const auto& casillaTrt : casillasTrt)
        {
            if(casillaTrt->getTorreta())
            {
                casillaTrt->getTorreta()->draw(window);
                casillaTrt->getTorreta()->actualizar(enemigos);
                //casillaTrt->getTorreta()->apuntarHaciaMouse(window);
            }
        }

        if (spawnClock.getElapsedTime().asSeconds() >= 1.0f) {
            randomType = rand() % 7 + 1;
            if (randomType < 5) {
                enemigos.push_back(new Enemigo(tileset, 1));
            }
            else if (randomType > 4 && randomType < 7) {
                enemigos.push_back(new Enemigo(tileset, 2));
            }
            else{
                enemigos.push_back(new Enemigo(tileset, 3));
            }
            spawnClock.restart();
        }

        // Actualizar y dibujar los enemigos
        for (auto it = enemigos.begin(); it != enemigos.end(); ++it)
        {
            (*it)->actualizar();
            (*it)->draw(window);
        }

        // Eliminar enemigos que han llegado al final de la ruta
        for (auto it = enemigos.begin(); it != enemigos.end();)
        {
            if ((*it)->actualizar() || (*it)->getVida() == 0)
            {
                delete *it;
                it = enemigos.erase(it);
            }
            else
            {
                ++it;
            }
        }




        window.draw(processor);
        window.display();

        // Controlar la velocidad de fotogramas
        if (elapsed < timePerFrame)
        {
            sf::sleep(timePerFrame - elapsed);
        }
    }


    return 0;
}

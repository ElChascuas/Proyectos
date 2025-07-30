#include "tau/tau.h"
#include <iostream>

#include "Evento.h"
#include "Expositor.h"

TAU_MAIN()

TEST(Expositor, TestBasico)
{
    Expositor e("Juan", GASTRONOMIA);
    CHECK(e.getNombre() == "Juan");
    CHECK(e.getRubro() == GASTRONOMIA);

    e.setRubro(BAZAR);
    CHECK(e.getRubro() == BAZAR);
}

TEST(Evento, OperacionesBasicas)
{
    Evento feria("Feria Anual", 20250729);
    CHECK(feria.getNombre() == "Feria Anual");
    CHECK(feria.getFecha() == 20250729);

    feria.setFecha(20240801);
    CHECK(feria.getFecha() == 20240801);
}

TEST(Evento, GestionExpositores)
{
    Evento feria("Feria Anual", 20250729);

    auto* e1 = feria.inscribirExpositor("Maria", GASTRONOMIA);
    auto* e2 = feria.inscribirExpositor("Pedro", BAZAR);
    auto* e3 = feria.inscribirExpositor("Laura", GASTRONOMIA);

    CHECK(feria.cantidadExpositores() == 3);
    CHECK(feria.cantidadRubros() == 2);

    CHECK(feria[0]->getNombre() == "Maria");
    CHECK(feria[1]->getNombre() == "Pedro");
    CHECK(feria[2]->getNombre() == "Laura");

    // Cambiar rubro y verificar cambio de conteo
    feria[2]->setRubro(BAZAR);
    CHECK(feria.cantidadRubros() == 1);

    // Desinscripción
    CHECK(feria.desinscribirExpositor(*feria[1]));
    CHECK(feria.cantidadExpositores() == 2);
}

TEST(Evento, LimiteDeExpositores)
{
    Evento feria("Max Feria", 20250729);

    for (int i = 0; i < 100; ++i) {
        std::string nombre = "Expositor " + std::to_string(i + 1);
        CHECK(feria.inscribirExpositor(nombre, static_cast<rubro_t>(i % 6)) != nullptr);
    }

    // Intento de inscripción 101
    CHECK(feria.inscribirExpositor("Exceso", GASTRONOMIA) == nullptr);
    CHECK(feria.cantidadExpositores() == 100);
    CHECK(feria.cantidadRubros() == 6);
}

/* Devolucion y nota

Devolucion:El destructor de Carrera debería hacer delete de cada Corredor que hubiera creado.
El método que cuenta la cantidad de escuderías es incorrecto. No funciona para más de 3 escuderías.
El método que cuenta la cantidad de pilotos es incorrecto. No funciona para más de 3 corredores.
Se modifico erroneamente el tamaño de la grilla.

Nota: 2

Comentario: Basicamente era nuestro primer examen con tau, haciendo testing, y como el tiempo 
estaba algo justo para no tener que hacer tanto test reduje el tamaño de grilla, y luego me olvide
de regresarlo a como estaba, y todo el codigo quedo corrupto por eso. Ademas de la fuga de memoria por
olvidar hacer el destructor.
*/


#include "tau/tau.h"
#include <iostream>

#include "Carrera.h"
#include "Corredor.h"

TAU_MAIN()

//Correcion innecesaria: Test menos redundantes (antes eran como 100 linas)

TEST(Corredor, GettersAndSetters)
{
    Corredor c("Yo", "Si");
    CHECK(c.getNombre() == "Yo");
    CHECK(c.getEscuderia() == "Si");

    c.setEscuderia("No");
    CHECK(c.getEscuderia() == "No");
}

TEST(Carrera, InscribirYDesinscribir)
{
    Carrera carrera("No se", 1);
    CHECK(carrera.getCiudad() == "No se");
    carrera.setFecha(2);
    CHECK(carrera.getFecha() == 2);
    CHECK(carrera.cantidadCorredores() == 0);
    CHECK(carrera.cantidadEscuderias() == 0);

    carrera.inscribirCorredor("el", "cual");
    carrera.inscribirCorredor("ella", "ni idea");
    carrera.inscribirCorredor("quien", "cual");

    CHECK(carrera.cantidadCorredores() == 3);
    CHECK(carrera.cantidadEscuderias() == 2);

    CHECK(carrera[0]->getNombre() == "el");
    CHECK(carrera[1]->getEscuderia() == "ni idea");

    CHECK(carrera.desinscribirCorredor(*carrera[1]) == true);
    CHECK(carrera.cantidadCorredores() == 2);
    CHECK(carrera.cantidadEscuderias() == 1);
    CHECK(carrera.desinscribirCorredor(*carrera[0]) == true);
    CHECK(carrera.desinscribirCorredor(*carrera[2]) == true);
    CHECK(carrera.cantidadCorredores() == 0);
    CHECK(carrera.cantidadEscuderias() == 0);
    CHECK(carrera.desinscribirCorredor(*carrera[0]) == false);
}

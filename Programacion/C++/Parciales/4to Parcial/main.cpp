/**
    Segundo parcial de Programación 2.

    Se dispone de la clase abstracta Item de la cual derivan Producto y Combo
    Programar los métodos de Producto y Combo como se explica en los respectivos .cpp de cada clase.
    Considerar que Combo puede contener cualquier tipo de Item en la lista de items. Es decir, puede contener
    Producto o Combo.
    Programar utilizando metodología TDD.
    Al finalizar, eliminar del proyecto las carpetas BIN y OBJ. Comprimir todo el proyecto en un archivo llamado
    con su apellido (ej. Simpson.zip) y adjuntarlo en la tarea correspondiente del aula virtual.

*/

#include "tau/tau.h"
#include <iostream>

#include "Item.h"
#include "Producto.h"
#include "Combo.h"

TAU_MAIN()


TEST(Parcial2, Parcial2)
{
    Producto p1("prod1", -10);
    Producto p2("prod2", 100);
    Producto p3("prod3", 10);
    Producto p4("prod4", 10);
    CHECK(p1.getNombre() == "prod1");
    CHECK(p2.getNombre() == "prod2");
    CHECK(p1.getNombre() != "prod3");
    CHECK(p1.getPrecio() != -10);
    CHECK(p1.getPrecio() == 0);
    CHECK(p2.getPrecio() == 100);

    Combo c1("com", 10);
    Combo c2("com2", 100);
    Combo c3("com3", -1);


    CHECK(c1.getNombre() == "com");
    CHECK(c2.getNombre() == "com2");
    CHECK(c1.getNombre() != "com1");
    CHECK(c1.getPorcentajeDescuento() == 10);
    CHECK(c1.getPorcentajeDescuento() != 1);
    CHECK(c2.getPorcentajeDescuento() == 100);
    CHECK(c3.getPorcentajeDescuento() == 0);
    c1.agregarItem(p1);
    c1.eliminarItem(p1);
    CHECK(c1.getPrecio() == 0);
    c1.agregarItem(p1);
    CHECK(c1.getPrecio() == 0);
    c1.agregarItem(p2);
    CHECK(c1.getPrecio() == 90);
    c1.setPorcentajeDescuento(20);
    CHECK(c1.getPrecio() == 80);
    c2.setPorcentajeDescuento(10);
    c2.agregarItem(p3);
    c2.agregarItem(p4);
    c1.agregarItem(c2);
    CHECK(c1.getPrecio() == 94.4);


    /*
    try
    {
        c1.eliminarItem(p1);
        CHECK(false);
    }
    catch(const char *e)
    {
        CHECK(true);
        std::cerr << e << std::endl;
    }
    */


    CHECK(true);
}

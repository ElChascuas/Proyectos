#include "tau/tau.h"

#include "Carrera.h"
#include "Corredor.h"

TAU_MAIN()

TEST(Corredor, Corredor_testing)
{
    Corredor alan("Alan","Corredor1");
    Corredor gabi("Gabi","Corredor2");
    Corredor javier("Javier","Corredor1");
    Corredor si("Si","Corredor2");

    CHECK(alan.getNombre()=="Alan");
    CHECK(gabi.getNombre()=="Gabi");
    CHECK(javier.getNombre()=="Javier");
    CHECK(si.getNombre()!="Alan");

    CHECK(alan.getEscuderia()=="Corredor1");
    CHECK(gabi.getEscuderia()=="Corredor2");
    CHECK(javier.getEscuderia()!="Corredor2");
    CHECK(si.getEscuderia()=="Corredor2");

    javier.setEscuderia("Corredor3");
    si.setEscuderia("Corredor4");

    CHECK(javier.getEscuderia()=="Corredor3");
    CHECK(javier.getEscuderia()!="Corredor1");
    CHECK(si.getEscuderia()=="Corredor4");
    CHECK(si.getEscuderia()!="Corredor2");
}

TEST(Carrera, Carrera_testing)
{
    Corredor alan("Alan","Corredor1");
    Corredor gabi("Gabi","Corredor2");
    Corredor javier("Javier","Corredor1");
    Corredor si("Si","Corredor2");

    Carrera c("CABA", 20241010);

    CHECK(c.getCiudad()=="CABA");
    CHECK(c.getCiudad()!="CORDOBA");

    CHECK(c.getFecha()==20241010);
    CHECK(c.getFecha()!=20241009);
    CHECK(c.getFecha()!=20241011);

    c.setFecha(20241011);

    CHECK(c.getFecha()==20241011);
    CHECK(c.getFecha()!=20241010);
    CHECK(c.getFecha()!=20241012);

    CHECK(c.cantidadCorredores()==0);

    c.inscribirCorredor("Alan","Corredor1");
    CHECK(c[1]->getNombre()=="Alan");
    CHECK(c[1]->getEscuderia()=="Corredor1");
    CHECK(c.cantidadCorredores()==1);
    CHECK(c.cantidadCorredores()==1);

    c.inscribirCorredor("Gabi","Corredor2");
    CHECK(c[2]->getNombre()=="Gabi");
    CHECK(c[2]->getEscuderia()=="Corredor2");
    CHECK(c.cantidadCorredores()==2);
    CHECK(c.cantidadEscuderias()==2);

    c.inscribirCorredor("Javier","Corredor1");
    CHECK(c[3]->getNombre()=="Javier");
    CHECK(c[3]->getEscuderia()=="Corredor1");
    CHECK(c.cantidadCorredores()==3);
    CHECK(c.cantidadEscuderias()==2);

    CHECK(c.desinscribirCorredor(*c[1])==true);
    c.inscribirCorredor("Si","Corredor2");
    CHECK(c[1]->getNombre()=="Si");
    CHECK(c[1]->getEscuderia()=="Corredor2");
    CHECK(c.cantidadCorredores()==3);
    CHECK(c.cantidadEscuderias()==2);

    CHECK(c.desinscribirCorredor(*c[1])==true);
    CHECK(c.cantidadCorredores()==2);
    CHECK(c.cantidadEscuderias()==2);

    CHECK(c.desinscribirCorredor(*c[2])==true);
    CHECK(c.cantidadCorredores()==1);
    CHECK(c.cantidadEscuderias()==1);

    CHECK(c.desinscribirCorredor(*c[3])==true);
    CHECK(c.cantidadCorredores()==0);
    CHECK(c.cantidadEscuderias()==0);

}


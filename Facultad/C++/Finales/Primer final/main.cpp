/* Devolucion y Nota

Devolucion: El código está bien encarado, se nota que entendiste el objetivo y aplicaste bien los 
conceptos de la materia. Sin embargo, el codigo no complila, y ese es un error garrafal.

Esto se podria haber evitado con un simple testeo en el main, aunque no se tenga en cuenta para la nota
los testeos son casi tan importantes como el codigo, esto normalmente seria un desaporbado, pero
tus contribuciones en clase y tus notas previas me hicieron darte un punto de confianza, en el futuro
no lo dejare pasar.

Nota: 4

Comentario: No mucho que decir totalmente mi culpa, me senti muy frustrado, porque en mi cabeza
el codigo era un diez, encima entregue antes, confiado, habiendome propuesto entregarlo primero,
y no solo no fui primero sino que casi desapruebo la materia.

*/ 


/**
APELLIDO Y NOMBRE: FERNANDEZ THOMAS

Dado el siguiente código, programar los métodos según las indicaciones del comentario
incluido en cada uno de ellos.

En el main se puede programar lo que se necesite para probar los métodos, pero no será
tenido en cuenta a la hora de la corrección.

Al finalizar, adjuntar el archivo main.cpp de este proyecto en la tarea correspondiente
del aula virtual.

La nota surgirá de la evaluación integral de la aplicación de los conocimientos vistos en clase
junto con la correcta ejecución del código entregado.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Equipo {
public:
    std::string nombre;
    unsigned int puntos;
    unsigned int golesAFavor;
    unsigned int golesEnContra;

    Equipo() {
        /**
            Inicializa el equipo con nombre="" y demás propiedades en cero
        */
        this->nombre = "";
        this->puntos = 0;
        this->golesAFavor = 0;
        this->golesEnContra = 0;
    }

    void asignarResultado(unsigned int gaf, unsigned int gec) {
        /**
            Asigna el resultado de un juego de la siguiente forma:
             - Acumula golesAFavor con el correspondiente parámetro (gaf)
             - Acumula golesEnContra con el correspondiente parámetro (gec)
             - Acumula puntos según el resultado:
                 - gaf mayor a gec --> victoria --> +3 puntos
                 - gaf igual a gec --> empate ----> +1 punto
                 - gaf menor a gec --> derrota ---> +0 punto
        */
        if (gaf > gec) {
            this->puntos += 3;
        } else if (gaf == gec) {
            this->puntos += 1;
        }

        this->golesAFavor += gaf;
        this->golesEnContra += gec;
    }

    void imprimir(void) {
        std::cout << this->puntos << ", "
                  << this->golesAFavor << ", "
                  << this->golesEnContra;
    }
};

class Torneo {
public:
    Equipo participantes[5];

    Torneo(std::string e1, std::string e2, std::string e3, std::string e4, std::string e5) {
        /**
            Asigna los respectivos parámetros a los nombres de los equipos participantes
        */
        this->participantes[0].nombre = e1;
        this->participantes[1].nombre = e2;
        this->participantes[2].nombre = e3;
        this->participantes[3].nombre = e4;
        this->participantes[4].nombre = e5;
    }

    bool jugarPartido(std::string e1, std::string e2) {
        /**
            Primero se corrobora que los equipos cuyos nombres se reciben como parámetros
            estén entre los participantes. Si alguno no está se retornará falso, terminándose
            la ejecución del método sin más acciones.

            Si ambos equipos son participantes, deberán generarse de forma aleatoria
            dos números enteros positivos entre 0 y 10 (ambos inclusive).
            Estos números serán los goles convertidos por cada equipo.
            Con esos valores, se asignará el resultado a cada uno de los objetos Equipo que
            jugaron el partido. Finalmente, se retornará verdadero.
        */
        bool p1 = false;
        int equipo1 = 0;
        int res1 = 0;
        bool p2 = false;
        int equipo2 = 0;
        int res2 = 0;

        for (unsigned int i = 0; i < 5; i++) {
            if (this->participantes[i].nombre == e1) {
                equipo1 = i;
                p1 = true;
            }
        }
        for (unsigned int i = 0; i < 5; i++) {
            if (this->participantes[i].nombre == e2) {
                equipo2 = i;
                p2 = true;
            }
        }

        if (p1 && p2) {
            res1 = rand() % 11;
            res2 = rand() % 11;

            this->participantes[equipo1].asignarResultado(res1, res2);
            this->participantes[equipo2].asignarResultado(res2, res1);

            return true;
        } else {
            return false;
        }
    }

    void ordenarTablaPosiciones() {
        /**
            Este método ordenará el arreglo "participantes" con el siguiente criterio:
                - Por puntos de manera decreciente (de mayor a menor).
                - Si 2 o más equipos tienen la misma cantidad de puntos, se desempata por
                  diferencia de golesAFavor y golesEnContra decrecientemente (de mayor a menor).
                - Si 2 o más equipos tienen los mismos puntos y diferencia de gol, se desempata
                  por mayor cantidad de golesAFavor.
        */
        for (unsigned int i = 0; i < 5; i++) {
            for (unsigned int j = i + 1; j < 5; j++) {
                int dif_i = (int)this->participantes[i].golesAFavor - (int)this->participantes[i].golesEnContra;
                int dif_j = (int)this->participantes[j].golesAFavor - (int)this->participantes[j].golesEnContra;

                if (this->participantes[j].puntos > this->participantes[i].puntos ||
                    (this->participantes[j].puntos == this->participantes[i].puntos && dif_j > dif_i) ||
                    (this->participantes[j].puntos == this->participantes[i].puntos && dif_j == dif_i &&
                     this->participantes[j].golesAFavor > this->participantes[i].golesAFavor)) {
                    Equipo aux = this->participantes[i];
                    this->participantes[i] = this->participantes[j];
                    this->participantes[j] = aux;
                }
            }
        }
    } //Correcion: Agregado el cierre de llave

    void imprimirTablaPosiciones() {
        /**
            Se imprimirá la tabla de participantes ordenada mostrando:
             - nombre del equipo
             - goles a favor
             - goles en contra
             - diferencia de goles
        */
        for (unsigned int i = 0; i < 5; i++) {
            std::cout << "- nombre del equipo " << i + 1 << ": " << participantes[i].nombre << std::endl;
            std::cout << "- goles a favor del equipo " << i + 1 << ": " << participantes[i].golesAFavor << std::endl;
            std::cout << "- goles en contra del equipo " << i + 1 << ": " << participantes[i].golesEnContra << std::endl;
            std::cout << "- diferencia de goles del equipo " << i + 1 << ": " << ((int)participantes[i].golesAFavor - (int)participantes[i].golesEnContra) << std::endl;
        }
    }
};

int main() {
    /**
        Hacer un main de prueba con lo que sea necesario para probar las clases.

        *** NO SERÁ TENIDO EN CUENTA PARA LA CORRECCIÓN ***
    */

    //Correcion: Testeo correcto

    srand(time(0));

    Torneo torneo("Boca", "River", "Racing", "Independiente", "SanLorenzo");

    torneo.jugarPartido("Boca", "River");
    torneo.jugarPartido("Racing", "Independiente");
    torneo.jugarPartido("SanLorenzo", "Boca");
    torneo.jugarPartido("River", "Independiente");
    torneo.jugarPartido("SanLorenzo", "Racing");

    torneo.ordenarTablaPosiciones();
    torneo.imprimirTablaPosiciones();

    return 0;
}

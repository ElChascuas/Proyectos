/**

APELLIDO Y NOMBRE: FERNANDEZ THOMAS


Dado el siguiente c�digo, programar los m�todos seg�n las indicaciones del comentario
incluido en cada uno de ellos.

En el main se puede programar lo que se necesite para probar los m�todos, pero no ser�
tenido en cuenta a la hora de la correcci�n.

Al finalizar, adjuntar el archivo main.cpp de este proyecto en la tarea correspondiente
del aula virtual.

La nota surgir� de la evaluaci�n integral de la aplicaci�n los conocimientos vistos en clase
junto con la correcta ejecuci�n del c�digo entregado.

*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Equipo
{
public:
    std::string nombre;
    unsigned int puntos;
    unsigned int golesAFavor;
    unsigned int golesEnContra;

    Equipo()
    {
        /**
            Inicializa el equipo con nombre="" y dem�s propiedades en cero
        */
        this->nombre = "";
        this->puntos = 0;
        this->golesAFavor = 0;
        this->golesEnContra = 0;
    }

    void asignarResultado(unsigned int gaf, unsigned int gec)
    {
        /**
            Asgina el resultado de un juego de la siguiente forma:
             - Acumula golesAFavor con el correspondiente par�metro (gaf)
             - Acumula golesEnContra con el correspondiente par�metro (gec)
             - Acumula puntos seg�n seg�n el resultado:
                 - gaf mayor a gec --> victoria --> +3 puntos
                 - gaf igual a gec --> empate ----> +1 punto
                 - gaf menor a gec --> derrota ---> +0 punto

            Ejemplo para Equipo x =
                nombre: "Un Equipo"
                puntos: 7
                golesAFavor: 10
                golesEnContra: 6
            x.asignarResultado(2, 1), quedar�a con
                nombre: "Un Equipo" --> no cambia
                puntos: 10 -----------> +3 porque es victoria
                golesAFavor: 12 ------> +2 porque sum� 2 goles a favor
                golesEnContra: 7 -----> +1 porque sum� 1 gol en contra

        */

        if (gaf > gec)
        {
            this->puntos += 3;
        }
        else if (gaf == gec)
        {
            this->puntos++;
        }

        this->golesAFavor += gaf;
        this->golesEnContra += gec;

    }

    void imprimir(void)
    {
        std::cout << this->puntos << ", " << this->golesAFavor << ", " << this->golesEnContra;
    }
};


class Torneo
{
public:
    Equipo participantes[5];

    Torneo(std::string e1, std::string e2, std::string e3, std::string e4, std::string e5)
    {
        /**
            Asigna los respectivos par�metros a los nombres de los equipos participantes
        */

        this->participantes[0].nombre = e1;
        this->participantes[1].nombre = e2;
        this->participantes[2].nombre = e3;
        this->participantes[3].nombre = e4;
        this->participantes[4].nombre = e5;
    }

    bool jugarPartido(std::string e1, std::string e2)
    {
        /**
            Primero se corrobora que los equipos cuyos nombres se reciben como par�metros
            est�n entre los participantes. Si alguno no est� se retornar� falso, termin�ndose
            la ejecuci�n del m�todo sin m�s acciones.

            Si ambos equipos son participantes, deber�n generarse de forma aleatoria
            dos n�meros enteros positivos entre 0 y 10 (ambos inclusive).
            Estos n�meros ser�n los goles convertidos por cada equipo.
            Con esos valores, se asignar� el resultado a cada uno de los objetos Equipo que
            jugaron el partido. Finalmente, se retornar� verdadero.
        */

        bool p1 = false;
        int equipo1 = 0;
        int res1 = 0;
        bool p2 = false;
        int equipo2 = 0;
        int res2 = 0;

        for(unsigned int i = 0; i < 5; i++)
        {
            if(this->participantes[i].nombre == e1)
            {
                equipo1 = i;
                p1 = true;
            }
        }
        for(unsigned int i = 0; i < 5; i++)
        {
            if(this->participantes[i].nombre == e2)
            {
                equipo2 = i;
                p2 = true;
            }
        }

        if(p1 == true && p2 == true)
        {
            res1 = rand()%(10+1);
            res2 = rand()%(10+1);

            this->participantes[equipo1].asignarResultado(res1, res2);
            this->participantes[equipo2].asignarResultado(res2, res1);

            return true;
        }
        else
        {
            return false;
        }
    }

    void ordenarTablaPosiciones()
    {
        /**
            Este m�todo ordenar� el arreglo "participantes" con el siguiente criterio:
                - Por puntos de manera decreciente (de mayor a menor).
                - Si 2 o m�s equipos tienen la misma cantidad de puntos, se desempata por
                  diferencia de golesAFavor y golesEnContra decrecientemente (de mayora a menor).
                - Si 2 o m�s equipos tiene los mismos puntos y diferencia de gol, se desempata
                  por mayor cantidad de golesAFavor.
        */


        {
            for (unsigned int i = 0; i < 5; i++)
            {
                for (unsigned int j = i + 1; j < 5; j++)
                {

                    if (this->participantes[j].puntos > this->participantes[i].puntos)
                    {
                        Equipo aux = this->participantes[j];
                        this->participantes[j] = this->participantes[i];
                        this->participantes[i] = aux;
                    }

                    else if (this->participantes[j].puntos == this->participantes[i].puntos &&
                            (this->participantes[j].golesAFavor - this->participantes[j].golesEnContra) >
                            (this->participantes[i].golesAFavor - this->participantes[i].golesEnContra))
                    {
                        Equipo aux = this->participantes[j];
                        this->participantes[j] = this->participantes[i];
                        this->participantes[i] = aux;
                    }

                    else if (this->participantes[j].puntos == this->participantes[i].puntos &&
                            (this->participantes[j].golesAFavor - this->participantes[j].golesEnContra) ==
                            (this->participantes[i].golesAFavor - this->participantes[i].golesEnContra) &&
                             this->participantes[j].golesAFavor > this->participantes[i].golesAFavor)
                    {
                        Equipo aux = this->participantes[j];
                        this->participantes[j] = this->participantes[i];
                        this->participantes[i] = aux;
                    }
                }

                void imprimirTablaPosiciones()
                {
                    /**
                        Se imprimir� la tabla de participantes ordenada mostrando:
                         - nombre del equipo
                         - goles a favor
                         - goles en contra
                         - difrencia de goles
                    */
                    for (unsigned int i = 0; i < 5; i++)
                    {
                        std::cout << "- nombre del equipo " << i + 1  << ": " << participantes[i].nombre << std::endl;
                        std::cout << "- goles a favor del equipo " << i + 1  << ": " << participantes[i].golesAFavor << std::endl;
                        std::cout << "- goles en contra del equipo " << i + 1  << ": " << participantes[i].goles en contra << std::endl;
                        std::cout << "- difrencia de goles del equipo " << i + 1  << ": " << (participantes[i].golesAFavor - participantes[i].golesEnContra) << std::endl;
                    }
                }
            };


            int main()
            {
                /**
                    Hacer un main de prueba con lo que sea necesario para probar las clases.

                    *** NO SERA TENIDO EN CUENTA PARA LA CORRECCION ***
                */



                return 0;
            }

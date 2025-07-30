/* Devolucion y Nota

Correccion: Al declarar "arr" de tamaño 100, se asume (erróneamente) 
que el resultado no superará ese tamaño. Es decir, la función sirve para los casos en que ambos 
arreglos no superan los 99 valores útiles entre los 2. En el resto de los casos, fallaría.

Nota: 5

Refleccion: Luego de esto empezamos a aprender colecciones y punteros, y entendi porque jamas trabajas
con arreglos de valor fijo, tarde pero aprendida la leccion.

*/

/**
APELLIDO Y NOMBRE: Fernandez Thomas

TEMA 2

Hacer una función cuyo prototipo sea:

void adosar(int a[], int b[]);

Los dos arreglos recibidos como parámetro contienen números enteros y el cero marca el final de los valores útiles.
La función deberá incorporar todos los valores del primer arreglo, al principio del segundo arreglo.
El primer arreglo (a) no puede modificarse.
Por ejemplo, si se recibe como parmátros:
a = 20, 30, 75, 0 / b = 20, 14, 19, 7, 22, 0
Al finalizar la función, el arreglo a debe quedar intacto y el b debe contener: 20, 30, 75, 20, 14, 19, 7, 22, 0

Aclaración: se pide hacer únicamente la función del enunciado y, si las hubiera, las funciones complementarias.
No se pide realizar el programa completo (main). Se puede hacer un main para probar la función pero no será
tenido en cuenta para la corrección del examen.
 */

#include <iostream>

void adosar(int a[], int b[]);

using namespace std;

int main()
{
    // Datos de ejemplo
    int x[100]={20, 30, 75, 0};
    int y[100]={20, 14, 19, 7, 22, 0};
    adosar(x, y);
    //y --> 20, 30, 75, 20, 14, 19, 7, 22, 0
    return 0;
}

/*Se corrige desde acá en adelante. 
(agregar prototipos adicionales arriba de main)*/

void adosar(int a[], int b[])
{
    /* Codigo previo
    unsigned int j = 0;
    int arr[100] = {};
    for (j = 0; a[j] != 0; j++)
    {
        arr[j] = a[j];
    }
    for (unsigned int i = 0; b[i] != 0; i++, j++)
    {
        arr[j] = b[i];
    }
    for (unsigned int i = 0; arr[i] != 0; i++)
    {
        b[i] = arr[i];
    }*/

    //Correcion: Trabajar con contadores en vez de valores fijos
    unsigned int i = 0;
    while (a[i] != 0) i++;
    unsigned int cantA = i;
    i = 0;
    while (b[i] != 0) i++;
    unsigned int finalB = i;
    for (unsigned int j = finalB - 1; j >= 0; j--) {
        b[j + cantA] = b[j];
    }
    for (unsigned int j = 0; j < cantA; j++) {
        b[j] = a[j];
    }
    b[cantA + finalB] = 0;
}
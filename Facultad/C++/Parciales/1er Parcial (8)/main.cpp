/* Devolucion y Nota

Correccion: Debería validar que el tamaño sea positivo como pide el enunciado. Si no,
utilizar unsigned int.

La condición correcta para la diagonal:

i<=escala-j

debería ser:

i<=escala-j-1

Nota: 8

*/


/**

APELLIDO Y NOMBRE: FERNANDEZ, THOMAS URIEL

**/
/**
Realizar un programa en el que el usuario ingrese el tama�o de una figura (n�mero entero positivo).
A continuaci�n deber� dibujarse con asteriscos una figura de base y altura igual al tama�o ingresado,
de manera que la parte superior izquierda de la diagonal quede rellena y la parte inferior quede hueca
(ver ejemplo para referencia).
Por ejemplo:

Ingrese el tamano de la figura: 8

********
********
****** *
*****  *
****   *
***    *
**     *
********
*/


#include <iostream>

using namespace std;


int main()
{
	unsigned int escala;

    /*Correcion: Validacion de positivo*/
    do {
        cout << "Ingrese un tamanio positivo: ";
        cin >> escala;
    } while (escala <= 0);

    for(unsigned int i = 0; i < escala; i++)
    {
    	for(unsigned int j = 0; j < escala; j++)
        {
            if (i<=escala-j-1 /*Correcion: -1 agregado*/ || i == 0 || i == escala - 1 || j == 0 || j == escala - 1)
            {
                cout << "*";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
 	return 0;
}

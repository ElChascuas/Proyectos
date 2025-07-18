#include <iostream>

using namespace std;

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

int main()
{
	int i, j, escala;

    cout << "Tamanio ";
    cin >> escala;

    for(i = 0; i < escala; i++)
    {
    	for(j = 0; j < escala; j++)
        {
            if (i<=escala-j || i == 0 || i == escala - 1 || j == 0 || j == escala - 1)
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

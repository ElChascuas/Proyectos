#include <iostream>
using namespace std;

//THOMAS FERNANDEZ

void adosar(int a[], int b[]);

int main()
{
    // Datos de ejemplo
    int a[100]={20, 30, 75, 0};
    int b[100]={20, 14, 19, 7, 22, 0};
    adosar(a, b);
    //y --> 20, 30, 75, 20, 14, 19, 7, 22, 0
    return 0;
}

void adosar(int a[], int b[])
{
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
    }
}

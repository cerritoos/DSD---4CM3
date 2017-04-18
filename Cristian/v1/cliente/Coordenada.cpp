/* Implementación de la clase coordenada */
#include "Coordenada.h"

#include <iostream>
#include <cmath>

using namespace std;

Coordenada::Coordenada(int xx, int yy)
{
	if((xx < 0) || (yy < 0))
		cout << "Coordenadas no válidas. Deben estar en el primer octante" << endl;
	else
	{
		x = xx;
		y = yy;
	}
}

int Coordenada::obtenerX(void)
{	return x; }

int Coordenada::obtenerY(void)
{	return y; }


void Coordenada::imprimirCoord(void)
{
	cout << "( " << x << ", " << y << " )" << endl;
}



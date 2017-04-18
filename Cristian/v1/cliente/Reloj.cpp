/* Implementación de la clase Reloj */

#include "Reloj.h"
#include "gfxModified.h"
#include "DisplaySegmentos.h"
#include "Coordenada.h"
#include <iostream>

using namespace std;

Reloj::Reloj()
{	time;	}

Reloj::Reloj(Hora t)
{	time = t;	}

Reloj::Reloj(short h, short m, short s, short d)
{	time = Hora(h,m,s,d);	}

void Reloj::iniciarDisplaySegmentos()
{
	bool cero[7] = {true, true, true, true, true, true, false};
	bool uno[7] = {false, true, true, false, false, false, false,};
	bool dos[7] = {true, true, false, true, true, false, true};
	bool tres[7] = {true, true, true, true, false, false, true};
	bool cuatro[7] = {false, true, true, false, false, true, true};
	bool cinco[7] = {true, false, true, true, false, true, true};
	bool seis[7] = {true, false, true, true, true, true, true};
	bool siete[7] = {true, true, true, false, false, false, false};
	bool ocho[7] = {true, true, true, true, true, true, true};
	bool nueve[7] = {true, true, true, true, false, true, true};

	numeros[0] = DisplaySegmentos(cero);
	numeros[1] = DisplaySegmentos(uno);
	numeros[2] = DisplaySegmentos(dos);
	numeros[3] = DisplaySegmentos(tres);
	numeros[4] = DisplaySegmentos(cuatro);
	numeros[5] = DisplaySegmentos(cinco);
	numeros[6] = DisplaySegmentos(seis);
	numeros[7] = DisplaySegmentos(siete);
	numeros[8] = DisplaySegmentos(ocho);
	numeros[9] = DisplaySegmentos(nueve);
}


void Reloj::dibujar( )
{ 
	char * hora = time.toString();

	//cout << "Dibujando.." << endl;

	for(int i = 0; i < 10; i++)
	{
		int offset = SPACE_X * (i + 1) + T_WIDTH * i;
		if(hora[i] == ':')
			puntos(offset, SPACE_Y);
		else
			numeros[hora[i] - '0'].dibujar((int)offset, SPACE_Y);
		flush();
	}
}

void Reloj::setTime(Hora h)
{	time = h;	}


Hora Reloj::getTime()
{	return time;	}


void Reloj::puntos(int o_x, int o_y)
{
	gfx_fill_rectangle( 0 + o_x, 20 + o_y, 20, 20);
	gfx_fill_rectangle( 0 + o_x, 60 + o_y, 20, 20);
}

void Reloj::iniciar(void)
{
	gfx_open(W_SCREEN, L_SCREEN, "Reloj");
	gfx_color(255, 0, 0);
}

void Reloj::flush(void)
{	gfx_flush();	}

void Reloj::limpiar(void)
{	gfx_clear();	}













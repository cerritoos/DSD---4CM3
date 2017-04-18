#include "Digito.h"
#include <iostream>
#include <cstdlib>
#include "gfxModified.h"



using namespace std;
Digito::Digito(int num, int supX, int supY, int anchoSeg, int altoSeg) : numero(num), superiorIzquierdaX(supX), superiorIzquierdaY(supY), anchoSegmento(anchoSeg), altoSegmento(altoSeg)
{
	switch(numero){
		case 0:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = false;
			break;
		case 1:
		 	segmentoA = false;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = false;
			segmentoG = false;
			break;
		case 2:
			segmentoA = true;
			segmentoB = true;
			segmentoC = false;
			segmentoD = true;
			segmentoE = true;
			segmentoF = false;
			segmentoG = true;
			break;
		case 3:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = false;
			segmentoF = false;
			segmentoG = true;
			break;

		case 4:
			segmentoA = false;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;

		case 5:
			segmentoA = true;
			segmentoB = false;
			segmentoC = true;
			segmentoD = true;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;
		case 6:
			segmentoA = true;
			segmentoB = false;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = true;
			break;
		case 7:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = false;
			segmentoG = false;
			break;
		case 9:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;
		default:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = true;
	}
}

void Digito::dibujaDigito()
{
	if(segmentoA)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX + altoSegmento, superiorIzquierdaY, anchoSegmento, altoSegmento);
	if(segmentoB)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX + altoSegmento + anchoSegmento, superiorIzquierdaY + altoSegmento, altoSegmento, anchoSegmento);
	
	if(segmentoC)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX + altoSegmento + anchoSegmento, superiorIzquierdaY + anchoSegmento + (2 * altoSegmento), altoSegmento, anchoSegmento);
	
	if(segmentoD)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX + altoSegmento, superiorIzquierdaY + anchoSegmento + (2 * altoSegmento) + anchoSegmento, anchoSegmento, altoSegmento);
	
	if(segmentoE)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX, superiorIzquierdaY + anchoSegmento + (2 * altoSegmento), altoSegmento, anchoSegmento);
	
	if(segmentoF)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX, superiorIzquierdaY + altoSegmento, altoSegmento, anchoSegmento);
	
	if(segmentoG)
		gfx_color(0,0,200);
	else
		gfx_color(0,0,0);

		gfx_fill_rectangle( superiorIzquierdaX + altoSegmento, superiorIzquierdaY + altoSegmento + anchoSegmento, anchoSegmento, altoSegmento);
	
}

void Digito::setNumero(int num)
{
	numero = num;
	switch(numero){
		case 0:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = false;
			break;
		case 1:
		 	segmentoA = false;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = false;
			segmentoG = false;
			break;
		case 2:
			segmentoA = true;
			segmentoB = true;
			segmentoC = false;
			segmentoD = true;
			segmentoE = true;
			segmentoF = false;
			segmentoG = true;
			break;
		case 3:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = false;
			segmentoF = false;
			segmentoG = true;
			break;

		case 4:
			segmentoA = false;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;

		case 5:
			segmentoA = true;
			segmentoB = false;
			segmentoC = true;
			segmentoD = true;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;
		case 6:
			segmentoA = true;
			segmentoB = false;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = true;
			break;
		case 7:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = false;
			segmentoG = false;
			break;
		case 9:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = false;
			segmentoE = false;
			segmentoF = true;
			segmentoG = true;
			break;
		default:
			segmentoA = true;
			segmentoB = true;
			segmentoC = true;
			segmentoD = true;
			segmentoE = true;
			segmentoF = true;
			segmentoG = true;
	}
}
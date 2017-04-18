#include "DisplaySegmentos.h"
#include "gfxModified.h"
#include <stdio.h>

Coordenada DisplaySegmentos::segmentos[];


DisplaySegmentos::DisplaySegmentos()
{	
	for(int i = 0; i < 7; i++)
		seg_on[i] = true;
	iniciarCoord();
}

DisplaySegmentos::DisplaySegmentos(bool so[])
{
	for(int i = 0; i < 7; i++)
		seg_on[i] = so[i];
	iniciarCoord();
}


void DisplaySegmentos::iniciarCoord()
{
	segmentos[0] = Coordenada(WIDTH, 0);
	segmentos[1] = Coordenada(WIDTH + LENGTH , WIDTH);
	segmentos[2] = Coordenada(WIDTH + LENGTH , 2* WIDTH + LENGTH);
	segmentos[3] = Coordenada(WIDTH, 2 * ( WIDTH + LENGTH ) );
	segmentos[4] = Coordenada( 0 , 2* WIDTH + LENGTH);
	segmentos[5] = Coordenada( 0 , WIDTH);
	segmentos[6] = Coordenada( WIDTH, WIDTH + LENGTH );
}

Coordenada DisplaySegmentos::get( char c )
{
	if( (c - 'A') > 0 && (c - 'A') < 7)
		return segmentos[c - 'A'];
	return Coordenada();
}

void DisplaySegmentos::dibujar(int o_x, int o_y)
{
	//printf("Dibujando numero\n");
	for(int i = 0; i < 7; i++)
		if(seg_on[i])
		{
			gfx_fill_rectangle(segmentos[i].obtenerX() + o_x, segmentos[i].obtenerY() + o_y, (i%3) ? WIDTH : LENGTH, (i%3) ? LENGTH : WIDTH);
			//printf("Dibujando segemento: %d %d\n", segmentos[i].obtenerX(), segmentos[i].obtenerY());
			gfx_flush();
		}
}
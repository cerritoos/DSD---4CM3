
#include "gfxModified.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <stdbool.h>
using namespace std;

#define PI 3.1416
int main()
{
	int ysize = 600;
	int xsize = 800;

	char c;

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Grafica Fourier");

	// Set the current drawing color to green.
	gfx_color(0,200,100);

	// Dibuja el plano carteciano
	gfx_line(xsize/2,0,xsize/2,ysize);
	gfx_line(0,ysize/2,xsize,ysize/2);

	//blue
	gfx_color(0,0,200);
	for (int j= 1; j < 6; j+=2)
	{
		for (float i = -PI; i < PI; i+=.0001)
		{
			int x,y=0;
			x=i*100+xsize/2;

			for (int n = 1; n <= j; n+=2)
			{
				float bn=4/(PI*n);
				float y_aux=-1*(bn*sin(n*i)*200);
				y+=y_aux;
			}
			gfx_point(x, y+ysize/2);
		}
	}

	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}

	return 0;
}
#include <stdio.h>
#include <math.h>

int main()
{
	double i=0,seno=0,coseno=0,tangente=0,logaritmo=0,raizCuad=0;
	double max = 1000000;
	while(i<max)
	{
		seno+= sin(i);
		coseno += cos(i);
		tangente += tan(i);
		logaritmo += log10(i);
		raizCuad += sqrt(i);
		i++;
	}
	return 0;
}
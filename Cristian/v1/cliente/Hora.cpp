#include "Hora.h"
#include <sys/time.h>
#include <iostream>

using namespace std;


/* Crea un nuevo objeto con la hora actual del sistema */
Hora::Hora()
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	seg = tv.tv_sec % 60;
	min = (tv.tv_sec)/ 60 % 60;
	hr = ( tv.tv_sec)/3600 % 24;
	dec = (tv.tv_usec/10000) % 10;

}

/* Crea una hora con los parámetros especificados */
Hora::Hora(short h, short m, short s, short d)
{
	hr = h;
	min = m;
	seg = s;
	dec = d;
}


short Hora::getHr()
{	return hr;	}

short Hora::getMin()
{	return min;	}

short Hora::getSeg()
{	return seg;	}

short Hora::getDec()
{	return dec;	}

void Hora::setHr(short h)
{	hr = h;	}

void Hora::setMin(short m)
{	min = m;	}

void Hora::setSeg(short s)
{	seg = s; }

void Hora::setDec(short d)
{	dec = d;	}

char * Hora::toString()
{
	char * hora = new char[10];
	

	hora[0] = (hr/10)%10 + '0';
	hora[1] = hr%10 + '0';




	hora[2] = ':';

	hora[3] = (min/10)%10 + '0';
	hora[4] = min%10 + '0';

	hora[5] = ':';

	hora[6] = (seg/10)%10 + '0';
	hora[7] = seg%10 + '0';

	hora[8] = ':';

	hora[9] = dec+ '0';

	return hora;
}








#include "Fecha.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Fecha::Fecha(int dd, int mm, int aaaa) : dia(dd),  mes(mm), anio(aaaa) 
{
	if(dia > 31 || dia < 1)
	{
		cout << "Valor ilegal para el dia" << endl;
		exit(1);
	}

	if(anio < 0 || anio > getCurrentYear())
	{
		cout << "Valor ilegal para el año" << endl;
		exit(1);	
	}
}

void Fecha::inicializaFecha(int dd, int mm, int aaaa)
{
	anio = aaaa;
	mes = mm;
	dia = dd;   
	return;
}

void Fecha::muestraFecha()
{
	cout << "La fecha es(dia-mes-año):" << dia << "-" << mes << "-" << anio << "\n";
	return;   
}

int Fecha::convierte()
{
	int i;
	i=anio*10000+mes*100+dia;
	//cout << "convierte: " << i << "\n";
	return i;
}

bool Fecha::leapyr()
{
	bool b=false;
	if (anio%400==0)
	{
		b=true;
	}
	if (anio%4==0&&anio%100!=0)
	{
		b=true;
	}
	cout << anio <<" bisiesto: " << b << "\n";
	return b;
}

int Fecha::getCurrentYear()
{
	time_t t = time(0);
	struct tm * now = localtime(&t);
	return (int)(now->tm_year + 1900);
}


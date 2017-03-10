#include "Fecha.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 1000000
using namespace std;


int masVieja(Fecha & f1, Fecha & f2)
{
	if(f1.convierte() > f2.convierte())
		return 1;
	if(f1.convierte() < f2.convierte())
		return -1;
	return 0;
}



int main()
{
	srand(time(0));
   for(int i = 0; i < N; i++)
   {
   		
   		int dia1 = (int)(rand()%31L + 1);
   		int dia2 = (int)(rand()%31L + 1);

   		int mes1 = (int)(rand()%12L + 1);
   		int mes2 = (int)(rand()%12L + 1);

   		int anio1 = (int)(rand()%2017L + 1);
   		int anio2 = (int)(rand()%2017L + 1);

   		Fecha f1(dia1, mes1, anio1);
   		Fecha f2(dia2, mes2, anio2);

   		masVieja(f1,f2);
   		//f1.muestraFecha();
   		//f2.muestraFecha();

   		//cout << masVieja(f1, f2) << endl;

   }
   Fecha f1 = Fecha(2,3,4);
   cout << sizeof(&f1) << endl;
   cout <<sizeof(f1) << endl;
}
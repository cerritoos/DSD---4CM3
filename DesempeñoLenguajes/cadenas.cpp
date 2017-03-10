#include <iostream>
#include <ctime>
#include <cstdlib>

#define ESP ' '
#define TOKENS 351520 
#define NEEDLE "IPN"
#define TOKEN_LEN 4

using namespace std;

string cadena;
void generar_cadena();
int buscar_cadena();

int main()
{
	generar_cadena();
	//cout << "Cadena generada" << endl;
	//cout << cadena.length() << endl;
	cout <<	buscar_cadena() << endl;
	return 0;
}

void generar_cadena()
{
	char a, b, c;
	srand(time(NULL));
	//cout << "Generando cadena" << endl;
	for(int i = 0; i < TOKENS; i++)
	{
		a = rand()%26 + 'A';
		b = rand()%26 + 'A';
		c = rand()%26 + 'A';

		cadena = cadena + a + b + c + ESP;
	}
}

int buscar_cadena()
{
	int pos = 0;
	int found = 0;
	int times_found = 0;
	//int size = cadena.length();
	//cout << "SIZE : " << size << endl;

	while( found != -1	)
	{
		found = cadena.find(NEEDLE, pos);
		if(found > 0)
		{
			pos += found + TOKEN_LEN;
			times_found++;
		}

	}

	return times_found;
}
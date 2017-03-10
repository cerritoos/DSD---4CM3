#include <iostream>
#include <ctime>
#include <cstdlib>

#define ESP ' '
#define TOKENS 70304
#define NEEDLE "IPN"
#define TOKEN_LEN 4

using namespace std;

string cadena;
void generar_cadena();
int buscar_cadena();

int main()
{
	srand(time(NULL));
	generar_cadena();
	//cout << "Cadena generada" << endl;
	//cout << cadena.length() << endl;
	cout <<	buscar_cadena() << endl;
	return 0;
}

void generar_cadena()
{
	char a, b, c;

	for(int i = 0; i < TOKENS; i++){
		a = rand()%26 + 'A';
		b = rand()%26 + 'A';
		c = rand()%26 + 'A';

		cadena += a;
		cadena += b;
		cadena += c;
		cadena += ESP; 
	}
}

int buscar_cadena()
{
	int pos = 0;
	int found = -2;
	int times_found = 0;
	//int size = cadena.length();
	//cout << "SIZE : " << size << endl;

	while( found != -1	)
	{
		found = cadena.find(NEEDLE, pos);
		if(found > -1)
		{
			pos = found + TOKEN_LEN;
			times_found++;
		}

	}

	return times_found;
}
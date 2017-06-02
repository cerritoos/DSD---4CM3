#include "SocketMulticast.h"
#include <iostream>
#include<thread>

using namespace std;

#define MULT_ADDR "225.12.12.12"
#define EVER 1

int puerto = 7200;
void escucha();
void anuncia();

SocketMulticast s(7200);

int main()
{
	
	s.setMulticast(3);
	s.joinMulticast(MULT_ADDR);

	thread hilo_anuncia = thread(anuncia);
	thread hilo_escucha = thread(escucha);
	hilo_escucha.join();
	hilo_anuncia.join();

	

	return 0;


}

void anuncia(){
	char * mensaje = "HOla mundo\n";
	PaqueteDatagrama p(mensaje, sizeof(mensaje), MULT_ADDR, puerto);

	s.envia(p);
	cout << "Mensaje enviado" << endl;
	return;
}


void escucha()
{
	for(;EVER;)
	{
		PaqueteDatagrama p(100);
		s.recibe(p);
		cout << "Se ha recibido algo: " << p.obtieneDatos() << endl;

	}
}
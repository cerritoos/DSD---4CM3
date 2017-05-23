#include <errno.h>
#include "SocketDatagrama.h"
#include <iostream>
#include <stdlib.h>
#include <thread>

#define INICIO "192.168.0.100"
#define FIN "192.168.0.133"
#define EVER 1


using namespace std;

void envia(SocketDatagrama s);
void recibe(SocketDatagrama s);

int main(int argc, char * argv[])
{
	SocketDatagrama s(0);
	s.unsetTimeout();	
	thread t2 = thread(recibe, s);
	thread t1 = thread(envia, s);
	t1.join();
	t2.join();
}

void envia(SocketDatagrama s)
{
	PaqueteDatagrama pd(10);

	in_addr_t IP_inicio = inet_addr(INICIO);
	in_addr_t inc = inet_addr("0.0.0.1");
	in_addr_t IP_fin = inet_addr(FIN);
	in_addr_t IP_act;

	//cout << "Enviando solicitudes a todas las IPs" << endl;
	
	int ips_activas = 0;

	sleep(1);
	for(IP_act = IP_inicio; IP_act != IP_fin; IP_act += inc)
	{
		struct in_addr dir;
		dir.s_addr = IP_act;		

		int num[2] = {2,3};

		PaqueteDatagrama p( (char *)num, 8, inet_ntoa(dir), 7200);
		cout << "Enviando a: " << inet_ntoa(dir) << endl;
		s.envia(p);
		sleep(1);
	}


	cout << "Servidores activos: " << ips_activas << endl;
	return;
}

void recibe(SocketDatagrama s)
{
	PaqueteDatagrama pd(10);

	in_addr_t IP_inicio = inet_addr(INICIO);
	in_addr_t inc = inet_addr("0.0.0.1");
	in_addr_t IP_fin = inet_addr(FIN);
	in_addr_t IP_act;

	//cout << "Recibiendo solicitudes a todas las IPs" << endl;
	
	int ips_activas = 0;

	for(;EVER;)
	{
		struct in_addr dir;
		dir.s_addr = IP_act;		

		PaqueteDatagrama p( (char *)"HOLA", 8, inet_ntoa(dir), 7200);

		int n = s.recibe(p);

		if(n > 0)
		{
			cout << "Respuesta desde " << p.obtieneDireccion() << endl;
			ips_activas++;
		}
		else
			cout << inet_ntoa(dir) << " no ha respondido" << endl;
	}


	cout << "Servidores activos: " << ips_activas << endl;

	return;
}
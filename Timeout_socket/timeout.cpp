#include <errno.h>
#include "SocketDatagrama.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[])
{

	PaqueteDatagrama pd(10);

	in_addr_t IP_inicio = inet_addr(argv[1]);
	in_addr_t inc = inet_addr("0.0.0.1");
	in_addr_t IP_fin = inet_addr(argv[2]);
	in_addr_t IP_act;


	SocketDatagrama s(0);
	s.setTimeout(0,500000);

	cout << "Enviando solicitudes a todas las IPs" << endl;
	
	int ips_activas = 0;


	for(IP_act = IP_inicio; IP_act != IP_fin; IP_act += inc)
	{
		struct in_addr dir;
		dir.s_addr = IP_act;		

		int num[2] = {2,3};

		PaqueteDatagrama p( (char *)num, 8, inet_ntoa(dir), 7200);
		s.envia(p);

		int n = s.recibeTimeout(p);

		if(n > 0)
		{
			cout << "Respuesta desde " << p.obtieneDireccion() << endl;
			ips_activas++;
		}
		//else
		//	cout << inet_ntoa(dir) << " no ha respondido" << endl;
	}


	cout << "Servidores activos: " << ips_activas << endl;

	/*struct in_addr dir;
	dir.s_addr = IP_act;

	cout << inet_ntoa(dir) << endl;
	//cout << inet_addr("192.168.0.100") << endl;
	//cout << inet_addr("192.168.0.101") << endl;*/


	return 0;
}
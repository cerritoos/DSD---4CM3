#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include "mensajes.h"
#include "hilos.h"
#include <iostream>
#include <thread>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <set>
#include <map>
#include <string>
//#include <pair>

using namespace std;


string MULT_ADDR = "225.12.12.12";
int PTO_MULTICAST= 7200;
int PTO_UNICAST = 7300;
int EVER = 1;

SocketMulticast sMulti(PTO_MULTICAST);
SocketDatagrama sUni(PTO_UNICAST);

set<string> IP_activas;
set<string>::iterator i_ips;
string IP_local;
bool solicitando_retrans = false;
string dir;
string dir1;




int main(int argc, char * argv[])
{
	
	IP_local = argv[1];
	dir = argv[2];
	dir1 = argv[3];

	cout << "La ruta es : " << dir << endl;
	cout << "La ruta es : " << dir1 << endl;

	sMulti.setMulticast(3);
	sMulti.joinMulticast(MULT_ADDR.c_str());

	thread hilo_anuncia = thread(anuncia);
	thread hilo_escuchaMulti = thread(escuchaMulticast);
	thread hilo_escuchaUni = thread(escuchaUnicast);
	thread hilo_busca = thread(busca);
	
	hilo_escuchaMulti.join();
	hilo_anuncia.join();
	hilo_busca.join();
	hilo_escuchaUni.join();


	return 0;


}


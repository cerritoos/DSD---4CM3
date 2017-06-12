#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // inet_ntoa()
#include <netinet/in.h> // ntohs()
#include <netdb.h>
#include <unistd.h> 

using namespace std;

SocketDatagrama::SocketDatagrama(int pto){
	s=socket(AF_INET,SOCK_DGRAM,0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	direccionLocal.sin_family=AF_INET;
	direccionLocal.sin_addr.s_addr=inet_addr("192.168.0.105");
	direccionLocal.sin_port=htons(pto);
	bind(s, (struct sockaddr *) &direccionLocal, sizeof(direccionLocal));
}


int SocketDatagrama::recibe(PaqueteDatagrama &p){
	int clien = sizeof(direccionForanea);
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
	int n= recvfrom(s, p.obtieneDatos() , p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, (socklen_t*) &clien);
	char* port=inet_ntoa(direccionForanea.sin_addr);
	p.inicializaIp(port);
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	return n;
}

int SocketDatagrama::envia(PaqueteDatagrama &p){
	int clien = sizeof(direccionForanea);
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());
	int n = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, clien);
	return n;
}

SocketDatagrama::~SocketDatagrama(){
	close(s);
}

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
#include <errno.h>
#include <sys/time.h>


using namespace std;

SocketDatagrama::SocketDatagrama(int pto){
	s=socket(AF_INET,SOCK_DGRAM,0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	direccionLocal.sin_family=AF_INET;
	direccionLocal.sin_addr.s_addr=htonl(INADDR_ANY);
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


void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos)
{
	tiempofuera.tv_sec=segundos;
	tiempofuera.tv_usec=microsegundos;
	setsockopt(s,SOL_SOCKET, SO_RCVTIMEO,(char*)&tiempofuera, sizeof(tiempofuera));
	timeout=1;

}
void SocketDatagrama::unsetTimeout()
{
	tiempofuera.tv_sec=0;
	tiempofuera.tv_usec=0;
	setsockopt(s,SOL_SOCKET, SO_RCVTIMEO,(char*)&tiempofuera, sizeof(tiempofuera));
	timeout=0;

}
int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p)
{
	int clien = sizeof(direccionForanea);
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
	gettimeofday(&tiempo1,NULL);
	int n= recvfrom(s, p.obtieneDatos() , p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, (socklen_t*) &clien);
	gettimeofday(&tiempo2,NULL);
	timersub(&tiempo2,&tiempo1,&resultado);
	printf("\nresultado: %ld %ld\n", resultado.tv_sec,resultado.tv_usec);
	char* port=inet_ntoa(direccionForanea.sin_addr);
	p.inicializaIp(port);
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));

	if (n < 0) {
		if (errno == EWOULDBLOCK)
		fprintf(stderr, "Tiempo para recepción transcurrido\n");
		else
		fprintf(stderr, "Error en recvfrom\n");
	}

	return n;
}
SocketDatagrama::~SocketDatagrama(){
	close(s);
}

#include "SocketMulticast.h"
#include <iostream>

using namespace std;


SocketMulticast :: SocketMulticast(int puerto){
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
   	direccionLocal.sin_family = AF_INET;
   	direccionLocal.sin_addr.s_addr = INADDR_ANY;
   	direccionLocal.sin_port = htons(puerto);
   	bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketMulticast :: ~SocketMulticast(){
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	close(s);
}

int SocketMulticast::setMulticast(unsigned char ttl)
{
	TTL = ttl;
	return setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL, sizeof(TTL));
}

int SocketMulticast::joinMulticast(char * ip_multicast)
{
	struct ip_mreq multicast;

	multicast.imr_multiaddr.s_addr = inet_addr(ip_multicast);
	multicast.imr_interface.s_addr = INADDR_ANY;

	return setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&multicast, sizeof(multicast));
}

int SocketMulticast::recibe(PaqueteDatagrama &p){
	socklen_t clilen =  sizeof(direccionForanea);
	int r = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	inet_ntop(AF_INET, &(direccionForanea.sin_addr), p.obtieneDireccion(), INET_ADDRSTRLEN);
	:: cout << "\n"<< p.obtieneDireccion() << " - "<< p.obtienePuerto() << " dice: " << p.obtieneDatos() << std :: endl;
	return r; 
}

int SocketMulticast::envia(PaqueteDatagrama &p){
	socklen_t clilen =  sizeof(direccionForanea);
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   	direccionForanea.sin_family = AF_INET;
   	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   	direccionForanea.sin_port = htons(p.obtienePuerto());
	int r = sendto(s,(char *) p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
	//std :: cout << "Direccion IP del paquete a enviar: " << p.obtieneDireccion() << std :: endl;
	//std :: cout << "Puerto del paquete enviado: " << p.obtienePuerto() << std :: endl;
	return r;
}

void SocketMulticast::setTimeout(time_t segundos, suseconds_t microseconds)
{
	s_timeout.tv_sec = segundos;
	s_timeout.tv_usec = microseconds;

	timeout = true;

	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&s_timeout, sizeof(s_timeout));

}

void SocketMulticast::unsetTimeout()
{
	timeout = false;
	s_timeout.tv_sec = 0;
	s_timeout.tv_usec = 0;

	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&s_timeout, sizeof(s_timeout));
}


int SocketMulticast::recibeTimeout(PaqueteDatagrama &p)
{
	socklen_t clilen =  sizeof(direccionForanea);
	struct timeval t1, t2, res;
	gettimeofday(&t1, NULL);
	int r = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);
	gettimeofday(&t2, NULL);

	

	timersub(&t2, &t1, &res);

	if( r < 0 )
	{
		if (errno == EWOULDBLOCK)
			fprintf(stderr, "Tiempo de espera para recepción transcurrido\n" );
		else
			fprintf(stderr, " Error en recvfrom\n" );
	}
	else
	{
		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
		inet_ntop(AF_INET, &(direccionForanea.sin_addr), p.obtieneDireccion(), INET_ADDRSTRLEN);
		printf("Tiempo transcurrido: %ld seg %ld microsegundos\n", res.tv_sec, res.tv_usec);
	}

	return r; 
}
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SocketDatagrama::SocketDatagrama(int pto)
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if( s  < 0 )
	{
		printf("Error al crear el socket\n");
		exit(1);
	}

	bzero(	(char *)&direccionLocal, sizeof(direccionLocal)	);
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_port = htons(pto);
	direccionLocal.sin_addr.s_addr = INADDR_ANY;

	bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal)); 
}

int SocketDatagrama::recibe(PaqueteDatagrama & p)
{
	unsigned size = sizeof(direccionForanea); 
	int recibido = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &size);
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));
	p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));

	return recibido;
}

int SocketDatagrama::envia(PaqueteDatagrama & p)
{
	unsigned size = sizeof(direccionForanea);
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());

	int enviado = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, size );

	return enviado;
}
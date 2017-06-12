
#include "PaqueteDatagrama.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // inet_ntoa()
#include <netinet/in.h> // ntohs()
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

class SocketDatagrama{
	
public:
	SocketDatagrama(int);
	~SocketDatagrama();
	//Recibe un paquete tipo datagrama proveniente de este socket
	int recibe(PaqueteDatagrama & p);
	//Envía un paquete tipo datagrama desde este socket
	int envia(PaqueteDatagrama & p);
	//configura las opciones del socket
	void setTimeout(time_t segundos, suseconds_t microsegundos);
	//Deja al socket en estado inicial
	void unsetTimeout();

	int recibeTimeout(PaqueteDatagrama &p);

private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	//El time val es para usarlo en setsockopt
	struct timeval tiempofuera;
	struct timeval tiempo1, tiempo2, resultado;
	//Nos dice si el temporizados esta activado o desctivado
	bool timeout;
	int s; //ID socket
};

#endif

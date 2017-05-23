
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

private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	int s; //ID socket
};

#endif

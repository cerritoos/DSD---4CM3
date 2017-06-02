#ifndef SOCKETMULTICAST_H_
#define SOCKETMULTICAST_H_

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include "PaqueteDatagrama.h"

#include "PaqueteDatagrama.h"

class SocketMulticast{
public:
	SocketMulticast(int);
	~SocketMulticast();
	int envia(PaqueteDatagrama &p);
	int recibe(PaqueteDatagrama &p);
	int setMulticast(unsigned char ttl);
	int joinMulticast(char * ip_multicast);
	void setTimeout(time_t segundos, suseconds_t microseconds);
	void unsetTimeout();
	int recibeTimeout(PaqueteDatagrama &p);
	unsigned char TTL;
private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	struct timeval s_timeout;
	bool timeout;
	int s; //ID socket

};


#endif
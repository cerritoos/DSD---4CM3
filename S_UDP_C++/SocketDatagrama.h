#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

#include "PaqueteDatagrama.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>

class SocketDatagrama{
public:
	SocketDatagrama(int);
	~SocketDatagrama();
	int recibe(PaqueteDatagrama & p);
	int envia(PaqueteDatagrama & p);

private:
	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	int s; //	ID socket

};

#endif
#ifndef __SocketDatagrama__
#define __SocketDatagrama__
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "PaqueteDatagrama.h"
#include <arpa/inet.h>
class SocketDatagrama{
public:
SocketDatagrama(int=0);
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

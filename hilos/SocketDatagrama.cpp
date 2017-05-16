#include "SocketDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
using namespace std;
SocketDatagrama::SocketDatagrama(int puerto){
  s = socket(AF_INET, SOCK_DGRAM, 0);
bzero((char *)&direccionLocal, sizeof(direccionLocal));
direccionLocal.sin_family = AF_INET;
direccionLocal.sin_addr.s_addr = INADDR_ANY;
direccionLocal.sin_port = htons(puerto);
bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}
SocketDatagrama::~SocketDatagrama(){
  //close(s);
}

int SocketDatagrama::recibe(PaqueteDatagrama & p){
  unsigned int addr_len = sizeof(direccionForanea);
     bzero((char *)&direccionForanea, sizeof(direccionForanea));
     int respuesta = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
     p.inicializaPuerto(ntohs(direccionForanea.sin_port));
     p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
  return respuesta;
}
int SocketDatagrama::envia(PaqueteDatagrama & p){
  bzero((char *)&direccionForanea, sizeof(direccionForanea));
  direccionForanea.sin_family = AF_INET;
  direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
  direccionForanea.sin_port = htons(p.obtienePuerto());
  return sendto(s,p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}

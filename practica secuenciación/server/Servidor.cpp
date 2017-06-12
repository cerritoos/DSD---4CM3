#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // inet_ntoa()
#include <netinet/in.h> // ntohs()
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

using namespace std;
int puerto = 7200;
char *dato=NULL;

struct mensaje{
   uint32_t secuencia;
   uint32_t solicitud[2];
   uint32_t respuesta;
};

int main(void) {
   struct mensaje peticion;
   char msj[50], msj_cliente[50];
   int num[2];
   int res;

   SocketDatagrama servidor(puerto);
   PaqueteDatagrama pk_recv(sizeof(peticion));
   
   cout << "Servidor iniciado... Esperando clientes" << endl;
   strcpy(msj, "");
//   sprintf(msj, "%s", "Que tal cliente");

   while(1) {
	int n= servidor.recibe(pk_recv);
	char *ip_cliente= pk_recv.obtieneDireccion();
	int pto_cliente= pk_recv.obtienePuerto();
	cout << "Mensaje recibido de cliente " << ip_cliente << ":" << pto_cliente << endl;
   memcpy(&peticion, pk_recv.obtieneDatos(),pk_recv.obtieneLongitud());
   peticion.respuesta= peticion.solicitud[0]+peticion.solicitud[1];
	cout << "Mensaje: " << peticion.respuesta<< endl;  
   //dato=pk_recv.obtieneDatos(); 
  // cout<<"jojo: "<<dato[0]<<" "<<dato[1]<<endl ;
   //num[0]=dato[0];
   //cout<<num[0]<<endl;
sprintf(msj, "%s%s",pk_recv.obtieneDatos(), "Solicitud recibida");
   //num[1]=dato[1];
   //cout<<num[1]<<endl;
   //res=(int)dato[0]+(int)dato[1];
   //cout<<res;
   //msj[0]=res;
   PaqueteDatagrama pk_send((char*)&peticion, sizeof(peticion), ip_cliente, pto_cliente);	
	cout << "Enviando mensaje..." << endl;
	int m= servidor.envia(pk_send);
   }

return 0;
}


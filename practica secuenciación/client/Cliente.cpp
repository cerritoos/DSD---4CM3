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
int puerto = 8085;
int pto_server = 7200;
//char *ip_server= "192.168.0.123";
char ip_server[16]="192.168.0.105";
char *p;
int intentos=0;

struct mensaje 
{
   uint32_t secuencia; //Número de secuencia
   uint32_t solicitud[2]; //pareja de números enviados por el cliente para su suma
   uint32_t respuesta; //respuesta enviada por el servidor
};

int main(void) {
   char msj[50];
   char num[3];
   char prueba[3];
   //p=prueba[0];
   SocketDatagrama cliente(puerto);
   cliente.setTimeout(2,500000);
  // cin>>num;
   strcpy(msj, "");
   sprintf(msj, "%s", "hola Diego");
   //ip_server[10]="h";
   //cout<<"ip: "<<ip_server<<endl;
   //cout<<"esta es la ip del servidor" <<ip_server[10]<<ip_server[11]<<ip_server[12]<<endl;
  
   PaqueteDatagrama pk_send2(msj, sizeof(msj), ip_server, pto_server);	
   int m= cliente.envia(pk_send2);
   cout << "Mensaje enviado" << endl;


   PaqueteDatagrama pk_recv2(sizeof(msj));
      while(intentos<7)
      {
      int n= cliente.recibeTimeout(pk_recv2);
      if (n>=0)
      {
      	/* code */
      char *ip_serv= pk_recv2.obtieneDireccion();
      char *msj_serv= pk_recv2.obtieneDatos();
      int pto_serv= pk_recv2.obtienePuerto();
      cout << "Mensaje recibido de servidor: " << ip_serv << ":" << pto_serv << endl;
      cout << "Servidor said: " << msj_serv << endl;
      intentos=7;
      }
      else
      {
         cout<<"no se ha podido establecer conexión con el server... :("<<endl;
         intentos++;
      }
      }
   
//   cliente.~SocketDatagrama();
return 0;
}


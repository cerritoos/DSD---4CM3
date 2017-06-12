#include <fcntl.h>
#include <dirent.h>
#include <map>
#include <string>
#include <fcntl.h>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include "mensajes.h"
#include "hilos.h"
#include "archivo.h"

extern string MULT_ADDR;
extern SocketMulticast sMulti;
extern SocketDatagrama sUni;
extern set<string> IP_activas;
extern string IP_local;
extern bool solicitando_retrans;

extern int PTO_MULTICAST;
extern int EVER;

extern string dir;
extern string dir1;

/* Mantener control de las eliminaciones */
extern map<string, int> elim_ack;

extern set<string>::iterator i_ips;

set <string> archivos;
set<string>::iterator i = archivos.begin();
set<string> trash;
set<string>::iterator j=trash.begin();


void anuncia(){
	
	/* Enviar un mensaje anunciando su presencia en la red */
	Mensaje m;
	m.opcode = 0;
	PaqueteDatagrama p((char *)&m, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST);
	sMulti.envia(p);
	cout << "Mensaje de union enviado" << endl;
	return;
}


void escuchaMulticast()
{
	

	for(;EVER;)
	{
		PaqueteDatagrama p(1120);
		sMulti.recibe(p);
		Mensaje msj;
		memcpy(&msj, p.obtieneDatos(), sizeof(Mensaje));
		cout << "Se ha recibido algo: " << msj.opcode << " de: " << p.obtieneDireccion() << endl;

		/* Si el remitente es la dirección local, se ignora el mensaje */
		if(!IP_local.compare(p.obtieneDireccion())) continue;

		switch(msj.opcode)
		{
			/* Se ha unido un nuevo nodo */
			case UNION:
				enviar_unionAck(p.obtieneDireccion());

			break;
			
			case NUEVO:
				archivos.insert(msj.filename);
				cout << "Hay un archivo nuevo: " << msj.filename << endl;
				crear_archivo(msj.filename);
				solicitar_archivo(msj.filename, p.obtieneDireccion(), 0);
			break;

			case ELIMINACION:
				eliminar_archivo(msj.filename);
				cout << "Archivo eliminado" << endl;

			break;
/*			case RETRANS_SOL:
				//retransmitir_archivo(msj);

			break;*/
			/*case ELIMIN_ACK:
				if( elim_ack.find(msj.filename) == elim_ack.end() ) continue;

				if(++elim_ack[msj.filename] == IP_activas.size() - 1)
					eliminar_archivo(msj.filename);
			break;*/
		}
	}
}

void busca()
{
	DIR * directorio;
	struct dirent *elemento;
	string elem;
	DIR * directorio_trash;
	struct dirent *elemento_trash;
	string elem_trash;
	
	archivos.clear();
	trash.clear();
	for(;EVER;)
	{
		
		i=archivos.begin();
		j=trash.begin();
		if(directorio=opendir(dir.c_str()))
		{
			while(elemento=readdir(directorio))
			{
	 			if(string(elemento->d_name)=="." || string(elemento->d_name)=="..")
					continue;

				if ( archivos.find(elemento->d_name) == archivos.end() )
				{
					cout << "Hay un archivo nuevo en la carpeta local " << endl;
					archivos.insert(i,elemento->d_name);
					notificar_archivo(elemento->d_name);
				}
		
			}
		}

		if(directorio_trash=opendir(dir1.c_str()))
		{
			while(elemento_trash=readdir(directorio_trash))
			{
				if(string(elemento_trash->d_name)=="."||string(elemento_trash->d_name)=="..")
					continue;
				//trash.insert(j,elemento_trash->d_name);
				
				cout << "Hay un archivo nuevo en la carpeta Trash local " << endl;

				if ( trash.find(elemento_trash->d_name) == trash.end() )
				{
					cout << "HOLA 2" << endl;
					trash.insert(j,elemento_trash->d_name);
					notificar_eliminacion(elemento_trash->d_name);
					//eliminar_archivo(elemento->d_name);
					eliminar_trash(elemento_trash->d_name);
					archivos.erase(archivos.find(elemento_trash->d_name));
				}
				
				//elim_ack.insert( pair<string, int>(elemento_trash->d_name, 0));

			}
		}

		
		j=trash.begin();
		i=archivos.begin();

		
		while(i != archivos.end()) cout<< *i++<<endl;
		while(j != trash.end()) cout<< *j++<<endl;

		closedir(directorio);
		closedir(directorio_trash);
		sleep(5);
	}
}

void escuchaUnicast()
{
	for(;EVER;)
	{
		PaqueteDatagrama p(1120);
		sUni.recibe(p);
		Mensaje msj;
		memcpy(&msj, p.obtieneDatos(), sizeof(Mensaje));
	
		cout << "Se ha recibido algo (Unicast) " << msj.opcode << " de: " << p.obtieneDireccion() << endl;

		switch(msj.opcode)
		{
			
			case UNION_ACK:
				//cout<< "Hay un nuevo nodo en la red: " << p.obtieneDireccion() << endl;
				IP_activas.insert(p.obtieneDireccion());

				/*for ( i_ips = IP_activas.begin(); i_ips != IP_activas.end(); i_ips++)
					cout << "Enviado a: " << *i_ips << endl;
				fflush(stdout);*/
			break;

			case SOLICITUD_ARCH:
				enviar_archivo(msj, p.obtieneDireccion());
			break;

			case ENVIO_ARCH:
				cout << "Archivo recibido " << endl;
				guardar_archivo(msj, p.obtieneDireccion());
			break;


			/* Se ha recibido la solicitud deseada */
			/*case RETRANSMISION:
				if (!solicitando_retrans) break;

			break;*/

			/*case RETRANS_SOL:
				//retransmitir_archivo(msj);

			break;
			case ELIMIN_ACK:
				if( elim_ack.find(msj.filename) == elim_ack.end() ) continue;

				if(++elim_ack[msj.filename] == IP_activas.size() - 1)
					eliminar_archivo(msj.filename);
			break;*/

		}
	}	
}
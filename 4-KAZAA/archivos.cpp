#include <set>
#include <fcntl.h>
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>

using namespace std;

#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include "mensajes.h"
#include "archivo.h"

extern string MULT_ADDR;

extern SocketMulticast sMulti;
extern SocketDatagrama sUni;
extern set<string> IP_activas;
extern string IP_local;
extern bool solicitando_retrans;

extern int PTO_MULTICAST;
extern int PTO_UNICAST;
extern int EVER;
extern set<string>::iterator i_ips;

extern set <string> archivos;
extern set<string> trash;

/*string dir="./KAZAA";
string dir1="./TRASH";*/

extern string dir;
extern string dir1;
/* Mantener control de las eliminaciones */
map<string, int> elim_ack;

int guardar_archivo(Mensaje m, string ip)
{

	string archivo = dir + '/';
	archivo += m.filename;

	string archivo_simple = m.filename;

	int recv = 0;


	/*if( !m.count ) 
	{
		cout << "Terminando recepcion con m: " << m.count << endl;
		return 1;
	}*/
	sUni.setTimeout(0, 500000);
	int times = 0;

	while( ( m.opcode == ENVIO_ARCH ) && m.count )
	{
		int fd_archivo = open(archivo.c_str(), O_WRONLY, 0666);
		lseek(fd_archivo, m.offset, SEEK_SET);

		if( fd_archivo < 0 )
		{
			cout << "No se pudo abrir archivo " << endl;
			perror("HAy error");
			close(fd_archivo);
			exit(0);
		}

		//cout << "Tratando de escribir a " << archivo << endl;
		cout << "Se han recibido " << m.count << " bytes" << endl;
		cout << "Con offset: " << m.offset << endl;
		//cout << "Los datos: " << m.data << endl;
		int escritos = write(fd_archivo, m.data, m.count);
		/*cout << " Los datos escritos : " << endl;

		for( int i = 0; i < m.count; i++)
			printf("%x%c\n", m.data[i], ( (i +1)% 20 ) ? ' ' : '\n' );
		cout << endl;
		cout << "Se han escrito " << escritos << " bytes" << endl;*/
		close(fd_archivo);
		
		//sleep(1);

		int n_offset = m.offset + m.count;
		do{
//			sleep(1);
			solicitar_archivo(archivo_simple.c_str(), ip, n_offset);
			//cout << "Archivo solicitado con offset: " << n_offset << endl;

			PaqueteDatagrama p_res(1120);
			recv = sUni.recibeTimeout(p_res);
			memcpy( (char *) &m, p_res.obtieneDatos(), sizeof(Mensaje));
		}while(recv < 0);
		//cout << " Pedazo de archivo recibido " << endl;
	}

	sUni.unsetTimeout();
	return 1;
}

int solicitar_retransmision(Mensaje m)
{
	Mensaje mr = m;
	mr.opcode = RETRANSMISION;

	PaqueteDatagrama pr((char *)&mr, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST);
	//sMulti.envia(pr);
	solicitando_retrans = true;
	cout << "Solicitud de retransmision enviada " << endl;
}

int eliminar_archivo(string filename)
{
	string archivoK = dir + '/';
	archivoK += filename; 
	while ( !remove(archivoK.c_str()) );

	archivos.erase(archivos.find(filename));
	/*Mensaje m;
	m.opcode = ELIMIN_ACK;
	memcpy(m.filename, filename.c_str(), MAX_FILENAME);
	PaqueteDatagrama p( (char *)&m, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST );*/
	return 0;
}

void enviar_unionAck(string ip)
{
	Mensaje m;
	m.opcode = UNION_ACK;

	PaqueteDatagrama p2((char *)&m, sizeof(Mensaje), ip.c_str(), PTO_UNICAST  );
	sUni.envia(p2);
	cout << "UNION_ACK ENVIADO a " << ip << endl;
	return;
}

void enviar_archivo(Mensaje m, string ip)
{
	int fd_archivo;

	cout << "El archivo se ha solicitado con offset : " << m.offset << endl;
	//cout << "Enviando archivo a: " << ip << endl;

	string archivo = dir + '/';
	archivo += m.filename;
	/* Si hay un error al abrir el archivo */
	if ( ! (fd_archivo = open(archivo.c_str(), O_RDONLY) ) ) return;
	lseek(fd_archivo, m.offset, SEEK_SET);

	m.opcode = ENVIO_ARCH;

	cout << "Tratando de leer a : "  << archivo << endl;
	bzero(m.data, BUFSIZE);
	int leidos = read(fd_archivo, m.data, BUFSIZE);
	
	cout << "Se han leido " << leidos << endl;
	/*cout << " Los datos enviados : " << endl;

	for( int i = 0; i < leidos; i++)
		printf("%x%c", m.data[i], ( (i + 1)% 20 ) ? ' ' : '\n' );

	cout << endl;*/

	if(leidos < 0)
	{
		perror("Hay error");
		exit(EXIT_FAILURE);
	}
	

	cout << "Se han leido " << leidos  << " bytes" << endl;

	m.count = leidos;


	PaqueteDatagrama p( (char *)&m, sizeof(Mensaje), ip.c_str(), PTO_UNICAST);
	sUni.envia(p);

	cout << "El archivo se ha enviado con offset:" << m.offset << endl;

	close(fd_archivo);
	return;	
}

void notificar_archivo(string filename)
{
	int fd_archivo;
	/* Si hay un error al abrir el archivo */
	Mensaje m;

	m.opcode = NUEVO;
	memcpy(m.filename, filename.c_str(), MAX_FILENAME);

	PaqueteDatagrama p( (char * )&m, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST);
	sMulti.envia(p);

	//char * mensaje = "Ya paren el semestre";


	return;
}

/* Solicitar archivo */
void solicitar_archivo(string filename, string ip, int offset)
{
	Mensaje m;
	m.opcode = SOLICITUD_ARCH;
	m.count = 0;
	m.offset = offset;
	memcpy(m.filename, filename.c_str(), MAX_FILENAME);

	PaqueteDatagrama p( (char *) &m, sizeof(Mensaje), ip.c_str(), PTO_UNICAST);
	sUni.envia(p);
	//cout << "Archivo solicitado " << endl;
}

void crear_archivo(string filename)
{
	string archivo = dir + '/';
	archivo += filename;
	string archivo_simple = filename;	
	int fd_archivo = open(archivo.c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	close(fd_archivo);
	return;
}

void notificar_eliminacion(string name)
{
	Mensaje m;
	m.opcode = ELIMINACION;
	memcpy(m.filename, name.c_str(), MAX_FILENAME);

	PaqueteDatagrama p( (char *)&m, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST );
	sMulti.envia(p);
	return;
}

void eliminar_trash(string filename)
{
	string archivoT = dir1 + '/';
	archivoT += filename; 
	while ( !remove(archivoT.c_str()) );

	trash.erase(trash.find(filename));
	/*Mensaje m;
	m.opcode = ELIMIN_ACK;
	memcpy(m.filename, filename.c_str(), MAX_FILENAME);
	PaqueteDatagrama p( (char *)&m, sizeof(Mensaje), MULT_ADDR.c_str(), PTO_MULTICAST );*/
	return;		
}
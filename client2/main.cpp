#include "header.h"
#include "SocketDatagrama.h"
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


int main(int argc, char * argv[] )
{

	if(argc < 4)
	{
		perror("Número de argumentos inválido");
		exit(EXIT_FAILURE);
	}

	
	char IP_server[16];
	memcpy(IP_server, argv[1], 16);
	//char IP_server[16] = argv[1];
	int puerto = atoi(argv[2]);
	char archivo[MAX_PATH];
	memcpy(archivo, argv[3], MAX_PATH);

	int g_offset = 0, recv_bytes = 1;

	/* Abrir el archivo */
	int fd_archivo;
	if( (fd_archivo = open(archivo, O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
	{
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	SocketDatagrama s(0);
	s.setTimeout(0,500000);

	/* Leer los datos */
	while( recv_bytes )
	{


		Peticion pet;
		Respuesta resp;
		pet.opcode = READ;
		pet.offset = g_offset;
		memcpy(pet.name, archivo, MAX_PATH);

		PaqueteDatagrama p( (char *)&pet, sizeof(resp), IP_server, puerto);
		

		s.envia(p);
		cout << p.obtieneDireccion() << ":" << p.obtienePuerto() << endl;
		cout << pet.name << endl;

		/* Recibir respuesta */
		
		resp.count = 1;
		PaqueteDatagrama p_resp(1050);
		cout<<"El offset es: "<<g_offset<<endl;
		//s.recibe(p_resp);
		int recibido = s.recibeTimeout(p_resp);
		memcpy( (char *)&resp, p_resp.obtieneDatos(), p.obtieneLongitud());
		printf("Bytes recibidos: %d\n", resp.count );
		
		if(recibido < 0)
		{
			resp.count = 1;
			continue;
		}

		if(resp.count < 0)
		{
			perror("Error al leer");	
			exit(EXIT_FAILURE);
		}

		if (resp.count > 0) 
		{

			int escritos = write(fd_archivo, resp.data, resp.count);
			cout << "Escritos: " << escritos << endl;
		}
		g_offset += resp.count;
		recv_bytes = resp.count;
		cout<<"La pet.count es: "<<pet.count<<endl;
	}

	close(fd_archivo);

	return 0;
}
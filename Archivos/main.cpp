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


	/* Leer los datos */
	while( recv_bytes )
	{

		Peticion pet;
		pet.opcode = READ;
		pet.offset = g_offset;
		memcpy(pet.name, archivo, MAX_PATH);

		PaqueteDatagrama p( (char *)&pet, sizeof(pet), IP_server, puerto);
		SocketDatagrama s(0);
		s.envia(p);
		cout << p.obtieneDireccion() << ":" << p.obtienePuerto() << endl;
		cout << pet.name << endl;

		/* Recibir respuesta */
		Respuesta resp;
		resp.count = 1;
		PaqueteDatagrama p_resp(1050);

		s.recibe(p_resp);
		memcpy( (char *)&resp, p_resp.obtieneDatos(), p.obtieneLongitud());
		printf("Bytes recibidos: %d\n", resp.count );
		
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
	}

	close(fd_archivo);

	return 0;
}
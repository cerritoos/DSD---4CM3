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

	
	//char IP_server[16];
	//memcpy(IP_server, argv[1], 16);
	//char IP_server[16] = argv[1];
	int puerto = atoi(argv[2]);
	//char archivo[MAX_PATH];
	//memcpy(archivo, argv[3], MAX_PATH);

	int g_offset = 0, recv_bytes = 1;

	/* Crear el archivo */
	int fd_archivo;
	if( (fd_archivo = open(argv[3], O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
	{
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	close(fd_archivo);

	Peticion pet;
	pet.opcode = READ;
	pet.offset = 0;
	pet.count = 0;
	memcpy(pet.name, argv[3], MAX_PATH);
	cout << "Enviando peticion a: " << argv[1] << endl;
	PaqueteDatagrama p( (char *)&pet, sizeof(pet)+ 20, argv[1], puerto);
	SocketDatagrama s(0);

	Respuesta resp;
	resp.count = 1;
	PaqueteDatagrama p_resp(2000);

	
	while( resp.count )
	{

		/* Enviar peticion */		
		p.inicializaDatos( (char *)&pet);
		s.envia(p);
		cout << p.obtieneDireccion() << ":" << p.obtienePuerto() << endl;
		cout << pet.name << endl;

		/* Recibir respuesta */
		s.recibe(p_resp);
		printf("Bytes en el datagrama: %d\n", p_resp.obtieneLongitud() );
		memcpy( (char *)&resp, p_resp.obtieneDatos(), p_resp.obtieneLongitud());
		printf("Bytes recibidos: %d\n", resp.count );

		fd_archivo = open("umaxO.jpg", O_RDONLY);
		lseek(fd_archivo, pet.offset, SEEK_SET);
		
		/*printf("Datos recibidos:\n" );
		int i = 0;

		for(i = 0; i < p.obtieneLongitud(); i++)
			printf("%d%c", resp.data[i], ((i+1)%20? ' ':'\n'));*/

		if(resp.count < 0)
		{
			perror("Error al leer");	
			exit(EXIT_FAILURE);
		}

		cout << "Holi desde aqui" << endl;
		if (resp.count > 0) 
		{

			int escritos = write(fd_archivo, resp.data, resp.count);
			cout << "Escritos: " << escritos << endl;
		}
		cout << "Holi desde aca" << endl;
		pet.offset += resp.count;

		cout << "Holi desde otro aca" << endl;
		close(fd_archivo);
	}

	cout << "Holi desde ajuera" << endl;
	
	cout << "Otro" << endl;
	/*int fd_archivo = open("umaxO.jpg", O_RDONLY);

	char buffer[BUF_SIZE];
	int rb = 1;
	register int i;
	while(rb)
	{
		rb = read(fd_archivo, buffer, BUF_SIZE);
		for(i = 0; i < rb; i++)
			printf("%d%c", buffer[i], ((i+1)%20? ' ':'\n'));
	}*/

	//return 0;
}
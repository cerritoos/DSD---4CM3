#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/ipc.h>
#include <math.h>
#include <pthread.h>
#include <fcntl.h>

int main(int argc, char **argv){

	int i;
	unsigned nums[3];
	//paso 0
	int puerto, str, sock, n2, desc, opc, tam, recvMsgSize, tempint;
	struct sockaddr_in servidor, cliente; //se pone servidor por que al ser cliente se llenara con los datos del servidor
	int canal, recibido, c=0;

	//paso 1 crear el socket, se usa AF_INET por que no solo se usara localmente, y se usa sock_dgram por que sera con datagramas.
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		printf("Error el crear el socket\n");
		exit(1);
	}

	//paso 2
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(atoi(argv[1]));
	servidor.sin_addr.s_addr = inet_addr(argv[2]);

	cliente.sin_family = AF_INET;
	cliente.sin_port = htons(atoi(argv[3]));
	cliente.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (struct sockaddr *)&cliente, sizeof(cliente));

	int size;

	size = sizeof(struct sockaddr_in);

	printf("esperando rangos...\n");
	//recibimos los parametros de n (inicio - fin)
	if((recibido = recvfrom(sock, &nums, 3*sizeof(unsigned), 0, (struct sockaddr*)&servidor, &size)) < 0){
		printf("\nError al recivir rangos");
		exit(0);
	}
	else
		printf("rango recibido\n");

	short isPrime = 1;
	for(i = nums[1]; i < nums[2]; i++){
		if( !(nums[0]%i) ){
			isPrime = 0;
			break;
		}
	}

	//enviamos la opcion que queremos
	if((n2 = sendto(sock, (char*)&isPrime, sizeof(isPrime), 0, (struct sockaddr*)&servidor, sizeof(struct sockaddr_in))) < 0){
		printf("Error al enviar opc menu\n");
		exit(1);
	}
	else
		printf("respuesta enviada\n");
	
	//paso 5
	close(desc);
}

//4294967295


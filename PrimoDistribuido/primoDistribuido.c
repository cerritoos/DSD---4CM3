/* 
	Programa que recibe un númeor entero por consola
	y una lista de direcciones IP a quiénes distribuir el cálculo 
	de si un número es primo o no.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct in_addr IP;

unsigned validar_entrada( int, char **);
void * reservar_memoria(int n, unsigned);
void asignar_rangos(unsigned, int *);

IP * IPs;
int COMP_NUM;
int * rangos;
char * ip_server = "192.168.43.16";
int pto_server = 8888;
int puertos[20];
float peso [] = {1.10,1.10,1,1,9.05,9.05,9.05,9.05};

int main(int argc, char * argv[])
{
	printf("%u\n", UINT_MAX);
	unsigned num = validar_entrada(argc, argv);
	int i;
	unsigned nums[3];
	short * res;

	rangos = (int *)reservar_memoria(COMP_NUM + 1, sizeof(int));
	res = (short *)reservar_memoria(COMP_NUM, sizeof(short));
	asignar_rangos(num, rangos);

	/*for(i = 0; i < COMP_NUM; i++)
		printf("%d ", puertos[i]);
	printf("\n");

	/* Envio de rangos */
	struct sockaddr_in msg_ser, client_addr;
	int s;

	/* rellena la dirección del servidor*/
	bzero( (char *)&msg_ser, sizeof(msg_ser) );
	msg_ser.sin_family = AF_INET;
	msg_ser.sin_addr.s_addr = inet_addr(ip_server);
	msg_ser.sin_port = htons(pto_server);

	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bind(s, (struct sockaddr *)&msg_ser, sizeof(msg_ser	) );

	/* Enviar los rangos */
	for(i = 0; i < COMP_NUM * 2; i++)
	{
		/* rellenar la dirección del cliente */
		bzero( (char *)&client_addr, sizeof(client_addr) );
		client_addr.sin_family = AF_INET;
		client_addr.sin_addr = IPs[i];
		client_addr.sin_port = htons(puertos[i]);

		nums[0] = num;
		nums[1] = rangos[i];
		nums[2] = rangos[i + 1];
		/* regresa el número bytes enviados */
		int enviado = sendto(s, (char *)nums, 3 * sizeof(unsigned), 0, (struct sockaddr *)&client_addr, sizeof(client_addr) );
	}
	//printf("Se han envidado los rangos\n");

	/* Recibir los rangos */
	for (i = 0; i < COMP_NUM * 2; i++)
	{
		int size = sizeof(client_addr);
		recvfrom(s, (char *)&res[i], sizeof(short), 0, (struct sockaddr *)&client_addr, &size);
		printf("Recibido\n");
	}	

	int esPrimo = 1;
	for( i = 0; i < COMP_NUM && esPrimo; i++)
		esPrimo = esPrimo & res[i];

	printf("El numero %u %s primo\n", num, (esPrimo ? "es" : "no es"));
	free(IPs);
	free(rangos);
	return 0;
}

unsigned validar_entrada(int argc, char ** argv)
{
	register int i;
	int valid;

	if(argc < 3)
	{
		perror("Número de argumentos no válido");
		exit(EXIT_FAILURE);	
	}

	unsigned long aux = strtoul(argv[1], NULL, 10);

	if( aux > UINT_MAX)
	{
		perror("El numero no es válido");
		exit(EXIT_FAILURE);
	}

	COMP_NUM = (argc - 2)/2;
	printf("%d\n", COMP_NUM );

	IPs = (IP *)reservar_memoria(COMP_NUM * 2, sizeof(IP));
	//puertos = (int *)reservar_memoria(COMP_NUM, sizeof(int));


	for(i = 0; i < COMP_NUM; i+= 2)
	{
		valid = inet_aton(argv[i + 2], &(IPs[i]));
		puertos[i] = atoi(argv[i + 3]);
		if( !valid )	
		{
			printf("Direccion %d no válida\n", i);
			perror("Dirección IP número no válida");
      		exit(EXIT_FAILURE);
		}
	}
	printf("hola\n");

	return (unsigned int)aux;
}

void * reservar_memoria(int n, unsigned size)
{
	void * a = malloc(n * size);
	if(!a)
	{
		perror("Error en la asignación de memoria");
		exit(EXIT_FAILURE);
	}

	return a;
}

void asignar_rangos(unsigned num, int * rangos)
{
	unsigned skip = (num-2)/40 + 1;
	int i;
	printf("Skip: %u\n", skip );

	rangos[0] = 2;

	for(i = 1; i < COMP_NUM * 2; i++)
		rangos[i] = rangos[i - 1] + skip*peso[i];

	rangos[COMP_NUM] = num;

	for(i = 0; i < COMP_NUM; i++)
		printf("%u ", rangos[i]);
	printf("\n");
}

#include "SocketDatagrama.h"

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1000
#define PI 3.1416

int main(int args, char *argv[]){

	/* De consola sólo recibe el puerto donde va a estar
		montado el servidor	*/
	
	int PUERTO = atoi(argv[1]);

	/* Socket del servidor */
	SocketDatagrama sock(PUERTO);

	struct timeval tv;
	struct timezone tz;

	while(1){

		PaqueteDatagrama solicitud(10);
		sock.recibe(solicitud);
		char * IP = solicitud.obtieneDireccion();
		int p_cliente = solicitud.obtienePuerto();
		cout << "Solicitud recibida" << endl;

		gettimeofday(&tv, &tz);

		PaqueteDatagrama respuesta((char *)&tv, sizeof(tv), IP, p_cliente);

		sock.envia(respuesta);
		cout << "Tiempo enviado" << endl;
	}
	
	return 0;
}

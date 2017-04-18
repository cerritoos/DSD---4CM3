#include "Digito.h"
#include "SocketDatagrama.h"

#include "gfxModified.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

#define BUF_SIZE 1000
#define PI 3.1416

int main(int args, char *argv[]){
	int ysize = 400;
	int xsize = 900;
	char c;

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Reloj");

	//cout << "Soy el servidor" << endl;

	gfx_color(0,200,100);
	struct timeval now, t1, t2;
	struct tm* local;
	int decimasSegs, segundos, minutos, horas;
	
	gfx_flush();
	gfx_color(0,0,200);
		Digito hora1(8, 10, 100, 60, 10);
		Digito hora2(8, 110, 100, 60, 10);
		Digito minuto1(8, 250, 100, 60, 10);
		Digito minuto2(8, 350, 100, 60, 10);
		Digito segundo1(8, 490, 100, 60, 10);
		Digito segundo2(8, 590, 100, 60, 10);
		Digito decimaSegundo(8, 730, 100, 60, 10);

		gfx_fill_rectangle(210,120, 20, 20);
		gfx_fill_rectangle(210,210, 20, 20);

		gfx_fill_rectangle(450,120, 20, 20);
		gfx_fill_rectangle(450,210, 20, 20);

		gfx_fill_rectangle(690,220, 20, 20);
		
		hora1.dibujaDigito();
		hora2.dibujaDigito();
		minuto1.dibujaDigito();
		minuto2.dibujaDigito();
		segundo1.dibujaDigito();
		segundo2.dibujaDigito();
		decimaSegundo.dibujaDigito();
		gfx_flush();

	char *IP = argv[1]; /* IP del servidor */
	int PUERTO = atoi(argv[2]); /* Puerto del servidor */
	int  leidos = 0, destino;
	int PUERTOCli = atoi(argv[3]); /* Puerto del cliente (donde estará escuchando) */

	gettimeofday(&t1, NULL);
	SocketDatagrama sock(PUERTOCli);

	PaqueteDatagrama solicitud("hola", 5, IP, PUERTO);
	sock.envia(solicitud);
	cout << "Solicitud enviada" << endl;

	PaqueteDatagrama respuesta(sizeof(now));

	sock.recibe(respuesta);
	cout << "Tiempo recibido" << endl;
	gettimeofday(&t2, NULL);
	struct timeval * aux = (struct timeval *) respuesta.obtieneDatos();
	now = * aux;

	now.tv_sec += (t2.tv_sec - t1.tv_sec)/2;
	const struct timeval now_2 = now;
	settimeofday(&now_2, NULL);

	while(1){
		
		gettimeofday(&now, NULL);
		local = localtime(&now.tv_sec);

		decimasSegs = now.tv_usec /100000;
		decimaSegundo.setNumero(decimasSegs);
		decimaSegundo.dibujaDigito();
		gfx_flush();			

		horas = local->tm_hour;
		minutos = local->tm_min;
		segundos = local->tm_sec;

		segundo1.setNumero(segundos/10);
		segundo2.setNumero(segundos%10);
		segundo1.dibujaDigito(); segundo2.dibujaDigito();
		gfx_flush();

		minuto1.setNumero(minutos/10);
		minuto2.setNumero(minutos%10);
		minuto1.dibujaDigito(); minuto2.dibujaDigito();
		gfx_flush();	

		hora1.setNumero(horas/10);
		hora2.setNumero(horas%10);
		hora1.dibujaDigito(); hora2.dibujaDigito();

		gfx_flush();		
		
	}
	

	return 0;
}

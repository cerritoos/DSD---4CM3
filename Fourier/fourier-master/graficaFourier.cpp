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
using namespace std;

#define BUF_SIZE 1000
#define PI 3.1416

int main(int args, char *argv[]){
	int ysize = 600;
	int xsize = 800;
	char c;

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Grafica Fourier");

	//cout << "Soy el servidor" << endl;
	char *IP = argv[1];
	int PUERTO = atoi(argv[2]);
	int  leidos = 0, destino;
	int PUERTOCli = atoi(argv[3]);
	SocketDatagrama sock(PUERTO);
	int cooX=0, cooY=0;

	gfx_color(0,200,100);
	gfx_line(xsize/2,0,xsize/2,ysize);
	gfx_line(0,ysize/2,xsize,ysize/2);
	gfx_flush();

	while(1){
		PaqueteDatagrama resp(10);
		
		// Recibe los datos para graficar
		sock.recibe(resp);
		//cout << "Cadena " << resp.obtieneDatos() << endl;

		string cad = resp.obtieneDatos();

		/* El primer caracter indica si se debe dibujar o si se debe borrar */
		//cout << "Elemento " << cad[0] << endl;
		/* 0->dibujar, 1-> borrar */
		bool dibuja = (cad[0] == '1');
		//cout << "Booleano " << dibuja << endl;

		int ind = cad.find('?');
		int ind2 = cad.length();

		//cout << "Ind " << ind << endl;
		//cout << "Ind2 " << ind2 << endl;


		//guarda coordenada x
		cooX = atoi((cad.substr(1,ind)).c_str());
		//cout << "coordX: " << cooX << endl;
		
		//cout << "substr " << cad.substr(ind ,ind2-ind) << endl;
		
		cooY = atoi( cad.substr(ind + 1 ,ind2-ind).c_str() );
		//cout << "coordY: " << cooY << endl;
		//grafica el punto
		//blue
		(!dibuja ? gfx_color(0,0,200) : gfx_color(0,0,0) );
		gfx_point(cooX, cooY);
		gfx_flush();			
	}
	
	//if((c = gfx_wait()) == 'q')
	//	break;
	close(destino);
	return 0;
}

/* shorterfaz de la clase Reloj */

#ifndef RELOJ_H
#define RELOJ_H

#include "Hora.h"
#include "DisplaySegmentos.h"
#define W_SCREEN 900
#define L_SCREEN 200
#define SPACE_X 20
#define SPACE_Y 20

class Reloj
{
	private:
		Hora time;
		bool sincronizando;
		DisplaySegmentos numeros[10];
		void puntos(int, int);



	public:
		Reloj();
		Reloj(Hora);
		Reloj(short , short, short , short );
		void iniciarDisplaySegmentos(void);
		void dibujar();
		void setTime(Hora);
		void adelantar();
		Hora getTime();
		void iniciar();
		void flush();
		void limpiar();



};


#endif
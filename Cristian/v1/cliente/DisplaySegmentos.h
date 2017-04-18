#ifndef DISPLAYSEGMENTOS_H_
#define DISPLAYSEGMENTOS_H_


#include "Coordenada.h"
#define WIDTH 10
#define T_WIDTH 70
#define LENGTH 50

class DisplaySegmentos{
	private:
		bool seg_on[7];

	public:
		static Coordenada segmentos[7];
		DisplaySegmentos();
		DisplaySegmentos(bool []);
		static void iniciarCoord();
		Coordenada get(char);
		void dibujar(int, int);


};

#endif
#ifndef DIGITO_H_
#define DIGITO_H_
class Digito
{
	private:
		int numero;
		int superiorIzquierdaX;
		int superiorIzquierdaY;
		int anchoSegmento;
		int altoSegmento;
		bool segmentoA;
		bool segmentoB;
		bool segmentoC;
		bool segmentoD;
		bool segmentoE;
		bool segmentoF;
		bool segmentoG;

	public:
		Digito(int = 8, int = 0, int = 0, int = 10, int = 2);
		void dibujaDigito();
		//int getNumero();
		//void setSuperiorIzquierda(int, int);
		void setNumero(int);
};
#endif
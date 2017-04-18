/* Interfaz de la clase coordenada */
#ifndef COORDENADA_H_
#define COORDENADA_H_



class Coordenada
{
	private:
		int x;
		int y;
	public:
		Coordenada(int = 0, int = 0);
		int obtenerX();
		int obtenerY();
		void imprimirCoord();

};

#endif

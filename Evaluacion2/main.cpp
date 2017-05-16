#include "SocketDatagrama.h"
#include <inttypes.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define EVER 1
#define NOMBRE "Angeles Cerritos"

typedef struct messsageSC{
	char nombre[45];
	uint32_t num[10];
} message;

using namespace std;

int main(void)
{

	SocketDatagrama s(7300);
	uint32_t * arreglo;

	for(;EVER;)
	{
		PaqueteDatagrama solicitud(10 * sizeof(uint32_t));
		s.recibe(solicitud);

		arreglo = (uint32_t *) solicitud.obtieneDatos();
		
		

		/*cout << "Del arreglo" << endl;
		for(int i = 0; i < 10; i++)
			printf("%d\n", arreglo[i] );*/

		vector<uint32_t> v_arreglo(10);

		for(int i = 0; i < 10; i++)
			v_arreglo[i] = arreglo[i];

		/*cout << "Del vector" << endl;
		for(int i = 0; i < 10; i++)
			printf("%d\n", v_arreglo[i] );*/

		std::sort(v_arreglo.begin(), v_arreglo.end());

		cout << "Ordenados" << endl;
		for(int i = 0; i < 10; i++)
			printf("%d\n", v_arreglo[i] );

		message mensaje;
		//mensaje.nombre = NOMBRE;
		memcpy(mensaje.nombre, NOMBRE, sizeof(NOMBRE) + 1);
		memcpy(mensaje.num, &v_arreglo[0], 10 * sizeof(uint32_t));
		//mensaje.num = &v_arreglo[0];

		cout << "Cosas a enviar"<< endl;
		cout << "Nombre: " << mensaje.nombre << endl;
		cout << "Numeros: " << endl;
		for(int i = 0; i < 10; i++)
			printf("%d\n", mensaje.num[i] );

		PaqueteDatagrama respuesta((char *)&mensaje, (int)sizeof(mensaje), solicitud.obtieneDireccion(), solicitud.obtienePuerto());
		s.envia(respuesta);
		cout <<"Respuesta enviada" << endl;
	}



}
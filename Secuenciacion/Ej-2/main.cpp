#include "SocketDatagrama.h"
#include <iostream>
#include <stdlib.h>
#include <inttypes.h>

using namespace std;

int puerto = 7200;

typedef struct message{
   uint32_t secuencia;
   uint32_t solicitud[2];
   uint32_t respuesta;
}Mensaje;

void mostrarStats(void);


int s_diferentes = 0;
int s_totales = 0;
int s_respondidas = 0;


int main(int argc, char ** argv)
{
   SocketDatagrama s(0);
   s.setTimeout(0,500000);

   int n = atoi(argv[3]);

   

   /* Generar mensaje que se va a enviar */

   for(s_diferentes = 0; s_diferentes < n; s_diferentes++)
   {

      Mensaje solicitud;
      solicitud.secuencia = 0;
      solicitud.solicitud[0] = rand()%100 + 1;
      solicitud.solicitud[1] = rand()%100 + 1;

      
      int num_secuencia;
      for(num_secuencia = 0; num_secuencia < 7; num_secuencia++)
      {

         PaqueteDatagrama p( (char *)&solicitud, sizeof(solicitud), argv[1], atoi(argv[2]));
         cout << "Enviado a " << p.obtieneDireccion() << ":" << p.obtienePuerto() << endl;
         s.envia(p);
         s_totales++;

         /* Esperando respuesta */
         int respondido = s.recibeTimeout(p);
         if(respondido > 0)
         {
            Mensaje resultado = * ( (Mensaje *) p.obtieneDatos());
            cout << "Numeros enviados: " << solicitud.solicitud [0];
            cout << ", " << solicitud.solicitud[1]  << endl;



            cout << "Resultado: " << resultado.respuesta << endl;
            s_respondidas++;
            break;
         }

         solicitud.secuencia = num_secuencia;

      }

      if(num_secuencia == 7)
      {
         cout << "El servidor no está disponible" << endl;
         mostrarStats();
         return 0;
      }
   }

   mostrarStats();

   return 0;
}


void mostrarStats(void)
{
   cout << "Solicitudes distintas al servidor: " << s_diferentes << endl;
   cout << "Solicitudes totales hechas al servidor: " << s_totales << endl;
   cout << "Solicitudes respondidas: " << s_respondidas << endl;
   cout << (s_totales - s_respondidas)*100/s_totales << " \% datagramas perdidos"<< endl;
}

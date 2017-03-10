#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int puerto_server;
int puerto_cliente = 9999;
struct in_addr ip_server;

void validar_argumentos(int, char **);

int main( int argc, char * arcv[] )
{
   /* Validar los argumenros obtenidos*/
   validar_argumentos(argc, arcv);

   struct sockaddr_in msg_to_server_addr, client_addr;
   int s, num[2], res;
   
   s = socket(AF_INET, SOCK_DGRAM, 0);

   /* rellena la dirección del servidor */
   bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
   msg_to_server_addr.sin_family = AF_INET;
   //msg_to_server_addr.sin_addr.s_addr = inet_addr("192.168.43.16");
   msg_to_server_addr.sin_addr = ip_server;
   msg_to_server_addr.sin_port = htons(puerto_server);

   
   /* rellena la direcciòn del cliente*/
   bzero((char *)&client_addr, sizeof(client_addr));
   client_addr.sin_family = AF_INET;
   client_addr.sin_addr.s_addr = INADDR_ANY;
   
   /*cuando se utiliza por numero de puerto el 0, el sistema se encarga de asignarle uno */
   client_addr.sin_port = htons(9999);
   bind(s, (struct sockaddr *)&client_addr,sizeof(client_addr));
   num[0] = 2;
   num[1] = 5; /*rellena el mensaje */
   sendto(s, (char *)num, 2 * sizeof(int), 0, (struct sockaddr *) &msg_to_server_addr, sizeof(msg_to_server_addr));
   
   /* se bloquea esperando respuesta */
   int size2 = sizeof(client_addr);
   recvfrom(s, (char *)&res, sizeof(int), 0, (struct sockaddr *)&client_addr, &size2);
   //printf("%s\n", inet_ntoa(client_addr.sin_addr));
   //printf("%d\n", client_addr.sin_port);
   printf("2 + 5 = %d\n", res);
   close(s);
}

void validar_argumentos(int argc, char ** arcv)
{
   if(argc != 3)
   {
      perror("Número de argumentos no válido");
      exit(EXIT_FAILURE);
   }

   int valid = inet_aton(arcv[1], &ip_server);
   if(!valid)
   {
      perror("Dirección IP no válida");
      exit(EXIT_FAILURE);
   }

   printf("%s\n", inet_ntoa(ip_server));

   puerto_server = atoi(arcv[2]); 
   printf("Puerto server : %d\n", puerto_server);
   if(puerto_server < 1024 || puerto_server > 65536)  
   {
      perror("Puerto no valido");
      exit(EXIT_FAILURE);
   }

}

#ifndef HEADER_H
#define HEADER_H

#include <inttypes.h>

/* Definiiciones necesariass para los clientes y el servidor de archivos*/
#define MAX_PATH 255 //Longitud maxima en el nombre de un archivo
#define BUF_SIZE 1000 // Cantidad de bytes que se transfieren por paquete


/* Operaciones permitidas */
#define CREATE 	1
#define READ 	2
#define WRITE 	3
#define DELETE	4

/* Codigos de error */
#define OK 				 0
#define E_BAD_OPCODE 	-1
#define E_BAD_PARAM 	-2
#define E_IO			-3


/* Mensaje que viaja del cliente hasta el servidor */
typedef struct messageCS{
	uint32_t opcode; 
	uint32_t count;
	uint32_t offset;
	char name[MAX_PATH];
}Peticion;

typedef struct messageSC{
	uint32_t count;
	uint32_t result;
	char data[BUF_SIZE];
}Respuesta;





#endif
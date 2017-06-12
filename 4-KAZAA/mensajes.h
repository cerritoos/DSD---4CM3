#ifndef MENSAJES_H_
#define MENSAJES_H_

#define MAX_FILENAME 100
#define BUFSIZE 	 1000


#define UNION 			0
#define NUEVO 			1
#define ELIMINACION 	2
#define RETRANS_SOL 	3
#define UNION_ACK 		4
#define ELIMIN_ACK		5
#define RETRANSMISION 	6
#define SOLICITUD_ARCH  7
#define ENVIO_ARCH		8


#include <inttypes.h>

typedef struct mensaje{
	uint32_t opcode;
	char filename[MAX_FILENAME];
	uint32_t count;
	uint32_t offset;
	char data[BUFSIZE];
}Mensaje;

#endif
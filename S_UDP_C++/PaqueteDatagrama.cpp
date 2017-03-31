#include "PaqueteDatagrama.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char * msg, unsigned int len_msg, char * IP, int pto)
{	
	longitud = len_msg;
	copy(IP, IP + 16, ip);
	puerto = pto;
	datos = reservar_memoria();
	memcpy( datos, msg, len_msg + 1);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int len_msg):longitud(len_msg)
{
	longitud = len_msg;
	datos = reservar_memoria();
}

char * PaqueteDatagrama::reservar_memoria()
{
	char * mem = new char(longitud + 1);
	if( !mem )
	{
		perror("Error en la asignación de memoria\n");
		exit(EXIT_FAILURE);
	}

	return mem;
}

char * PaqueteDatagrama::obtieneDireccion()
{	return ip;	}

unsigned PaqueteDatagrama::obtieneLongitud()
{	return longitud;	}

int PaqueteDatagrama::obtienePuerto()
{	return puerto;	}	

char * PaqueteDatagrama::obtieneDatos()
{	return datos;	}

void PaqueteDatagrama::inicializaPuerto(int p)
{	puerto = p;	}

void PaqueteDatagrama::inicializaIP( char * IP )
{	copy(IP, IP + 16, ip);	}

void PaqueteDatagrama::inicializaDatos(char * d)
{	
	datos = reservar_memoria();
	memcpy( datos, d, longitud + 1);
}
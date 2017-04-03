#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama(char *msj, unsigned int lon, char *IP, int p) {
	longitud = lon;
	puerto = p;
	datos = new char[lon];
	memcpy(datos, msj, lon);
	strcpy(ip, IP);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int lon){
	longitud = lon;
	datos = new char[lon]();
}

PaqueteDatagrama::~PaqueteDatagrama(){
	delete datos;
	longitud = 0;
	puerto = 0;
}

char *PaqueteDatagrama::obtieneDireccion(){
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
	return longitud;
}

int PaqueteDatagrama::obtienePuerto(){
	return puerto;
}

char * PaqueteDatagrama::obtieneDatos(){
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int p){
	puerto = p;
}

void PaqueteDatagrama::inicializaIp(char *IP){
	strcpy(ip, IP);
}

void PaqueteDatagrama::inicializaDatos(char *d){
	memcpy(datos, d, longitud);	
}

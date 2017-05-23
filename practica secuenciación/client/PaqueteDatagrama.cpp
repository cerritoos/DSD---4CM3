#include "PaqueteDatagrama.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

PaqueteDatagrama:: PaqueteDatagrama(char *msj, unsigned int cad_size, char *address, int pto){
	longitud=cad_size;
	datos = new char[cad_size+1];
	memcpy(datos, msj, cad_size);
	strcpy(ip, address);
	puerto=pto;
	//cout<<ip;
}

PaqueteDatagrama:: PaqueteDatagrama(unsigned int cad_size){
	longitud=cad_size;
	datos = new char[cad_size+1];
}

PaqueteDatagrama:: ~PaqueteDatagrama(){
	delete[] datos;
}

char* PaqueteDatagrama:: obtieneDireccion(){
	return ip;
}

char* PaqueteDatagrama:: obtieneDatos(){
	return datos;
}

unsigned int PaqueteDatagrama:: obtieneLongitud(){
	return longitud;
}

int PaqueteDatagrama:: obtienePuerto(){
	return puerto;
}

void PaqueteDatagrama:: inicializaPuerto(int pto){
	puerto=pto;
}

void PaqueteDatagrama:: inicializaIp(char *address){
	strcpy(ip, address);
}

void PaqueteDatagrama:: inicializaDatos(char *data){
	memcpy(datos, data, longitud);
}



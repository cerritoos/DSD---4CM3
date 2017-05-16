#include "PaqueteDatagrama.h"
using namespace std;
PaqueteDatagrama::PaqueteDatagrama(char * cadena, unsigned int tamanio, char * direccion, int puertor):longitud(tamanio),puerto(puertor){
    datos=new char[tamanio];
    memcpy(datos,cadena,tamanio);
    strcpy(ip,direccion);
}
PaqueteDatagrama::PaqueteDatagrama(unsigned int tamanio):longitud(tamanio){
  datos=new char[tamanio];
}

PaqueteDatagrama::~PaqueteDatagrama(){
  delete [] datos;
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
char *PaqueteDatagrama::obtieneDatos(){
return datos;
}
void PaqueteDatagrama::inicializaPuerto(int puertor){
  puerto=puertor;
}
void PaqueteDatagrama::inicializaIp(char *ipRecibida){
  strcpy(ip,ipRecibida);
}
void PaqueteDatagrama::inicializaDatos(char *datosEnviados){
  memcpy(datos,datosEnviados,longitud);
}

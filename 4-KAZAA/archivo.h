#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <map>

using namespace std;






/* Funciones de interacción de archivos */
/* Crear archivo */
void crear_archivo(string filename);

/* Guardar archivo */
int guardar_archivo(Mensaje m, string ip);

/* Solicitar archivo */
void solicitar_archivo(string filename, string ip, int offset);

/* Solicitar retransmision de un archivo en caso de error en el guardado */
int solicitar_retransmision(Mensaje m);

/* Eliminar un archivo */
int eliminar_archivo(string filename);

/* Enviar enterado a un nodo que se unio */
void enviar_unionAck(string ip);

/* Retransmitir archivo */
void enviar_archivo(Mensaje m, string ip);

/* Enviar archivo */
void notificar_archivo(string filename);

/* Notificar la eliminacion de un archivo */
void notificar_eliminacion(string name);

/* Borrar un archivo de la carpeta trash */
void eliminar_trash(string filename);

#endif
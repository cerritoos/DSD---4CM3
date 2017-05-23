/* Servidor de archivos para probar código de los alumnos en lenguaje C++ 
 $ ./file_server_objetos1 7000
*/
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "header.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



using namespace std;

int main(int argc, char *argv[]){

   struct messageSC mensEnv;
   struct messageCS mensRcb;
   int pid, estado, fileDescriptor;
   
      
   if(argc != 2){
      cout << "Forma de uso: " << argv[0] <<  " puerto\n";
      exit(0);
   }
   bzero((char *)&mensEnv, sizeof(messageSC));
   bzero((char *)&mensRcb, sizeof(messageCS));
   
   PaqueteDatagrama envio((char *)(&mensEnv), sizeof(messageSC), "", 0);
   //PaqueteDatagrama recepcion(sizeof(struct messageCS));
   SocketDatagrama socketlocal(atoi(argv[1]));
   PaqueteDatagrama recepcion(sizeof(messageCS));
   //Crea Demonio
   cout << "Este es un Demonio servidor de archivos \n";
   while(1){   
      pid = fork();
      switch(pid){
         case -1:
            perror("Error en el fork");
            socketlocal.~SocketDatagrama();         
            exit(-1);
            break;
         case 0: //Hijo      
            cout << "Crea un proceso hijo para atender a clientes\n";
            
            while(1){                   
               //recvfrom(s, (char *) &mensaje, sizeof(struct message), 0, (struct sockaddr *)&msg_to_client_addr, &clilen);
               cout << "Esperando solicitud ...\n";      
               socketlocal.recibe(recepcion);         
               cout << "\nLa IP de quien me envió es: " << recepcion.obtieneDireccion() << endl;
               cout << "El puerto de quien me envió es: " << recepcion.obtienePuerto() << endl;      
               //recepcion.~PaqueteDatagrama();
               memcpy((char *)&mensRcb, recepcion.obtieneDatos(), sizeof(mensRcb));
               cout << "Opción recibida: = " << mensRcb.opcode << endl;               
               cout << "count: = " << mensRcb.count << endl;       
               cout << "offset: = " << mensRcb.offset << endl;
               cout << "nombre: " << mensRcb.name << endl; 
               cout << "Mi estructura messageCS " << sizeof(struct messageCS);// << " mensEnv= " sizeof(struct messageCS) << " Bytes" << endl;
               if(mensRcb.opcode == READ){                  
                     //printf("Solicitud para leer del archivo: %s desde un offset = %ld\n", mensaje.name, mensaje.offset);                  
                  fileDescriptor = open(mensRcb.name, O_RDONLY);                     
                  if(fileDescriptor == -1)
                     mensEnv.result = E_IO; 
                  else{
                     lseek(fileDescriptor, mensRcb.offset, SEEK_SET);
                     mensEnv.count = read(fileDescriptor, mensEnv.data, BUF_SIZE);
                     mensEnv.result = OK;                        
                     close(fileDescriptor);                                             
                  }
                  envio.inicializaDatos((char *) &mensEnv);
                  envio.inicializaIp(recepcion.obtieneDireccion());
                  envio.inicializaPuerto(recepcion.obtienePuerto()); 
                  socketlocal.envia(envio);                 
               }
            }
            exit(0);
            break;
         default: //padre
            wait(&estado);
            cout << "Soy el padre y acaba de morir un proceso hijo. Se crea otro...\n";
            
      }
   }  
}

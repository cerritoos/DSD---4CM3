#include "SocketDatagrama.h"
#include <iostream>
#include <thread>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <memory.h>

using namespace std;

void funcion(int i)
{
	char* ip=(char*)"127.0.0.";
	char* id;
	
	SocketDatagrama socket(7200);
	//socket.setTimeout(0,500000);

	//cout << "HOLA1.5" << endl;
	char* mensaje = (char*)"hallo wie gehts?";
	sprintf(id,"%d",i);

	cout << "ID :" << id << endl;

	/*char * ipf = (char *) malloc(1 + strlen(ip)+ strlen(id) );
    strcpy(ipf,ip);
    strcat(ipf,id);
    cout<<ipf<<"a"<<endl;
    cout<<ipf<<endl;
    

    PaqueteDatagrama paquete1(mensaje,sizeof(mensaje),ipf,7200);
    cout<<paquete1.obtieneDireccion()<<"a"<<endl;
    socket.envia(paquete1);*/
}

int main(int argc, char const *argv[])
{
	cout<<"hola"<<endl;
	std::vector<thread> hilos;
	
	for (int i=0; i <30;i++)
		hilos.push_back(thread(funcion,i));
	
	cout<< "hola2" << endl;
	for(auto& t: hilos)
        t.join();

	
	//cout<<"hola";

	return 0;
}
 //g++ hilos.cpp -o hilos -std=c++11 -pthread
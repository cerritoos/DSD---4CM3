#include "Reloj.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
using namespace std;

void actualizarReloj(int);
void proceso_padre(void);
void proceso_hijo(void);
Reloj r;

int main(void)
{
	r = Reloj(Hora());
	r.iniciarDisplaySegmentos();
	/*cout << r.getTime().getHr() << endl;
	cout << r.getTime().getMin() << endl;
	cout << r.getTime().getSeg() << endl;
	cout << r.getTime().getDec() << endl;*/

	//string hora = r.getTime().toString();
	//cout <<  hora << endl;
	r.iniciar();

	/* Un proceso hijo es el que se encargará de la actualización del reloj */
	pid_t pid;
	pid = fork();

	if( !pid ) 
		proceso_padre();
	else	
		proceso_hijo();

	
    
	return 0;
}

void actualizarReloj(int sig)
{
	//cout << "Actualizando..." << endl;
	r.limpiar();
	r.setTime(Hora());
	r.dibujar();
	r.flush();
	//cout << r.getTime().toString() << endl;
}

void proceso_padre()
{
	wait();
}

void proceso_hijo()
{
	if( signal(SIGALRM, actualizarReloj) == SIG_ERR )
    {
            perror("Error en la señal \n");
            exit(EXIT_FAILURE);
    }

	/*Pone la alarma*/
	struct timeval intervalo;
	intervalo.tv_sec = 0;
	intervalo.tv_usec = 10000;

	struct timeval valor;
	valor.tv_sec = 0;
	valor.tv_usec = 10000;

	struct itimerval timer;
	timer.it_interval = intervalo;
	timer.it_value = valor;
	setitimer(ITIMER_REAL, &timer, NULL);

	while(1)
		pause();
}
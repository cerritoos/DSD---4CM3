/*
	Programa que recibe un número, un rango de números 
	y determina si el primer número es divisible por alguno de 
	los números en el rango.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct in_addr IP;


int main(void)
{


	return;
}


short isPrime(unsigned num)
{
	unsigned i;
	short isPrime = 1;
	for(i = 2; i < num; i++)
	{
		if( !(num%i) )
			isPrime = 0;
	}
	return isPrime;
}
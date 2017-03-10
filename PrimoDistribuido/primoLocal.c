#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


unsigned validar_entrada( int, char *);


int main(int argc, char * argv[])
{
	unsigned num = validar_entrada(argc, argv[1]);
	register unsigned i;
	short isPrime = 1;
	for(i = 2; i < num; i++)
	{
		if( !(num%i) )
			isPrime = 0;
	}
	printf("Eĺ número %u %s primo\n", num, (isPrime ? "es" : "no es"));
	return 0;
}

unsigned validar_entrada(int argc, char * numero)
{
	if(argc < 2)
	{
		perror("Número de argumentos no válido");
		exit(EXIT_FAILURE);	
	}
	unsigned long aux = strtoul(numero, NULL, 10);
	if( aux > UINT_MAX)
	{
		perror("El numero no es válido");
		exit(EXIT_FAILURE);
	}
	return (unsigned int)aux;

}
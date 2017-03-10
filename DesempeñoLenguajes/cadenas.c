#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ESP ' '
#define TOKENS 70304
#define NEEDLE "IPN"
#define TOKEN_LEN 4


void generar_cadena();
int buscar_cadena();

char * cadena;

int main()
{
	int times_found = 0;
	generar_cadena();
	srand(time(NULL));
	//printf("%s\n", cadena);
	printf("%d\n", buscar_cadena());
	free(cadena);
	return 0;
} 


void generar_cadena()
{
	long pos = 1;
	char token[4];
	
	int register i = 0;

	for(i = 0; i < TOKENS; i++)
	{
		token[0] = rand()%26 + 'A';
		token[1] = rand()%26 + 'A';
		token[2] = rand()%26 + 'A';
		token[3] = ESP;

		pos += TOKEN_LEN;
		cadena = (char *)realloc(cadena, pos);
		cadena = memcpy(cadena, token, 4);
	}
}


int buscar_cadena()
{
	char * found = " ";
	int found_times = 0;
	char * cad_aux = cadena;

	while(found)
	{
		found = strstr(cad_aux, NEEDLE);
		if(found)
		{
			cad_aux = found + TOKEN_LEN;
			found_times++;
		}
	}
	/*do{
		found = strstr(cad_aux, NEEDLE);
		printf("Buscando\n");
		if(!found) break;
		
		cad_aux = found + TOKEN_LEN;
		found_times++;

	}while(!found);*/

	return found_times;
}
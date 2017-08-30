/*
 * tp0.c
 *
 * Tema: Replicaci�n del comportamiento del comando 'echo'
 */

/*
 * PAR�METROS:
 * -----------
 *
 * -i: invierte el orden de los caracteres de salida.
 * -l: pasa el texto ingresado a min�scula
 * -n: no agrega una nueva l�nea al final
 * -o <ruta_archivo>: la salida va al archivo indicado y no por pantalla
 * -u: pasa el texto ingresado a may�scula
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>

/*
 * Invierte el orden de los caracteres de una cadena pasada por par�metro
 */
void invierte(char *cadena) {
	char cadena_tmp[255]="";
	strcpy(cadena_tmp,cadena);
	int j = strlen(cadena) - 1;
	for (int i = 0; i < strlen(cadena_tmp); i++) {
		strncpy(&cadena[i], &cadena_tmp[j], 1);
		j--;
	}
	return;
}

/*
 * Convierte una cadena pasada por par�metro a min�scula
 */
void minuscula(char *cadena) {
	for (int i = 0; i < strlen(cadena); i++) {
		cadena[i] = tolower((unsigned char) cadena[i]);
	}
	return;
}

/*
 * Convierte una cadena pasada por par�metro a may�scula
 */
void mayuscula(char *cadena) {
	for (int i = 0; i < strlen(cadena); i++) {
		cadena[i] = toupper((unsigned char) cadena[i]);
	}
	return;
}

/*
 * Imprime una cadena pasada por par�metro.
 * por_pantalla: 	0 -> imprime por pantalla
 * 					1 -> redirige salida a archivo (determinado por variable "ruta")
 * nueva_linea: 	0 -> agrega caracter de nueva l�nea
 * 					1 -> NO agrega caracter de nueva l�nea
 */
void imprimir(char *cadena, int nueva_linea, int por_pantalla, char *ruta) {
	if (por_pantalla == 1) {
		FILE *archivo;
		archivo = fopen(ruta, "w");
		if (archivo == NULL) {
			printf("La opcion '-o' requiere que se especifique una ruta a la que se pueda acceder para escritura.\n");
		} else {
			fputs(cadena, archivo);
			if (nueva_linea == 0) fputs("\n", archivo);
			fclose(archivo);
		}
	}
	else {
		printf("%s", cadena);
		if (nueva_linea == 0) printf("\n");
	}
	return;
}

/*
 * Funci�n principal
 */
int main (int argc, char *argv[]) {
	int nueva_linea = 0;
	int por_pantalla = 0;
	char ruta[255]="";
	if (argc == 1)
		printf("Debe ingresar texto a imprimir.\n");
	else if (argc == 2) {
		printf("%s\n", argv[1]);
	}
	else {
		for (int i = 1; i < argc-1; i++) {
			if (strcmp(argv[i], "-i") == 0)
				invierte(argv[argc-1]);
			else if (strcmp(argv[i], "-l") == 0)
				minuscula(argv[argc-1]);
			else if (strcmp(argv[i], "-n") == 0)
				nueva_linea = 1;
			else if (strcmp(argv[i], "-o") == 0) {
				por_pantalla = 1;
				strcpy(ruta, argv[i+1]);
				i++;
			}
			else if (strcmp(argv[i], "-u") == 0)
				mayuscula(argv[argc-1]);
			else {
				printf("El argumento ingresado no es correcto.\n");
				return (0);
			}
		}
		imprimir(argv[argc-1], nueva_linea, por_pantalla, ruta);
	}
	return (0);
	}

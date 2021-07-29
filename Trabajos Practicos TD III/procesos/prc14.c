/*
 * Ejercicio 14
*/
#include <stdio.h>
#include <stdlib.h>

int main (){
	
	fprintf (stdout, "Texto stdout\n");
	fprintf(stderr, "Texto stderr\n");
	exit(0);   
	}

//Respuesta:
//Por consola se observa unicamente el string dirigido a stdout.
//El contenido del archivo err.txt es el string dirigido a stderr.
// La funcion del operador "2>" es redirigir unicamente lo que se dirigia
// a stderr, mientras que lo que se dirigia a stdout sigue mostrandose por
// pantalla.
//Se ve entonces que ambos flujos pueden ser tratados por separado.

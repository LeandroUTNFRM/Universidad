/*
 * Ejercicio 5 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main ()
{
	int x = 100;
	
	printf("Soy el proceso: %d \n ",getpid());
	
	switch (fork())
	{
		case -1:   // No pudo crear el proceso
			printf ("Error. No se crea proceso hijo");
			break;

		case 0:   //proceso hijo
			printf ("Soy el proceso hijo, pid: %d , x = %d\n", getpid(), --x);
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d , x = %d\n", getpid(), ++x);
	}
    exit(0);

}

//Respuesta:

//La variable "x" no retorna a su valor original porque tanto el proceso padre como el hijo
//modifican el valor de la variable en su espacio de memoria.
//El proceso hijo resta 1 a 100.
//El proceso padre suma 1 a 100.

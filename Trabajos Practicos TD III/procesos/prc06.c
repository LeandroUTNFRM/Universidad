/*
 * Ejercicio 6 de TP Procesos
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
			printf ("Soy el proceso hijo, pid: %d , x = %d\n, posicion en memoria (&x): %ld", getpid(), --x, (&x));
			break;

		default:  //proceso padre
			printf ("Soy el proceso padre, pid: %d , x = %d\n, posicion en memoria (&x): %ld", getpid(), ++x, (&x));
	}
    exit(0);

}

//Respuesta:

//A pesar de que la variable "x" esta en diferentes espacios de memoria para cada proceso,
//la posicion en memoria de la variable es la misma para ambos ya que es una direccion
//relativa dentro de cada espacio de memoria.

/*
 * Ejercicio 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){
	
	printf ("Mi pid es %d y el pid de papa es %d\n", getpid(),getppid());

	exit(0);   
	}

//Respuesta:

//El PID (identificador de proceso) es un numero entero
//utilizado por el kernel para identificar un proceso.

//El PID del proceso hijo siempre es mayor que el del proceso padre.

//Esto es porque los pid se van asignando a medida que se van ejecutando
//los procesos.

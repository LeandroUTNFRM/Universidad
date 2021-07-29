/*
 * Ejercicio 7 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	for(i=0;i<3;i++){
		pid = fork();		
		printf ("Repeticion %d (i=%d). Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n",i+1,i, getpid(), getppid(), pid);
	}

	// Ejecute pstree en otra consola	
	sleep(30); 

	exit(0);

}

//Respuesta:

//En la primera repeticion, se crea 1 hijo. Dando como resultado 2 procesos.
//En la segunda repeticion, se crean 2 hijos, 1 por cada proceso. Dando como resultado 4 procesos.
//En la tercera repeticion, se crean 8 hijos, 1 por cada proceso. Dando como resultado 8 procesos
//Al final del bucle se tienen 8 procesos.
//Por cada pasada de bucle se duplican los procesos presentes.

//El valor de i aumenta del valor inicial al final indicado para repetir el bucle 3 veces.


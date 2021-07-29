/*
 * Ejercicio 8 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();		
	//printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

	//proceso hijo
	if(pid == 0){
		printf("Soy el proceso hijo. Mi PID es %d.", getpid());
		sleep(30);
		exit(0);

	}

	else{
		printf("Soy el proceso padre. Mi PID es %d.", getpid());
	}
	// Ejecute pstree en otra consola	
	//sleep(30); 

	exit(0);

}

//Respuesta:

//El padre termina antes que el hijo, por lo que el hijo queda huerfano y toma como padre
//a otro proceso.

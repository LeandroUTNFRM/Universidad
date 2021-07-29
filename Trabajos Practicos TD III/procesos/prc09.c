/*
 * Ejercicio 9 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <sys/wait.h>
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i, w;

	pid = fork();		
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

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
	w = wait(NULL);
	printf("Mi PID: %d, wait devuelve %d", getpid(),w);

	exit(0);

}

//Respuesta:

//El padre espera a que el hijo termine y wait devuelve el PID del hijo que terminó.


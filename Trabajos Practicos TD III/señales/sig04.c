/*
 * Ejercicio 7 de TP Señales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main ()
{

 pid_t pid1, pid2, pid3;

 pid1 = fork();

 if(pid1 == 0){
	printf("Hijo 1. PID: %d\n", getpid());
 }

 else{
	pid2 = fork();

	if(pid2 == 0){
		printf("Hijo 2. PID: %d\n", getpid());
	}

	else{
		pid3 = fork();

		if(pid3 == 0){
			printf("Hijo 3. PID: %d\n", getpid());
		}

		else{
			sleep(2);
			printf("Terminando proceso hijo 1\n");
			kill(pid1, SIGKILL);
			sleep(2);
			printf("Terminando proceso hijo 2\n");
			kill(pid2, SIGKILL);
			sleep(2);
			printf("Terminando proceso hijo 3\n");
			kill(pid3, SIGKILL);
			sleep(2);

		}
	}
 }
}

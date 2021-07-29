/*
 * Ejercicio 8 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void manejador_sig(int a){

	int devolucion_wait, status;

	devolucion_wait = wait(&status);

	printf("La funcion wait devuelve: %d y el valor de status es: %d", devolucion_wait, status);

}

int main ()
{

   pid_t pid1;

   signal(SIGCHLD, manejador_sig);

   pid1 = fork();

   if(pid1 == 0){

	printf("Proceso hijo. PID: %d\n", getpid());
	sleep(2);
	printf("Terminando proceso hijo\n");
	exit(0);

   }

   else{

	printf("Proceso padre. PID: %d\n", getpid());

	sleep(10);

   }
}

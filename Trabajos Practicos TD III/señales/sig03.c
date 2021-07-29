/*
 * Ejercicio 5 y 6 de TP Seniales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void manejador_sig(int a){

	write(STDOUT_FILENO, "\nMe rehuso a terminar\n", sizeof("\nMe rehuso a terminar\n"));

}

int main ()
{

   //signal(SIGKILL, manejador_sig);
   signal(SIGUSR1, manejador_sig);
 
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}

//Respuestas:
//5. Cuando se envia la señal SIGKILL, por mas que se esté intentando ignorar
//   la señal, el proceso termina porque no puede ser ignorada.

//6. Cuando se envia la señal SIGUSR1, se recibe la señal y se ejecuta el codigo
//   del manejador de señales, mostrando el mensaje "me rehuso a terminar" y 
//   cambiando la accion por defecto de SIGUSR1 de terminar el proceso. 

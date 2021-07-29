/*
 * Ejercicio 16 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main(void) {
	
	int err;
	
	//err = execl	("/bin/ls", "ls", "-l", (char *)NULL);
	err = execl("/otro_directorio/ls", "ls", "-l", (char *)NULL);
	
	if (err == -1)
		printf("Este printf se ejecuta en caso de error. Por que?\n");
			
	exit(0);

}
	
//Respuesta:
//Se produce un error debido a que bien, no existe el directorio "otro_directorio"
//o si existe, el comando ls no se encuentra incluido en el

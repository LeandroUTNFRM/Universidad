/*
 * Ejercicio 1 y 2 de TP Señales
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main ()
{

   sleep(5);
   
   exit(5);
}

//Respuesta:
//El valor varia. Cuando termina de forma normal, el estado de la salida es 5
//Cuando termina en forma abrupta con ctrl+c el estado es 130.

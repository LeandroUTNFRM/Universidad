/*
 * Ejercicio 4a del TP FIFO  Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO B"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   err = mkfifo(FIFO_PATH, 0777);
   if(err == -1) {
      write (STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   }else {
      write (STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   }
   
   fifo_d = open(FIFO_PATH, O_WRONLY, 0); // O_NONBLOCK
         if(fifo_d == -1){
            write (STDOUT_FILENO, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
            return -1;
         }else {
            write (STDOUT_FILENO, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
         }

   // Se escribe en el FIFO
 err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
 if(err == -1) {
 	write(STDOUT_FILENO, "\nError al escribir en FIFO", sizeof("\nError al escribir en FIFO"));
 } else {
 	write(STDOUT_FILENO, "\nEscritos MENSAJE en FIFO", sizeof("\nEscritos MENSAJE en FIFO"));
 }
         
   close(fifo_d);
   
   unlink(FIFO_PATH);
   
   exit(0);

}

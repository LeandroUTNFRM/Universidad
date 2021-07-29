/*
 * Ejercicio 4b del TP FIFO  Tipica implementacion de una FIFO.
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


         fifo_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK
         if(fifo_d == -1){
            write (STDOUT_FILENO, "\nError al abrir FIFO ", sizeof("\nError al abrir FIFO "));
            return -1;
         }else {
            write (STDOUT_FILENO, "\nFIFO abierto correctamente", sizeof("\nFIFO abierto correctamente"));
         }

         // Se lee FIFO
         leido = read(fifo_d, buff, sizeof(buff));
         if(leido == -1){
            write(STDOUT_FILENO, "\nError al leer en FIFO", sizeof("\nError al leer en FIFO"));
         }else {
            write(STDOUT_FILENO, "\nLeido del FIFO: ", sizeof("\nLeido del FIFO: "));
            write(STDOUT_FILENO, buff, leido-1);
            write(STDOUT_FILENO, "\n", sizeof("\n"));
         }
         close(fifo_d);

         unlink(FIFO_PATH);
        
         exit(0);


}

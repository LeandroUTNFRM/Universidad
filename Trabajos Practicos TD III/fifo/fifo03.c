/*
 * Ejercicio 3 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   if(err == -1) {
      write(STDOUT_FILENO, "\nError al crear FIFO, la FIFO ya existe", sizeof("\nError al crear FIFO, la FIFO ya existe"));
   }else {
      write(STDOUT_FILENO, "\nFIFO creado correctamente\n", sizeof("\nFIFO creado correctamente\n"));
   }


   switch (fork()){ //crea proceso hijo
      
      case -1://error
         write(STDOUT_FILENO, "\nError al crear hijo", sizeof("\nError al crear hijo"));
         return -1;
      break;

      case 0://proceso hijo

         write(STDOUT_FILENO, "\nEntrando proceso HIJO", sizeof("\nEntrando proceso HIJO"));

         sleep(5);

         /*  
         //El Hijo que debe hacer con la FIFO ?
         */      

	 fifo_d = open(FIFO_PATH, O_RDONLY, 0);//abre fifo con permisos de lectura

	 write(STDOUT_FILENO,"\nMensaje leido: ", sizeof("\nMensaje leido: "));
	 write(STDOUT_FILENO, MENSAJE, sizeof(MENSAJE));//muestra en pantalla el mensaje leido de la fifo

         write(STDOUT_FILENO, "\nSaliendo proceso HIJO\n", sizeof("\nSaliendo proceso HIJO\n"));
         exit(0);
      break;

      default://proceso padre
         write(STDOUT_FILENO, "\nEntrando proceso PADRE", sizeof("\nEntrando proceso PADRE"));

         fifo_d = open(FIFO_PATH, O_WRONLY, 0);//abre fifo con permisos de escritura
         if(fifo_d == -1){
            write(STDOUT_FILENO, "\nPADRE: Error al abrir FIFO ", sizeof("\nPADRE: Error al abrir FIFO "));
            return -1;
         }else {
            write(STDOUT_FILENO, "\nPADRE: FIFO abierto correctamente", sizeof("\nPADRE: FIFO abierto correctamente"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE));//escribe en la fifo el mensaje
         if(err == -1) {
            write(STDOUT_FILENO, "\nPADRE: Error al escribir en FIFO", sizeof("\nPADRE: Error al escribir en FIFO"));
         } else {
            write(STDOUT_FILENO, "\nPADRE: Escritos MENSAJE en FIFO", sizeof("\nPADRE: Escritos MENSAJE en FIFO"));
         }

         close(fifo_d);//cierra fifo

         wait(NULL);
         write(STDOUT_FILENO, "\nSaliendo proceso PADRE\n", sizeof("\nSaliendo proceso PADRE\n"));

      break;   
   }
   
   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}

//Respuesta:
//El problema era que el hijo no abria la fifo con permisos de lectura, por lo que nadie leia
//lo que el padre escribia.

/*
 * Ejercicio 2 de TP PIPE
 * 
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   if (pipe(ipc) == -1)//crea la tuberia con sus descriptores en ipc, da error si el valor es -1
      exit(-1);

   switch (fork()){ //se crea un proceso hijo
      
      case 0://proceso hijo
         close(ipc[0]);//Modificación: se cerraba el descriptor de entrada ipc[1]. Se cambia codigo para cerrar el de salida, ya que no será usado por el hijo.
         strncpy(buff, DATA, sizeof(DATA)); //se copian los datos a un buffer
         write(ipc[1], buff, sizeof(DATA));//se intentaba escribir en el descriptor de entrada ya cerrado anteriormente.
         exit(0);
         
      default://proceso padre
	 close(ipc[1]);//Modificación: se agregó esta linea. Se cierra el descriptor de entrada, que no será usado por el padre.
         printf("Leyendo tuberia... \n");
         leido = read(ipc[0], buff, sizeof(buff));//se lee la tuberia y se guardan los datos en el buffer
         if(leido < 1){//error si no se puede leer
            write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
         }else {

            write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write (STDOUT_FILENO, buff, leido-1);//muestra lo leido de la tuberia
            printf(", por el proceso padre, pid %d \n", getpid());
         }
         wait(NULL);

         exit(0);
   }
}

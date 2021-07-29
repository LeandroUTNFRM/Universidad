/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define FRASE_A "INFORMACION IMPORTANTE"
#define FRASE_B "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){//manejador de señal
   
   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
}

int main (){

   int ipc1[2], ipc2[2], proc;
   int leido, success;
   char buff1[BUFF_SIZE] = {0}, buff2[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);//se asigna el manejador a la señal SIGPIPE
   
   pipe(ipc1);//se crea una tuberia con sus descriptores en ipc1[]
   pipe(ipc2);//se crea una tuberia con sus descriptores en ipc2[]
   switch (fork()){ //se crea un proceso hijo
      
      case 0://proceso hijo 1
      close(ipc1[0]);//Cierra descriptor de salida
      strncpy(buff1, FRASE_A, sizeof(FRASE_A)); //copia a buffer la frase A
      write(ipc1[1], buff1, sizeof(FRASE_A));//escribe en la tuberia 1 el contenido del buffer1
      exit(0);
      break;
      
      default://proceso padre
      switch (fork()){ //crea otro proceso hijo
            
         case 0://proceso hijo 2
            close(ipc2[0]);//cierra descriptor de salida
            strncpy(buff2, FRASE_B, sizeof(FRASE_B));//copia a buffer la frase B
            write(ipc2[1], buff2,    sizeof(FRASE_B));//escribe en la tuberia 2 el contenido del buffer 2
            exit(0);
         break;
         default://proceso padre
            close(ipc1[1]);//cierra descriptor de entrada de tuberia 1
	    close(ipc2[1]);//cierra descriptor de entrada de tuberia 2

               leido = read(ipc1[0], buff1, sizeof(buff1));//lee contenido de tuberia 1
               if(leido < 1){
                  write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
               }else {
                  write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
                  write (STDOUT_FILENO, buff1, leido-1);//muestra lo leido de la tuberia
                  printf(", por el proceso padre, pid %d \n", getpid());
               }


	       leido = read(ipc2[0], buff2, sizeof(buff2));//lee contenido de tuberia 2
               if(leido < 1){
                  write (STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
               }else {
                  write (STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
                  write (STDOUT_FILENO, buff2, leido-1);//muestra lo leido de la tuberia
                  printf(", por el proceso padre, pid %d \n", getpid());
               }
            }

            close(ipc1[0]);//cierra descriptor de salida de tuberia 1
	    close(ipc2[0]);//cierra descriptor de salida de tuberia 2
            wait(NULL);//espera a que termine alguno de los hijos
            wait(NULL);//espera a que termine el otro hijo restante
            exit(0);
         break;
      }
   }

//El error esta en utilizar una sola tuberia para comunicar al proceso padre con dos hijos.

//Se debe crear una tuberia para comunicar cada proceso hijo con el padre.

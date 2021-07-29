/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define DATA "INFORMACION IMPORTANTE"
#define BUFF_SIZE 80

void pipe_sign_handler(int a){//manejador de señal
   
   write (STDOUT_FILENO, "\n Problema con pipeline.\n ", sizeof("\n Problema con pipeline.\n"));
   exit(-1);
}

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);//asigna el manejador de señal a la señal SIGPIPE
   
   if (pipe(ipc) == -1)//crea tuberia con sus descriptores en ipc[]
      exit(-1);
   
   //close(ipc[0]); Se comentó esta linea. Se estaba cerrando el descriptor de salida para lectura para ambos procesos
   
   switch (fork()){ //crea proceso hijo
      
      case 0://proceso hijo
         close(ipc[1]);//cierra descriptor de entrada
         printf("Leyendo tuberia... \n");
         leido = read(ipc[0], buff, sizeof(buff));//lee tuberia y guarda contenido en buffer
         if(leido < 1){
            write(STDOUT_FILENO, "\nError al leer tuberia", sizeof("\nError al leer tuberia"));
         }else {
            write(STDOUT_FILENO, "Leido de la tuberia ", sizeof("\nLeido de la tuberia"));
            write(STDOUT_FILENO, buff, leido-1);
            printf(", por el proceso hijo, pid %d \n", getpid());
         }
	 close(ipc[0]);
         exit(0);
         
      default:
	 close(ipc[0]);//se agregó esta linea. Se cierra el descriptor de salida
         strncpy(buff, DATA, sizeof(DATA));
         write(ipc[1], buff, sizeof(DATA));
      
         wait(NULL);      
         
	 close(ipc[1]);
         exit(0);      
   }
}

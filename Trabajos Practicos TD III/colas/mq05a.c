/*
 * Ejercicio 5a del TP de Cola de mensajes
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3"  

   int err, leido;
   char buff[1024];   
   mqd_t mqd = 0; 
   struct mq_attr attr, attr_rcv;
   struct sigevent sev;   
   int retval;


void lee_mensaje(int a){ 

   leido = mq_receive(mqd, buff, sizeof(buff),0);
   write(STDOUT_FILENO, buff, sizeof(buff));
}

int main() {

   signal(SIGINT, lee_mensaje);    //Ctrl + C

   printf("Soy el proceso: %d \n ",getpid());

   // abrir y crear cola de mensajes
   mqd = mq_open(MQ_PATH, O_RDONLY, 0666, &attr);
   if (mqd < 0) {
      printf ("error en mq_open()");
      exit(-1);  }

   printf("Cola de mensajes abierta\n");

   while(1){

   }  //fin while

   exit(0);
}

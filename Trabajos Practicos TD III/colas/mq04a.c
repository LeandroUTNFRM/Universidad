/*
* Ejercicio 4a del TP de Cola de mensajes
* 
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
mqd_t mqd; 
struct mq_attr attr, attr_rcv;

void sig_user1(int a){
   
   err = mq_close(mqd);
   if (( err < 0 )){
      write(STDOUT_FILENO, "\nerror en mq_close()\n", sizeof("\nerror en mq_close()\n"));
      exit(-1);   }

   write(STDOUT_FILENO, "\nCola de mensajes cerrada\n", sizeof("\nCola de mensajes cerrada\n"));


   err = mq_unlink(MQ_PATH);
   if(err == -1){
        write(STDOUT_FILENO, ")\nerror en mq_unlink())\n", sizeof(")\nerror en mq_unlink())\n"));
      exit(-1);    }

   write(STDOUT_FILENO, ")\nCola de mensajes eliminada\n", sizeof(")\nCola de mensajes eliminada\n"));

   write(STDOUT_FILENO, "\nTerminando proceso...\n", sizeof("\nTerminando proceso...\n"));
   
   exit(0);
}

int main() {
   
   signal(SIGUSR1, sig_user1);

   printf ("Mi pid es %d\n", getpid());


   attr.mq_msgsize = sizeof(buff);
   attr.mq_maxmsg = 5;

   mqd = mq_open(MQ_PATH, O_WRONLY | O_CREAT | O_NONBLOCK, 0666, &attr);//se cambió O_RDONLY por O_WRONLY
   if (mqd < 0) {
      printf ("error en mq_open()");      
      exit(-1) ;}

   printf("Cola de mensajes creada\n");
   
   while(1) {
      
      err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  //strlen nos da la longitud de una cadena
      if(err == -1){
         printf ("error en mq_send()");
         exit(-1);}
 
      printf("Mensaje enviado (%d)\n", err);

      sleep(1);

   }


   exit(0);
}

//Respuesta:
//Ejecutando este programa solo, escribirá mensajes hasta que esté llena la cola y luego se 
//terminará. No hay proceso que esté leyendo los mensajes.

//Si se ejecuta el programa que lee mensajes de cola al mismo tiempo, no se terminará
//el proceso porque siempre habrá espacio para un nuevo mensaje.

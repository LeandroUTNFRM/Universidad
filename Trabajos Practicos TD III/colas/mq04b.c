/*
* Ejercicio 4b del TP de Cola de mensajes
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

#define MQ_PATH "/MQ_TD3"

int main() {

   int err, leido;
   char buff[1024];
   mqd_t mqd;
   struct mq_attr attr, attr_rcv;


   printf ("Mi pid es %d\n", getpid());

   mqd = mq_open(MQ_PATH, O_RDONLY | O_NONBLOCK, 0666, &attr);
   if (mqd < 0) {
      printf ("error en mq_open()");
      exit(-1) ;}

   printf("Cola de mensajes abierta correctamente\n");

   while(1) {
      leido = 0;
      leido = mq_receive(mqd, buff, attr_rcv.mq_msgsize, 0);
      if(leido < 0){
         printf ("error en mq_receive()");
         exit(-1);}

      printf("Mensaje leido: %s\n", buff);

      sleep(1);

   }


   exit(0);
}
//Respuesta:
//Ejecutando este programa solo, leerá mensajes hasta que esté vacia la cola.
//No hay ningun proceso escribiendo mensajes.
//Si la cola estaba vacia en un principio, el proceso se terminará apenas intente leer la 
//primera vez.

//Si se ejecuta el programa que lee mensajes de cola al mismo tiempo, no se terminará 
//el proceso porque siempre habrá mensajes para leer.

/*
* Ejercicio 3 del TP de Cola de mensajes
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

   mqd = mq_open(MQ_PATH, O_RDONLY, 0666, &attr);
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

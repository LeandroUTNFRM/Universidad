/* Ejercicio 6 del TP mutex uso mutex dinamicos */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int t,total, vueltas , s ;
pthread_mutex_t mtx;
pthread_mutexattr_t mtxattr;


void *HILO0(void *nro) {
int local1 , j, numero,s;

	numero= *(int*)nro;

	s=pthread_mutex_lock(&mtx);         
   	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);  }

   	printf("Hilo= %d decrementa mutex\n", numero);

	for(j=0;j< vueltas;j++){
   		local1 = total;
   		local1++;
   		total=local1;
   	}

   	printf("Hola soy, el thread %d, total= %d\n", numero,total);

   	printf("Hilo= %d incrementa mutex\n", numero);

   	s=pthread_mutex_unlock(&mtx);     
   	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);   }

   	pthread_exit(NULL);
}

int main()   {
pthread_t hilo[5];
int rc ;
int arre[5];

	total=0;
   	vueltas=100000;

  	s=pthread_mutexattr_init(&mtxattr); //inicia el atributos mutex
 	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);  }

  	s=pthread_mutexattr_settype(&mtxattr,PTHREAD_MUTEX_NORMAL); //SETEA e ltipo en atributos mutex
  	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);  }

   	s=pthread_mutex_init(&mtx,&mtxattr); //inicia el mutex
  	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);  }

   	for(t=0; t< 5 ; t++){
   		printf("El main ... creando el thread nro %d\n", t);
   		arre[t] = t;

   		rc = pthread_create(&hilo[t], NULL, HILO0 , (void *)&arre[t]  ); 
   		if (rc){
        	printf("ERROR; pthread_create() = %d\n", rc);
	        exit(-1); }
	}
	pthread_join(hilo[0],NULL);
    pthread_join(hilo[1],NULL);
    pthread_join(hilo[2],NULL);
    pthread_join(hilo[3],NULL);
    pthread_join(hilo[4],NULL);

    s=pthread_mutex_destroy(&mtx);    //destruye el mutex
  	if (s!=0){
      	printf("ERROR; pthread_mutex() = %d\n", s);
      	exit(-1);  }

    printf("Total= %d\n",total);

    pthread_exit(NULL);

}

//Respuestas:
//El objetivo del programa es crear 5 hilos que aumenten 100000 el valor de una variable global.

//La diferencia con los ejercicios anteriores es que utiliza inicializacion dinamica de mutex
//en vez de inicializacion est??tica y que al final del programa destruye el mutex.

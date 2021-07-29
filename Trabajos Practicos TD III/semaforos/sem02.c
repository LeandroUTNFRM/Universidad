/* Ejercicio 2 del TP de semaforos sin nombre */

#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>   

//------- variables globales

int t, total, contador, s;
sem_t sem;

//------------------------------------------------------------

void *HILO(void *nro){
int local, j, numero;
	
	numero = *(int*)nro;

	s = sem_wait(&sem);//decrementa semaforo
	if(s != 0){
		printf("Error.");
		exit(-1);
	}

	for(j=0; j < contador; j++){
		local = total;
		local = local + 10;
		total = local;	   }

	s = sem_post(&sem);//incrementa semaforo
	if(s != 0){
		printf("Error.");
		exit(-1);
	}

	printf("Hilo %d, total = %d\n", numero,total);
	
	pthread_exit(NULL);
}

//------------------------------------------------------------

int main()	{
int rc, n_hilos;
int arre[10];
   
	total = 0;
	contador = 100000;
	n_hilos = 10;

	//inicializar semaforo
	s = sem_init(&sem, 0, 1);//0: entre hilos, 1: valor de inicio
	if(s != 0){
		printf("Error.");
		exit(-1);
	}

	pthread_t hilo[n_hilos];
	
	for(t=0; t < n_hilos; t++){
	
		arre[t] = t;
		
		rc = pthread_create(&hilo[t], NULL, HILO , (void *)&arre[t]  );
		if (rc){
			printf("ERROR; pthread_create() = %d\n", rc);
			exit(-1);      }
	}

//-------------------------------------

	for(t=0; t < n_hilos; t++){
		pthread_join(hilo[t],NULL);   
	}
	
	printf("total = %d\n",total);
	
	pthread_exit(NULL);
}

//Respuestas:
//El objetivo del programa es crear 10 hilos que aumenten en 100 una variable global.
//La salida por consola es 1000.
//La variable total al finalizar el programa deberia tener un valor de 1000.

//Cambiando el valor de inicializacion de contador de 10 a 100000 se observa que en cada
//ejecucion del programa se obtiene un resultado diferente.
//El resultado final deberia ser 10000000.

//El problema es que, al aumentar el contador (cantidad de veces que cada hilo suma 10 a la
//variable global), en ese tiempo otros hilos pueden comenzar a ejecutarse y luego comiencen
//a pisar el valor de la variable global.



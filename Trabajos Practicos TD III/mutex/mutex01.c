/* Ejercicio 2 del TP mutex 
 acceso a variables compartidas sin uso mutex */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/* Variables Globales */
int t,total, vueltas ;

void *HILO0(void *nro) {

int local1 , j, numero;

	numero= *(int*)nro;
	
	for(j=0;j< vueltas;j++){
		local1 = total;
		local1++;
		total=local1;
	}
	
	printf("Hola soy, el thread %d, total= %d\n", numero,total);
	pthread_exit(NULL);
}

int main() {

pthread_t hilo[5];
int rc ;
int arre[5];

	total=0;
	vueltas=100000;
	
	for(t=0; t< 5 ; t++){
		printf("El main ... creando el thread nro %d\n", t);
		arre[t] = t;
		
		rc = pthread_create(&hilo[t], NULL, HILO0 , (void *)&arre[t]  ); 
		if (rc){
			printf("ERROR; pthread_create() = %d\n", rc);
			exit(-1);    }
	}
	
	pthread_join(hilo[0],NULL);
	pthread_join(hilo[1],NULL);
	pthread_join(hilo[2],NULL);
	pthread_join(hilo[3],NULL);
	pthread_join(hilo[4],NULL);
	
	printf("Total= %d\n",total);
	
	pthread_exit(NULL);
}

//Respuestas:
//El proposito del programa es crear 5 hilos que cada uno aumente 100000 el valor de una
//variable global.

//El valor de la variable global total deberia ser 500000.

//El valor de la variable global total es diferente cada vez que se ejecuta el programa.

//Lo que sucede es que a cada hilo le toma cierta cantidad de tiempo tomar el valor de la
//variable global, pasarlo a una variable local, aumentar el valor y guardar el resultado
//nuevamente en la variable global.
//En ese tiempo, otro proceso puede tomar un valor anterior a modificaciones de la
//variable global y pisar el resultado final.

/* Ejercicio 7 del TP mutex  productor-consumidor con mutex */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUFFER 5		//tamanio del buffer
 

pthread_mutex_t mutex;      // mutex de acceso al buffer compartido
int cant;                 	// numero de elementos en el buffer 
int buffer[MAX_BUFFER];     // buffer comun 
int DATOS_A_PRODUCIR=20;

///////////////////////////////////////////////////////////////

void Productor() {     //PRODUCTOR 

int dato, i, pos;
	pos=0;
	dato=1000;
	i=0;

	while( i < DATOS_A_PRODUCIR ) {
	
		sleep(1);	//este retardo es para ver como funciona con mutex
		
		pthread_mutex_lock(&mutex);   
		
		while (cant < MAX_BUFFER){ 		//si buffer lleno
		
			buffer[pos] = dato;
			dato++;
			pos = (pos + 1) ;
			if (pos>= MAX_BUFFER) {
				pos=0;	}
			cant++;
			i++;
			printf("Productor posicion: %d, dato: %d, cantidad: %d, i: %d\n",pos,dato,cant,i);	 
		}
		
		pthread_mutex_unlock(&mutex);	     
	}
		printf("Termino produccion: %d\n",i);
		pthread_exit(0);
}

///////////////////////////////////////////////////////////////

void Consumidor(){    // CONSUMIDOR

int dato, i, pos;
	pos=0;
	i=0;
	
	while( i < DATOS_A_PRODUCIR ) {
	
		pthread_mutex_lock(&mutex); 	
		
		while (cant > 0){ 		// si buffer vacio
			dato = buffer[pos];
			pos = (pos + 1) ;
			if (pos > (MAX_BUFFER-1)) {
				pos=0;	}
			cant--;
			i++;
			printf("Consumidor posicion: %d, dato: %d, cantidad: %d, i: %d\n",pos,dato,cant,i);	 
		}
		
		pthread_mutex_unlock(&mutex);
	}
	printf("Termino Consumo: %d\n",i);
	
	pthread_exit(0);
}
 ///////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

pthread_t th1, th2;

	pthread_mutex_init(&mutex, NULL);//atributos por defecto - no es necesario inicializar los atributos del mutex
	
	if (argc == 2){
		printf ("argv[0]= %s , argv[1]= %s ,  argc=%d\n", argv[0], argv[1], argc);
		DATOS_A_PRODUCIR=atoi(argv[1]);
	}
	
	pthread_create(&th1, NULL, (void *)&Productor, NULL);
	pthread_create(&th2, NULL, (void *)&Consumidor, NULL);
	
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	
	printf("Productor-Consumidor con mutex: termina\n");
	
	pthread_exit(0);


}

//Respuestas:

//El objetivo del programa es pasar de un hilo a otro una cantidad de datos mayor al tamaño
//del buffer utilizado para dicha tarea.
//El hilo productor debe llenar el buffer, el hilo consumidor debe vaciarlo y este proceso se
//repite tantas veces como sea necesario para enviar los datos del productor al consumidor.

//El productor decrementa el mutex cuando va a llenar el buffer y luego lo incrementa para
//permitir que el consumidor pueda acceder al buffer y que lea los datos.

//El consumidor decrementa el mutex cuando va a vaciar el buffer y luego lo incrementa para
//permitir que el productor pueda acceder al buffer y volver a llenarlo con datos.

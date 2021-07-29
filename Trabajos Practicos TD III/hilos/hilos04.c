/*  
 * Ejercicio 4 del TP Hilos
 *   
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int suma=0;

void *hilo1 (void * nro)
{
   int numero, temp;
   
   numero = *(int*)nro;
   temp = suma;
   //usleep(300);
   pthread_yield();
   temp = temp + 1 ;
   suma = temp;
   
   printf("Ejecutando hilo %d\n", numero);
   pthread_exit(NULL);
}

int main()
{
   pthread_t hilo[100];
   int rc, t, arre[100];

   for(t=0; t< 100 ; t++){
      printf("Creando el hilo %d\n", t);
      arre[t] = t;
      rc = pthread_create(&hilo[t], NULL, hilo1 , (void *)(&arre[t]) );
      if (rc){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);
      }
   }

   int i;
   for (i=0; i<100;i++) {
       while(pthread_join(hilo[i], NULL));
   }
  
   printf("Valor de globlal = %d\n", suma);
      
   exit(0);
}

//Respuestas:
//El proposito del programa es crear 100 hilos que aumenten en 1 el valor de una variable
//global.
//La variable global suma termina con valor 100, pero ejecutando muchas veces pueden
//encontrarse casos en los que de un valor menor.

//Descomentando la linea 18 la variable global suma termina siempre con un valor diferente.
//Se hace evidente que los distintos hilos pisan la variable.
//Un hilo se puede comenzar a ejecutar mientras los otros hilos estan ejecutando su retardo,
//y por lo tanto el valor que recibe de la variable global es menor que el verdadero porque
//los otros procesos todavia no realizaron su operación.

//Se presenta el mismo problema usando pthread_yield porque el hilo cede la cpu a otro hilo
//y luego sobreescribe la variable global, desapareciendo el progreso realizado por los demas
//hilos.

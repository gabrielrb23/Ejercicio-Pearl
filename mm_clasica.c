/**************************************************************
 *     Pontificia Universidad Javeriana
 *     Autor: Gabriel Riaño
 *     Materia: Sistemas Operativos
 *     Fichero: Modulo de multiplicación de matrices
 *     Descripcion: Implementación del algoritmo clásico de 
 *                  multiplicación de matrices cuadradas NxN
 *                  utilizando hilos POSIX (Pthreads) para la 
 *                  evaluación de rendimiento computacional.
 **************************************************************/

 #include <stdio.h>       
 #include <stdlib.h>      
 #include <sys/time.h>    
 #include <time.h>        
 #include <pthread.h>     
 #include "mm_clasica.h"  // Cabecera con las declaraciones compartidas
 
 // Definición del tamaño total de memoria para las matrices
 #define DATA_SIZE (1024*1024*64*3)
 
 // Bloque de memoria compartido para las tres matrices
 double MEM_CHUNK[DATA_SIZE];
 
 // Punteros a las matrices A, B y C
 double *mA, *mB, *mC;
 
 // Mutex global para sincronización
 pthread_mutex_t MM_mutex;
 
 // Variables para control de tiempo
 static struct timeval start, stop;
 
 /**
  * Función: llenar_matriz
  * Descripción: Inicializa las matrices mA y mB con valores predefinidos
  *              y pone en cero la matriz mC.
  */
 void llenar_matriz(int SZ) {
     srand48(time(NULL)); // Semilla para valores aleatorios reproducibles
     for (int i = 0; i < SZ * SZ; i++) {
         mA[i] = 1.1 * i;  // Inicializa A
         mB[i] = 2.2 * i;  // Inicializa B
         mC[i] = 0.0;      // Inicializa C en cero
     }
 }
 
 /**
  * Función: print_matrix
  * Descripción: Imprime la matriz si el tamaño es pequeño (<12).
  */
 void print_matrix(int sz, double *matriz) {
     if (sz < 12) {
         for (int i = 0; i < sz * sz; i++) {
             if (i % sz == 0) printf("\n");
             printf(" %.3f ", matriz[i]);
         }
         printf("\n>-------------------->\n");
     }
 }
 
 /**
  * Función: inicial_tiempo
  * Descripción: Captura el tiempo de inicio del experimento.
  */
 void inicial_tiempo() {
     gettimeofday(&start, NULL);
 }
 
 /**
  * Función: final_tiempo
  * Descripción: Captura el tiempo de fin y muestra la diferencia en microsegundos.
  */
 void final_tiempo() {
     gettimeofday(&stop, NULL);
     stop.tv_sec -= start.tv_sec;
     printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
 }
 
 /**
  * Función: mult_thread
  * Descripción: Implementa la multiplicación clásica de matrices por bloques
  *              asignados a cada hilo. Cada hilo calcula un subconjunto de filas.
  */
 void *mult_thread(void *variables) {
     struct parametros *data = (struct parametros *)variables;
 
     // Cálculo de rango de filas que este hilo debe procesar
     int ini = (data->N / data->nH) * data->idH;
     int fin = (data->N / data->nH) * (data->idH + 1);
 
     // Multiplicación fila-columna clásica
     for (int i = ini; i < fin; i++) {
         for (int j = 0; j < data->N; j++) {
             double *pA = mA + (i * data->N);  // Fila i de A
             double *pB = mB + j;              // Columna j de B (recorriendo en pasos de N)
             double sumaTemp = 0.0;
 
             for (int k = 0; k < data->N; k++, pA++, pB += data->N) {
                 sumaTemp += (*pA * *pB);
             }
             mC[i * data->N + j] = sumaTemp; // Almacena resultado en C
         }
     }
 
     // Mutex usado como placeholder por ahora
     pthread_mutex_lock(&MM_mutex);
     pthread_mutex_unlock(&MM_mutex);
 
     free(data); // Libera memoria asignada para los parámetros del hilo
     pthread_exit(NULL); // Finaliza hilo
 }
 
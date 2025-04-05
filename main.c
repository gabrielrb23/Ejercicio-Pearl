/**************************************************************
 *     Pontificia Universidad Javeriana
 *     Autor: Gabriel Riaño
 *     Materia: Sistemas Operativos
 *     Fichero: Programa principal para multiplicación de matrices
 *     Descripcion: Función principal para la ejecución del
 *                  algoritmo clásico de multiplicación de
 *                  matrices cuadradas NxN utilizando hilos
 *                  POSIX (Pthreads). Crea los hilos, coordina
 *                  la ejecución y mide el tiempo de cálculo.
 **************************************************************/

 #include <stdio.h>         
 #include <stdlib.h>        
 #include <pthread.h>       
 #include "mm_clasica.h"    // Cabecera del módulo de multiplicación
 
 int main(int argc, char *argv[]) {
     // Validación de argumentos de entrada
     if (argc < 3) {
         printf("Uso correcto:\n $ ./ejecutable tamMatriz numHilos\n");
         return -1;
     }
 
     int SZ = atoi(argv[1]);       // Tamaño de la matriz NxN
     int n_threads = atoi(argv[2]); // Número de hilos a lanzar
 
     pthread_t threads[n_threads]; // Arreglo de identificadores de hilos
     pthread_attr_t attr;          // Atributos de los hilos
 
     // Asignación de bloques de memoria para matrices A, B y C
     mA = MEM_CHUNK;
     mB = mA + SZ * SZ;
     mC = mB + SZ * SZ;
 
     // Inicialización de las matrices con valores conocidos
     llenar_matriz(SZ);
     print_matrix(SZ, mA);
     print_matrix(SZ, mB);
 
     // Inicia la medición de tiempo
     inicial_tiempo();
 
     // Inicialización de atributos y mutex para los hilos
     pthread_mutex_init(&MM_mutex, NULL);
     pthread_attr_init(&attr);
     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 
     // Creación de los hilos y asignación de tareas a cada uno
     for (int j = 0; j < n_threads; j++) {
         struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
         datos->idH = j;           // ID del hilo
         datos->nH = n_threads;    // Número total de hilos
         datos->N  = SZ;           // Dimensión de la matriz
         pthread_create(&threads[j], &attr, mult_thread, (void *)datos);
     }
 
     // Espera a que todos los hilos terminen
     for (int j = 0; j < n_threads; j++)
         pthread_join(threads[j], NULL);
 
     // Finaliza la medición de tiempo
     final_tiempo();
 
     // Imprime la matriz resultante
     print_matrix(SZ, mC);
 
     // Limpieza de recursos
     pthread_attr_destroy(&attr);
     pthread_mutex_destroy(&MM_mutex);
     pthread_exit(NULL);
 }
 
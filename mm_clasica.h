/**************************************************************
 *     Pontificia Universidad Javeriana
 *     Autor: Gabriel Riaño
 *     Materia: Sistemas Operativos
 *     Fichero: Interfaz de multiplicación de matrices
 *     Descripcion: Cabecera del módulo de multiplicación de matrices
 *                  cuadradas NxN utilizando el algoritmo clásico,
 *                  implementado con hilos POSIX (Pthreads) para
 *                  evaluación de rendimiento.
 **************************************************************/

 #ifndef MM_CLASICA_H
 #define MM_CLASICA_H
 
 #include <pthread.h>  // Biblioteca para manejo de hilos POSIX
 
 // Prototipo de función que llena las matrices mA y mB con valores definidos
 void llenar_matriz(int SZ);
 
 // Prototipo de función que imprime una matriz si el tamaño es pequeño
 void print_matrix(int sz, double *matriz);
 
 // Prototipo de función que inicializa la medición de tiempo
 void inicial_tiempo();
 
 // Prototipo de función que finaliza la medición de tiempo e imprime el resultado
 void final_tiempo();
 
 // Prototipo de función que ejecuta la multiplicación de matrices dentro de un hilo
 void *mult_thread(void *variables);
 
 // Variables globales para las matrices de trabajo
 extern double *mA, *mB, *mC;        // Punteros a las matrices A, B y C
 extern double MEM_CHUNK[];          // Bloque de memoria contiguo donde residen las matrices
 extern pthread_mutex_t MM_mutex;    // Mutex para sincronización entre hilos
 
 // Estructura que contiene los parámetros necesarios para cada hilo
 struct parametros {
     int nH;   // Número total de hilos
     int idH;  // ID del hilo actual
     int N;    // Dimensión de la matriz (NxN)
 };
 
 #endif
 
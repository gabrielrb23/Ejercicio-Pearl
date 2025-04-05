#!/usr/bin/perl

#**************************************************************
#     Pontificia Universidad Javeriana
#     Autor: Gabriel Riaño
#     Materia: Sistemas Operativos
#     Fichero: Lanzador de procesos por lotes
#     Descripcion: Automatización de ejecuciones para obtención
#                  de 30 resultados de ejecuciones de los 
#                  benchmarks de distintos sabores con el
#                  propósito de hacer experimentos de carácter
#                  científico (fiabilidad y precisión)
#****************************************************************/

# Obtiene el directorio actual de trabajo
$Path = `pwd`;
chomp($Path);  # Elimina el salto de línea al final de la cadena

# Define la lista de ejecutables a probar
@Nombre_Ejecutable = ("main");

# Define los tamaños de matriz a utilizar en las pruebas
@Size_Matriz = (500, 1000);

# Define el número de hilos a usar en cada prueba
@Num_Hilos = (1, 10, 20);

# Número de veces que se repetirá cada prueba
$Repeticiones = 30;

# Itera sobre cada ejecutable en la lista
foreach $Nombre_Ejecutable (@Nombre_Ejecutable) {
    # Itera sobre cada tamaño de matriz
    foreach $size (@Size_Matriz) {
        # Itera sobre cada número de hilos
        foreach $hilo (@Num_Hilos) {

            # Define el nombre del archivo donde se guardarán los resultados
            $file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

            # Ejecuta el programa repetidamente y almacena los resultados
            for ($i = 0; $i < $Repeticiones; $i++) {

                # Ejecuta el programa con los parámetros especificados y almacena la salida en el archivo
                system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

		# Imprime el comando ejecutado
                #printf("$Path/$Nombre_Ejecutable $size $hilo \n"); 
            }

            # Cierra el archivo
            close($file);
        }
    }
}


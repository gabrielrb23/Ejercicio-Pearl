 #**************************************************************
#     Pontificia Universidad Javeriana
#     Autor: Gabriel Riaño
#     Materia: Sistemas Operativos
#     Fichero: Makefile
#     Descripcion: Compilación del proyecto de multiplicación
#                  de matrices con hilos POSIX, incluyendo el
#                  ejecutable compatible con lanzador.pl.
#**************************************************************

# Compilador y banderas
CC = gcc
CFLAGS = -Wall -pthread

# Archivos fuente
SRC = main.c mm_clasica.c
OBJ = main.o mm_clasica.o

# Nombre del ejecutable
TARGET = main

# Regla por defecto
all: $(TARGET)

# Reglas de compilación
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c mm_clasica.h
	$(CC) $(CFLAGS) -c main.c

mm_clasica.o: mm_clasica.c mm_clasica.h
	$(CC) $(CFLAGS) -c mm_clasica.c

# Limpia archivos intermedios y el ejecutable
clean:
	rm -f *.o $(TARGET)

# Limpia también los archivos de salida generados por lanzador.pl
clean_all: clean
	rm -f *.dat

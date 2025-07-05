#ifndef HEAP_H
#define HEAP_H

#include <string>
#include "Usuario.h" // Incluir Usuario.h

// Prototipos de funciones globales para el heap
int padre(int i);
int izq(int i);
int der(int i);
void intercambiar(Usuario& a, Usuario& b);
int valorPrioridad(std::string p);
void max_heapify(Usuario A[], int n, int i);
void insertarHeap(Usuario A[], int& n, Usuario nuevo);
Usuario extraerMax(Usuario A[], int& n);
void mostrarTop5(Usuario A[], int n);

#endif // HEAP_H

#include "Heap.h"
#include <iostream>
#include <string> // Necesario para std::string

int padre(int i) { return (i - 1) / 2; }
int izq(int i) { return 2 * i + 1; }
int der(int i) { return 2 * i + 2; }

void intercambiar(Usuario& a, Usuario& b) {
    Usuario temp = a;
    a = b;
    b = temp;
}

int valorPrioridad(std::string p) {
    if (p == "VIP") return 5;
    if (p == "Medico") return 4;
    if (p == "Seguridad") return 3;
    if (p == "Discapacitado") return 2;
    return 1; // Prioridad por defecto para "General" u otros
}

void max_heapify(Usuario A[], int n, int i) {
    int l = izq(i);
    int r = der(i);
    int mayor = i;

    if (l < n && valorPrioridad(A[l].prioridad) > valorPrioridad(A[mayor].prioridad))
        mayor = l;
    if (r < n && valorPrioridad(A[r].prioridad) > valorPrioridad(A[mayor].prioridad))
        mayor = r;

    if (mayor != i) {
        intercambiar(A[i], A[mayor]);
        max_heapify(A, n, mayor);
    }
}

void insertarHeap(Usuario A[], int& n, Usuario nuevo) {
    // Asumiendo que A[] tiene suficiente capacidad (e.g., 5000 como en main.cpp)
    if (n >= 5000) {
        std::cout << "Heap lleno, no se puede insertar mas usuarios." << std::endl;
        return;
    }
    A[n] = nuevo;
    int i = n;
    n++;

    // Heapify-Up
    while (i > 0 && valorPrioridad(A[padre(i)].prioridad) < valorPrioridad(A[i].prioridad)) {
        intercambiar(A[i], A[padre(i)]);
        i = padre(i);
    }
}

Usuario extraerMax(Usuario A[], int& n) {
    if (n <= 0) {
        std::cout << "Heap vacio. No se puede extraer el maximo.\n";
        return Usuario();
    }
    Usuario maximo = A[0];
    A[0] = A[n - 1];
    n--;
    max_heapify(A, n, 0);
    return maximo;
}

void mostrarTop5(Usuario A[], int n) {
    // Crear una copia del heap para no modificar el original al extraer
    Usuario copia[5000];
    int temp_n = 0;

    // Copiar solo los elementos válidos del heap original
    for (int i = 0; i < n; ++i) {
        copia[i] = A[i];
        temp_n++;
    }

    std::cout << "\n--- Proximos 5 accesos (por prioridad) ---\n";
    if (temp_n == 0) {
        std::cout << "El heap esta vacio.\n";
        std::cout << "------------------------------------------\n";
        return;
    }

    for (int i = 0; i < 5 && temp_n > 0; ++i) {
        Usuario u = extraerMax(copia, temp_n); // Extrae de la copia
        std::cout << u.dni << ", " << u.nombreCompleto << ", " << u.prioridad
                  << ", Zona: " << u.zona << ", Hora: " << u.horaIngreso << std::endl;
    }
    std::cout << "------------------------------------------\n";
}

#include <iostream>
#include <string>

using namespace std;

struct Usuario {
    string dni;
    string nombreCompleto;
    string prioridad;
    char zona;
    string horaIngreso;
};

// Convierte prioridad a valor numérico
int valorPrioridad(string p) {
    if (p == "VIP") return 5;
    if (p == "Medico") return 4;
    if (p == "Seguridad") return 3;
    if (p == "Discapacitado") return 2;
    return 1; // Público general
}

int padre(int i) { return (i - 1) / 2; }
int izq(int i) { return 2 * i + 1; }
int der(int i) { return 2 * i + 2; }

void intercambiar(Usuario& a, Usuario& b) {
    Usuario temp = a;
    a = b;
    b = temp;
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
    A[n] = nuevo;
    int i = n;
    n++;

    while (i > 0 && valorPrioridad(A[padre(i)].prioridad) < valorPrioridad(A[i].prioridad)) {
        intercambiar(A[i], A[padre(i)]);
        i = padre(i);
    }
}

Usuario extraerMax(Usuario A[], int& n) {
    if (n <= 0) {
        cout << "Heap vacío\n";
        return Usuario();
    }

    Usuario maximo = A[0];
    A[0] = A[n - 1];
    n--;
    max_heapify(A, n, 0);
    return maximo;
}

void mostrarTop5(Usuario A[], int n) {
    Usuario copia[100];
    int temp_n = n;
    for (int i = 0; i < n; i++) copia[i] = A[i];

    cout << "\n--- Próximos 5 accesos ---\n";
    for (int i = 0; i < 5 && temp_n > 0; i++) {
        Usuario u = extraerMax(copia, temp_n);
        cout << u.dni << ", " << u.nombreCompleto << ", " << u.prioridad
             << ", Zona " << u.zona << ", Hora: " << u.horaIngreso << endl;
    }
    cout << "--------------------------\n";
}

int main() {
    Usuario heap[100];
    int n = 0; // cantidad actual de elementos

    int cantidad;
    cout << "Ingrese cantidad de asistentes a registrar: ";
    cin >> cantidad;

    for (int i = 0; i < cantidad; i++) {
        Usuario u;
        cout << "\nAsistente #" << i + 1 << endl;
        cout << "DNI: "; cin >> u.dni;
        cout << "Nombre: "; cin.ignore(); getline(cin, u.nombreCompleto);
        cout << "Prioridad (VIP/Medico/Seguridad/Discapacitado/Publico): "; cin >> u.prioridad;
        cout << "Zona (A/B/C/etc): "; cin >> u.zona;
        cout << "Hora de ingreso (HH:MM): "; cin >> u.horaIngreso;

        insertarHeap(heap, n, u);
    }

    mostrarTop5(heap, n);

    return 0;
}

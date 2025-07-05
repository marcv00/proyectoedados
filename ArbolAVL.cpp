#include "ArbolAVL.h"
#include <iostream>
#include <string> // Necesario para std::string, std::to_string, etc.
#include <algorithm> // Necesario para std::max

// Constructor
ArbolAVL::ArbolAVL() : raiz(nullptr) {}

// Destructor
ArbolAVL::~ArbolAVL() {
    liberarNodos(raiz);
}

// Función auxiliar para liberar memoria recursivamente
void ArbolAVL::liberarNodos(Nodo* nodo) {
    if (nodo) {
        liberarNodos(nodo->izq);
        liberarNodos(nodo->der);
        delete nodo;
    }
}

void ArbolAVL::insertar(std::string id, std::string zona, int hora) {
    raiz = insertarRecursivo(raiz, id, zona, hora);
}

Nodo* ArbolAVL::insertarRecursivo(Nodo* nodo, std::string id, std::string zona, int hora) {
    if (!nodo)
        return new Nodo(id, zona, hora);

    std::string claveNueva = std::to_string(hora) + zona;
    std::string claveActual = std::to_string(nodo->horaIngreso) + nodo->zonaAcceso;

    if (claveNueva < claveActual) {
        nodo->izq = insertarRecursivo(nodo->izq, id, zona, hora);
        if (nodo->izq) nodo->izq->padre = nodo;
    } else if (claveNueva > claveActual) {
        nodo->der = insertarRecursivo(nodo->der, id, zona, hora);
        if (nodo->der) nodo->der->padre = nodo;
    } else {
        // Aquí usaremos el DNI para la comparación final para asegurar la unicidad del nodo si la clave es la misma
        if (id < nodo->idAsistente) { // Usamos el ID del asistente (DNI) para desambiguar
            nodo->izq = insertarRecursivo(nodo->izq, id, zona, hora);
            if (nodo->izq) nodo->izq->padre = nodo;
        } else {
            nodo->der = insertarRecursivo(nodo->der, id, zona, hora);
            if (nodo->der) nodo->der->padre = nodo;
        }
    }

    actualizarFactor(nodo);
    return rebalance(nodo);
}

int ArbolAVL::calcularAltura(Nodo* nodo) {
    if (!nodo) return 0;
    // La altura se almacena en el nodo si decides precalcularla,
    // o se recalcula así.
    return 1 + std::max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
}

void ArbolAVL::actualizarFactor(Nodo* nodo) {
    if (nodo) {
        nodo->factor_balance = calcularAltura(nodo->izq) - calcularAltura(nodo->der);
    }
}

Nodo* ArbolAVL::rebalance(Nodo* nodo) {
    if (!nodo) return nodo;

    actualizarFactor(nodo); // Asegura que el factor de balance esté actualizado

    // Caso Izquierda-Izquierda o Izquierda-Derecha
    if (nodo->factor_balance > 1) {
        if (nodo->izq && nodo->izq->factor_balance < 0) { // Caso Izquierda-Derecha
            nodo->izq = rotarIzquierda(nodo->izq);
        }
        return rotarDerecha(nodo); // Caso Izquierda-Izquierda
    }

    // Caso Derecha-Derecha o Derecha-Izquierda
    if (nodo->factor_balance < -1) {
        if (nodo->der && nodo->der->factor_balance > 0) { // Caso Derecha-Izquierda
            nodo->der = rotarDerecha(nodo->der);
        }
        return rotarIzquierda(nodo); // Caso Derecha-Derecha
    }

    return nodo;
}

Nodo* ArbolAVL::rotarIzquierda(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->der;
    Nodo* temp_izq = nuevaRaiz->izq;

    // Realiza la rotación
    nuevaRaiz->izq = nodo;
    nodo->der = temp_izq;

    // Actualiza los padres
    if (temp_izq) temp_izq->padre = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualiza factores de balance (alturas)
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

Nodo* ArbolAVL::rotarDerecha(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->izq;
    Nodo* temp_der = nuevaRaiz->der;

    // Realiza la rotación
    nuevaRaiz->der = nodo;
    nodo->izq = temp_der;

    // Actualiza los padres
    if (temp_der) temp_der->padre = nodo;
    nuevaRaiz->padre = nodo->padre;
    nodo->padre = nuevaRaiz;

    // Actualiza factores de balance (alturas)
    actualizarFactor(nodo);
    actualizarFactor(nuevaRaiz);

    return nuevaRaiz;
}

void ArbolAVL::mostrar() {
    if (!raiz) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }
    mostrarEchado(raiz, 0);
}

void ArbolAVL::mostrarEchado(Nodo* nodo, int nivel) {
    if (nodo) {
        mostrarEchado(nodo->der, nivel + 1);
        for (int i = 0; i < nivel; i++) std::cout << "    ";
        std::cout << nodo->idAsistente << " (" << nodo->zonaAcceso << ", " << nodo->horaIngreso << ", Factor: " << nodo->factor_balance << ")\n";
        mostrarEchado(nodo->izq, nivel + 1);
    }
}

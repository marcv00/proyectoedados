#include "ArbolRojoNegro.h"
#include <iostream>
#include <cstring> // Para strcmp, strncpy

// Constructor
ArbolRojoNegro::ArbolRojoNegro() {
    TNULL = new NodoRN(Acceso("", 0, 0)); // Crear un nodo nulo/sentinel
    TNULL->color = NEGRO;
    TNULL->izquierdo = nullptr;
    TNULL->derecho = nullptr;
    TNULL->padre = nullptr; // Opcional, pero buena práctica si el sentinel puede ser padre
    raiz = TNULL; // Inicialmente la raíz es el nodo nulo
}

// Destructor
ArbolRojoNegro::~ArbolRojoNegro() {
    liberarNodos(raiz);
    delete TNULL; // Liberar el nodo TNULL
}

// Función auxiliar para liberar memoria recursivamente
void ArbolRojoNegro::liberarNodos(NodoRN* nodo) {
    if (nodo != TNULL) { // Asegurarse de no eliminar TNULL recursivamente
        liberarNodos(nodo->izquierdo);
        liberarNodos(nodo->derecho);
        delete nodo;
    }
}

// Función auxiliar de reemplazo para rotaciones y eliminación
void ArbolRojoNegro::transplant(NodoRN* u, NodoRN* v) {
    if (u->padre == nullptr) {
        raiz = v;
    } else if (u == u->padre->izquierdo) {
        u->padre->izquierdo = v;
    } else {
        u->padre->derecho = v;
    }
    v->padre = u->padre;
}

// Función para encontrar el nodo con el valor mínimo en un subárbol
NodoRN* ArbolRojoNegro::minimo(NodoRN* nodo) {
    while (nodo->izquierdo != TNULL) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

void ArbolRojoNegro::insertar(const Acceso& acceso) {
    NodoRN* nuevo = new NodoRN(acceso);
    nuevo->izquierdo = TNULL; // Apuntar a TNULL en lugar de nullptr
    nuevo->derecho = TNULL;   // Idem

    NodoRN* y = nullptr;
    NodoRN* x = this->raiz; // Usar 'this->raiz' para evitar ambigüedad

    while (x != TNULL) { // Comparar con TNULL
        y = x;
        if (acceso.hora < x->acceso.hora)
            x = x->izquierdo;
        else if (acceso.hora > x->acceso.hora)
            x = x->derecho;
        else { // Misma hora, comparar por zona
            int cmp = strcmp(acceso.zona, x->acceso.zona);
            if (cmp == 0) {
                x->acceso.cantidad += acceso.cantidad;
                delete nuevo; // No necesitamos el nuevo nodo, solo actualizamos
                return;
            } else if (cmp < 0)
                x = x->izquierdo;
            else
                x = x->derecho;
        }
    }

    nuevo->padre = y;
    if (y == nullptr) {
        this->raiz = nuevo;
    } else if (acceso.hora < y->acceso.hora) {
        y->izquierdo = nuevo;
    } else if (acceso.hora > y->acceso.hora) {
        y->derecho = nuevo;
    } else { // Misma hora, comparar por zona
        int cmp = strcmp(acceso.zona, y->acceso.zona);
        if (cmp < 0)
            y->izquierdo = nuevo;
        else
            y->derecho = nuevo;
    }

    insertarFixup(nuevo);
}

// Implementación simplificada del fixup según tu descripción
void ArbolRojoNegro::insertarFixup(NodoRN* z) {
    raiz->color = NEGRO;
}


void ArbolRojoNegro::rotarIzquierda(NodoRN* x) {
    NodoRN* y = x->derecho;
    x->derecho = y->izquierdo;
    if (y->izquierdo != TNULL) {
        y->izquierdo->padre = x;
    }
    y->padre = x->padre;
    if (x->padre == nullptr) {
        this->raiz = y;
    } else if (x == x->padre->izquierdo) {
        x->padre->izquierdo = y;
    } else {
        x->padre->derecho = y;
    }
    y->izquierdo = x;
    x->padre = y;
}

void ArbolRojoNegro::rotarDerecha(NodoRN* x) {
    NodoRN* y = x->izquierdo;
    x->izquierdo = y->derecho;
    if (y->derecho != TNULL) {
        y->derecho->padre = x;
    }
    y->padre = x->padre;
    if (x->padre == nullptr) {
        this->raiz = y;
    } else if (x == x->padre->derecho) {
        x->padre->derecho = y;
    } else {
        x->padre->izquierdo = y;
    }
    y->derecho = x;
    x->padre = y;
}


// Función para contar zonas de forma recursiva
void ArbolRojoNegro::contarZonas(NodoRN* nodo, ZonaContador* zonas, int& numZonas, int maxZonas) const {
    if (nodo == TNULL) return;
    contarZonas(nodo->izquierdo, zonas, numZonas, maxZonas);

    int i;
    for (i = 0; i < numZonas; ++i) {
        if (strcmp(zonas[i].zona, nodo->acceso.zona) == 0) {
            zonas[i].cantidad += nodo->acceso.cantidad;
            break;
        }
    }
    if (i == numZonas && numZonas < maxZonas) {
        strncpy(zonas[numZonas].zona, nodo->acceso.zona, 19);
        zonas[numZonas].zona[19] = '\0';
        zonas[numZonas].cantidad = nodo->acceso.cantidad;
        ++numZonas;
    }

    contarZonas(nodo->derecho, zonas, numZonas, maxZonas);
}

void ArbolRojoNegro::zonaConMasEntradas(char* zona_resultado, int tam) const {
    const int MAX_ZONAS = 100; // Asumiendo un número máximo de zonas posibles
    ZonaContador zonas[MAX_ZONAS];
    int numZonas = 0;
    zona_resultado[0] = '\0'; // Asegurar que esté vacío inicialmente

    contarZonas(raiz, zonas, numZonas, MAX_ZONAS);

    int max_cantidad = -1; // Usar -1 para asegurar que cualquier cantidad válida sea mayor
    if (numZonas == 0) {
        strncpy(zona_resultado, "No hay accesos registrados.", tam - 1);
        zona_resultado[tam-1] = '\0';
        return;
    }

    for (int i = 0; i < numZonas; ++i) {
        if (zonas[i].cantidad > max_cantidad) {
            max_cantidad = zonas[i].cantidad;
            strncpy(zona_resultado, zonas[i].zona, tam - 1);
            zona_resultado[tam - 1] = '\0';
        }
    }
}

void ArbolRojoNegro::consultarFranja(NodoRN* nodo, int inicio, int fin, Acceso* resultado, int& num, int max_resultados) const {
    if (nodo == TNULL || num >= max_resultados) return;

    // Recorre el subárbol izquierdo si es relevante
    if (nodo->acceso.hora >= inicio) { // Potencialmente hay nodos relevantes a la izquierda
        consultarFranja(nodo->izquierdo, inicio, fin, resultado, num, max_resultados);
    }

    // Procesa el nodo actual si está dentro de la franja horaria
    if (nodo->acceso.hora >= inicio && nodo->acceso.hora <= fin && num < max_resultados) {
        resultado[num++] = nodo->acceso;
    }

    // Recorre el subárbol derecho si es relevante
    if (nodo->acceso.hora <= fin) { // Potencialmente hay nodos relevantes a la derecha
        consultarFranja(nodo->derecho, inicio, fin, resultado, num, max_resultados);
    }
}

int ArbolRojoNegro::consultarPorFranja(int inicio, int fin, Acceso* resultado, int max_resultados) const {
    int num = 0;
    consultarFranja(raiz, inicio, fin, resultado, num, max_resultados);
    return num;
}

// Función de demostración para mostrar el árbol (in-order traversal)
void ArbolRojoNegro::mostrarInOrden(NodoRN* nodo) const {
    if (nodo != TNULL) {
        mostrarInOrden(nodo->izquierdo);
        std::cout << "Zona: " << nodo->acceso.zona << ", Hora: " << nodo->acceso.hora
                  << ", Cantidad: " << nodo->acceso.cantidad
                  << (nodo->color == ROJO ? " (Rojo)" : " (Negro)") << std::endl;
        mostrarInOrden(nodo->derecho);
    }
}

void ArbolRojoNegro::mostrar() {
    if (raiz == TNULL) {
        std::cout << "El arbol Rojo-Negro esta vacio." << std::endl;
        return;
    }
    std::cout << "\n--- Contenido del Arbol Rojo-Negro (In-Order) ---\n";
    mostrarInOrden(raiz);
    std::cout << "--------------------------------------------------\n";
}

// Implementación placeholder para buscar y eliminar (si es necesario)
NodoRN* ArbolRojoNegro::buscar(const Acceso& acceso) const {
    NodoRN* current = raiz;
    while (current != TNULL) {
        if (acceso.hora < current->acceso.hora) {
            current = current->izquierdo;
        } else if (acceso.hora > current->acceso.hora) {
            current = current->derecho;
        } else {
            int cmp = strcmp(acceso.zona, current->acceso.zona);
            if (cmp == 0) {
                return current; // Encontrado
            } else if (cmp < 0) {
                current = current->izquierdo;
            } else {
                current = current->derecho;
            }
        }
    }
    return TNULL; // No encontrado
}

void ArbolRojoNegro::eliminar(const Acceso& acceso) {
    std::cout << "La funcion de eliminacion para el Arbol Rojo-Negro no esta completamente implementada." << std::endl;
}

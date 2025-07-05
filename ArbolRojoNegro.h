
#ifndef ARBOLROJONEGRO_H
#define ARBOLROJONEGRO_H

#include <cstring> // Para strncpy, strcmp
#include <string> // Para std::string si se usará en Acceso

enum Color { ROJO, NEGRO };

struct Acceso {
    char zona[20];
    int hora;
    int cantidad;

    Acceso(const char* z = "", int h = 0, int c = 1)
        : hora(h), cantidad(c) {
        std::strncpy(zona, z, 19);
        zona[19] = '\0';
    }
};

struct NodoRN {
    Acceso acceso;
    Color color;
    NodoRN* izquierdo;
    NodoRN* derecho;
    NodoRN* padre;

    NodoRN(const Acceso& a)
        : acceso(a), color(ROJO), izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}
};

struct ZonaContador {
    char zona[20];
    int cantidad;
};

class ArbolRojoNegro {
private:
    NodoRN* raiz;
    NodoRN* TNULL;

    void rotarIzquierda(NodoRN* x);
    void rotarDerecha(NodoRN* x);
    void insertarFixup(NodoRN* z);
    void transplant(NodoRN* u, NodoRN* v);
    NodoRN* minimo(NodoRN* nodo);
    void eliminarFixup(NodoRN* x);
    void eliminarNodo(NodoRN* nodo, const Acceso& acceso);
    void contarZonas(NodoRN* nodo, ZonaContador* zonas, int& numZonas, int maxZonas) const;
    void consultarFranja(NodoRN* nodo, int inicio, int fin, Acceso* resultado, int& num, int max_resultados) const;
    void mostrarInOrden(NodoRN* nodo) const;
    void liberarNodos(NodoRN* nodo);

public:
    ArbolRojoNegro();
    ~ArbolRojoNegro();
    void insertar(const Acceso&);
    // Agregamos la capacidad de buscar y posiblemente eliminar nodos por clave
    NodoRN* buscar(const Acceso& acceso) const;
    void eliminar(const Acceso& acceso);
    int consultarPorFranja(int, int, Acceso*, int) const;
    void zonaConMasEntradas(char*, int) const;
    void mostrar();
};

#endif // ARBOLROJONEGRO_H

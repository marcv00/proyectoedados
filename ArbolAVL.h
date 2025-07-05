
#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <string>
#include <algorithm>
#include "Usuario.h"

struct Nodo {
    std::string idAsistente;
    std::string zonaAcceso; // Mantener como string si la zona es 'A', 'B', etc.
    int horaIngreso;
    int factor_balance;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(std::string id, std::string zona, int hora)
        : idAsistente(id), zonaAcceso(zona), horaIngreso(hora),
          factor_balance(0), izq(nullptr), der(nullptr), padre(nullptr) {}
};

class ArbolAVL {
private:
    Nodo* raiz;

    Nodo* insertarRecursivo(Nodo* nodo, std::string id, std::string zona, int hora);
    int calcularAltura(Nodo* nodo);
    void actualizarFactor(Nodo* nodo);
    Nodo* rebalance(Nodo* nodo);
    Nodo* rotarIzquierda(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* nodo);
    void mostrarEchado(Nodo* nodo, int nivel);

public:
    ArbolAVL();
    ~ArbolAVL();
    void insertar(std::string id, std::string zona, int hora);
    void mostrar();

private:
    void liberarNodos(Nodo* nodo);
};

#endif // ARBOLAVL_H

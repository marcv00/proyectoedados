#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "Usuario.h"

class HashTable {
private:
    Usuario** hashTableArray;
    int tamanhoTabla;
    int elementosEnTabla;
    float umbralRehash = 0.7f;

    // Insertar evitando colisiones
    void insertarSinColision(int index, Usuario* valor);

    void rehash();

public:
    // Constructor
    HashTable(int size);
    // Destructor
    ~HashTable();

    // Esta metodo usara metodo privado insertarSinColision
    void insertar(const std::string& clave, Usuario* valor);

    int buscar(const std::string& dni);

    void imprimir();
    void imprimirUsuario(int i);
    bool estaLlena() const {
        return elementosEnTabla >= tamanhoTabla;
    }

};

#endif // HASHTABLE_H

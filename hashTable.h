#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

class HashTable {
private:
    int* hashTableArray;
    int tamanhoTabla;
    int elementosEnTabla;

    // Insertar evitando colisiones
    void insertarSinColision(int hashIndex, int valueToInsert);

public:
    // Constructor
    HashTable(int size);
    // Destructor
    ~HashTable();

    void insertar(const std::string& key, int value);
    void imprimir();
    bool estaLlena() const {
        return elementosEnTabla >= tamanhoTabla;
    }
};

#endif // HASHTABLE_H

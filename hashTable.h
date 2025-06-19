#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

class HashTable {
private:
    int* hashTableArray;
    int tamanhoTabla;
    int elementosEnTabla;

    // Insertar evitando colisiones
    void insertarSinColision(int index, int valor);

public:
    // Constructor
    HashTable(int size);
    // Destructor
    ~HashTable();

    // Esta metodo usara metodo privado insertarSinColision
    void insertar(const std::string& clave, int valor);

    int buscar(const std::string& dni);
    int obtenerUsuario(const std::string& dni);

    void imprimir();
    bool estaLlena() const {
        return elementosEnTabla >= tamanhoTabla;
    }

};

#endif // HASHTABLE_H

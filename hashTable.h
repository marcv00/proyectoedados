#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

struct Usuario {
    std::string dni;
    std::string nombreCompleto;
    std::string prioridad;
    char zona;
    std::string horaIngreso;
};

class HashTable {
private:
    Usuario** hashTableArray;
    int tamanhoTabla;
    int elementosEnTabla;

    // Insertar evitando colisiones
    void insertarSinColision(int index, Usuario* valor);

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

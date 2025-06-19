#include "HashTable.h"
#include <iostream>

// Al instanciarse, tamanhoTabla se define con el tamanho entregado por el usuario
// como parametro del constructor, tambien se define elementosEnTabla a 0.
HashTable::HashTable(int size) : tamanhoTabla(size), elementosEnTabla(0) {
    hashTableArray = new int[tamanhoTabla];
    for (int i = 0; i < tamanhoTabla; ++i) {
        hashTableArray[i] = -1; // -1 indica slot vacío
    }
    std::cout << "Tabla Hash creada con tamanho: " << tamanhoTabla << std::endl;
}

HashTable::~HashTable() {
    delete[] hashTableArray;
    std::cout << "Memoria de la Tabla Hash liberada." << std::endl;
}

void HashTable::insertarSinColision(int index, int valor) {
    int i = 0, indiceActual;

    do {
        indiceActual = (index + i) % tamanhoTabla;

        if (hashTableArray[indiceActual] == -1) {
            // Insertar si encuentra espacio
            hashTableArray[indiceActual] = valor;
            elementosEnTabla++;
            std::cout << "Valor " << valor << " insertado en indice: " << indiceActual << std::endl;
            break;
        } else {
            // Colisión, probar siguiente
            i++;
            std::cout << "Colision detectada en indice inicial, probando indice: " << indiceActual + 1 << std::endl;
        }
    } while (i < tamanhoTabla);

    // Si llega a este punto significa que ya se exploro toda la tabla
    if (i == tamanhoTabla) {
        std::cout << "Tabla Llena. No se pudo insertar el valor: " << valor << std::endl;
    }
}

void HashTable::insertar(const std::string& clave, int valor) {
    if (estaLlena()) {
        std::cout << "Error: Tabla hash llena, no se puede insertar." << std::endl;
        return;
    }

    int sumaDeAscii = 0;
    for (char c : clave) {
        sumaDeAscii += (int)c;
    }

    std::cout << "Clave '" << clave << "' suma ASCII: " << sumaDeAscii << std::endl;

    int index = sumaDeAscii % tamanhoTabla;
    std::cout << "Indice inicial: " << index << std::endl;

    insertarSinColision(index, valor);
}

int HashTable::buscar(const std::string& dniBuscado) {
    int sumaAscii = 0;
    for (char c : dniBuscado) {
        sumaAscii += static_cast<int>(c);
    }

    int index = sumaAscii % tamanhoTabla;
    int i = 0, indiceActual;

    while (i < tamanhoTabla) {
        indiceActual = (index + i) % tamanhoTabla;

        if (hashTableArray[indiceActual].dni == "") {
            break;
        }

        if (hashTableArray[indiceActual].dni == dniBuscado) {
            return indiceActual;
        }

        i++;
    }

    return -1;
}

int HashTable::obtenerUsuario(const std::string& dni) {
    int indice = buscar(dni);

    if (indice != -1) {
        return hashTableArray[indice];
    }

    // Usuario "inválido"
    return -1;
}

void HashTable::imprimir() {
    std::cout << "\n--- Contenido de la Tabla Hash ---\n";
    for (int i = 0; i < tamanhoTabla; ++i) {
        std::cout << "Indice " << i << ": " << hashTableArray[i] << std::endl;
    }
    std::cout << "----------------------------------\n";
}

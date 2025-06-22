#include "HashTable.h"
#include <iostream>

// Al instanciarse, tamanhoTabla se define con el tamanho entregado por el usuario
// como parametro del constructor, tambien se define elementosEnTabla a 0.
HashTable::HashTable(int size) : tamanhoTabla(size), elementosEnTabla(0) {
    hashTableArray = new Usuario*[tamanhoTabla];
    for (int i = 0; i < tamanhoTabla; ++i) {
        hashTableArray[i] = nullptr; // Se inicializara la tabla sin usuarios
    }
    std::cout << "Tabla Hash creada con tamanho: " << tamanhoTabla << std::endl;
}

HashTable::~HashTable() {
    for (int i = 0; i < tamanhoTabla; ++i) {
        delete hashTableArray[i];
    }
    delete[] hashTableArray;
    std::cout << "Memoria de la Tabla Hash liberada." << std::endl;
}

void HashTable::insertarSinColision(int index, Usuario* valor) {
    int i = 0, indiceActual;

    do {
        indiceActual = (index + i) % tamanhoTabla;

        if (hashTableArray[indiceActual] == nullptr) {
            // Insertar si encuentra espacio
            hashTableArray[indiceActual] = valor;
            elementosEnTabla++;
            std::cout << "Usuario con DNI " << valor->dni << " insertado en indice: " << indiceActual << std::endl;
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

void HashTable::insertar(const std::string& clave, Usuario* valor) {
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
        sumaAscii += (int)(c);
    }

    int index = sumaAscii % tamanhoTabla;
    int i = 0, indiceActual;

    while (i < tamanhoTabla) {
        indiceActual = (index + i) % tamanhoTabla;

        if (hashTableArray[indiceActual] == nullptr) {
            continue;
        }

        if (hashTableArray[indiceActual]->dni == dniBuscado) {
            return indiceActual;
        }

        i++;
    }

    return -1;
}


void HashTable::imprimir() {
    std::cout << "\n--- Contenido de la Tabla Hash ---\n";
    for (int i = 0; i < tamanhoTabla; ++i) {
        if (hashTableArray[i]) {
            std::cout << "Indice " << i << ": "
                      << hashTableArray[i]->dni << ", "
                      << hashTableArray[i]->nombreCompleto << ", "
                      << hashTableArray[i]->prioridad << ", "
                      << hashTableArray[i]->zona << ", "
                      << hashTableArray[i]->horaIngreso << std::endl;
        } else {
            std::cout << "Indice " << i << ": (vacio)" << std::endl;
        }
    }
    std::cout << "----------------------------------\n";
}

void HashTable::imprimirUsuario(int i){
    std::cout << "Usuario en indice " << i << ": "
                      << hashTableArray[i]->dni << ", "
                      << hashTableArray[i]->nombreCompleto << ", "
                      << hashTableArray[i]->prioridad << ", "
                      << hashTableArray[i]->zona << ", "
                      << hashTableArray[i]->horaIngreso << std::endl;
}

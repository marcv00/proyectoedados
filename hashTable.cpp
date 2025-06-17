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

void HashTable::insertarSinColision(int hashIndex, int valueToInsert) {
    int i = 0;
    int currentIndex;

    do {
        currentIndex = (hashIndex + i) % tamanhoTabla;

        if (hashTableArray[currentIndex] == -1) {
            // Slot vacío, insertar aquí
            hashTableArray[currentIndex] = valueToInsert;
            elementosEnTabla++;
            std::cout << "Valor " << valueToInsert << " insertado en indice: " << currentIndex << std::endl;
            break;
        } else {
            // Colisión, probar siguiente
            i++;
            std::cout << "Colision detectada en indice inicial, probando indice: " << currentIndex + 1 << std::endl;
        }
    } while (i < tamanhoTabla); // Asegura no salirnos del rango al probar

    if (i == tamanhoTabla) {
        std::cout << "Error: No se pudo insertar el valor " << valueToInsert << ", tabla llena o error de logica." << std::endl;
    }
}

void HashTable::insertar(const std::string& key, int value) {
    if (estaLlena()) {
        std::cout << "Error: Tabla hash llena, no se puede insertar." << std::endl;
        return;
    }

    int asciiSum = 0;
    for (char c : key) {
        asciiSum += static_cast<int>(c);
    }

    std::cout << "Clave '" << key << "' suma ASCII: " << asciiSum << std::endl;

    int initialIndex = asciiSum % tamanhoTabla;
    std::cout << "Indice inicial: " << initialIndex << std::endl;

    insertarSinColision(initialIndex, value);
}

void HashTable::imprimir() {
    std::cout << "\n--- Contenido de la Tabla Hash ---\n";
    for (int i = 0; i < tamanhoTabla; ++i) {
        std::cout << "Indice " << i << ": " << hashTableArray[i] << std::endl;
    }
    std::cout << "----------------------------------\n";
}

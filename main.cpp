#include <iostream>
#include <string>
#include <limits>
#include "HashTable.h"

int main() {
    char band;
    int tamanhoTabla;
    int valor;

    std::cout << "Ingrese el tamaño de la tabla hash: ";
    std::cin >> tamanhoTabla;

    // Creamos un objeto de nuestra clase HashTable
    HashTable myHashTable(tamanhoTabla);

    do {
        // Limpiamos el buffer de entrada antes de leer el string
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Pedir clave
        std::string clave;
        std::cout << "Ingrese la clave: ";
        std::getline(std::cin, clave);

        // Pedir valor
        std::cout << "Ingrese el valor: ";
        std::cin >> valor;

        // Insertamos en nuestra tabla hash
        myHashTable.insertar(clave, valor);

        // Mostramos la tabla
        myHashTable.imprimir();

        std::cout << "¿Desea ingresar otra clave (s/n)? ";
        std::cin >> band;

    } while (band == 's' && !myHashTable.estaLlena());

    // Cuando main termine, el destructor de Tabla hash se dispara automaticamente
    return 0;
}

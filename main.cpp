#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "HashTable.h"

int main() {
    HashTable tablaUsuarios(5000); // inicializamos la tabla con 5000 espacios

    std::ifstream archivo("data/usuarios.txt"); // abrimos el archivo txt
    std::string linea;
    int contador = 0;

    while (std::getline(archivo, linea) && contador < 5) { // solo leemos las primeras 5 lineas
        std::stringstream ss(linea);
        std::string dni, nombre, prioridad, zonaStr, hora;
        std::getline(ss, dni, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, prioridad, ',');
        std::getline(ss, zonaStr, ',');
        std::getline(ss, hora, ',');

        Usuario* user = new Usuario;
        user->dni = dni;
        user->nombreCompleto = nombre;
        user->prioridad = prioridad;
        user->zona = zonaStr[0];
        user->horaIngreso = hora;

        tablaUsuarios.insertar(user->dni, user);
        contador++;
    }

    std::string dniABuscar = "78804794"; // uno de los primeros dnis en el archivo
    int indice = tablaUsuarios.buscar(dniABuscar);

    if (indice != -1) {
        std::cout << "Dni encontrado!" << std::endl;
        tablaUsuarios.imprimirUsuario(indice);
    } else {
        std::cout << "Usuario con DNI " << dniABuscar << " no encontrado." << std::endl;
    }

    return 0;
}

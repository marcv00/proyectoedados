#include <iostream>
#include <fstream>
#include <sstream>
#include <string> // Necesario para std::string, std::getline, std::stoi, std::to_string

// Incluye tus archivos de cabecera personalizados
#include "Usuario.h" // Se incluyó aquí para usar la estructura Usuario
#include "ArbolAVL.h"
#include "ArbolRojoNegro.h"
#include "Heap.h"
#include "HashTable.h"

int main() {
    // Instancias de las estructuras de datos
    ArbolAVL arbolAVL;
    ArbolRojoNegro arbolRN;
    Usuario heap[5000]; // Array para el Heap
    int n = 0; // Tamaño actual del Heap
    HashTable tablaUsuarios(5000); // Tabla Hash con tamaño inicial

    std::ifstream archivo("data/usuarios.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir usuarios.txt. Asegurate que este en la ruta correcta (e.g., MiProyectoControlAccesos/data/usuarios.txt).\n";
        return 1; // Termina el programa con error
    }

    std::string linea;
    int contador = 0;

    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dni, nombre, prioridad, zonaStr, horaCompleta;

        // Parsear cada campo separado por coma
        std::getline(ss, dni, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, prioridad, ',');
        std::getline(ss, zonaStr, ',');
        std::getline(ss, horaCompleta, ',');

        // Extraer la hora (parte entera antes de ':')
        int horaIngreso = 0;
        try {
            horaIngreso = std::stoi(horaCompleta.substr(0, 2));
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Advertencia: Hora invalida para DNI " << dni << ". Se usara 0. " << ia.what() << '\n';
        } catch (const std::out_of_range& oor) {
            std::cerr << "Advertencia: Hora fuera de rango para DNI " << dni << ". Se usara 0. " << oor.what() << '\n';
        }

        // 1. Insertar en el Árbol AVL
        // El AVL usa id, zona (física), hora.
        // Asegúrate de que zonaStr sea la zona física (ej. 'A', 'B'), no la prioridad.
        arbolAVL.insertar(dni, zonaStr, horaIngreso);

        // 2. Insertar en el Árbol Rojo-Negro
        // El RN usa zona (física) y hora.
        arbolRN.insertar(Acceso(zonaStr.c_str(), horaIngreso));

        // 3. Insertar en el Heap
        Usuario u;
        u.dni = dni;
        u.nombreCompleto = nombre;
        u.prioridad = prioridad;
        u.zona = zonaStr[0]; // Tomar el primer carácter de la zona como char
        u.horaIngreso = horaCompleta; // Guardar la hora completa como string
        insertarHeap(heap, n, u);

        // 4. Insertar en la Tabla Hash
        // Se crea un nuevo Usuario dinámicamente para la tabla hash
        Usuario* userHash = new Usuario(u.dni, u.nombreCompleto, u.prioridad, u.zona, u.horaIngreso);
        tablaUsuarios.insertar(dni, userHash);

        contador++;
    }
    archivo.close();

    std::cout << "Carga completa de " << contador << " usuarios." << std::endl;

    // --- Mostrar algunos resultados de prueba ---

    // 1. Mostrar los 5 con mayor prioridad del Heap
    std::cout << "\n=== Proximos 5 accesos (por prioridad) ===\n";
    mostrarTop5(heap, n);

    // 2. Consultar la zona con más entradas del Árbol Rojo-Negro
    char zonaMax[20];
    arbolRN.zonaConMasEntradas(zonaMax, sizeof(zonaMax));
    std::cout << "\nZona con mas accesos: " << zonaMax << std::endl;

    // 3. Mostrar el árbol AVL (volcado en forma 'echada')
    std::cout << "\n=== Contenido del Arbol AVL ===\n";
    arbolAVL.mostrar();

    // 4. Mostrar la Tabla Hash completa
    std::cout << "\n=== Contenido de la Tabla Hash ===\n";
    tablaUsuarios.imprimir();

    // Ejemplo de búsqueda en la Tabla Hash
    std::string dniBuscar = "78804794"; // Ejemplo de DNI del usuarios.txt
    int indiceEncontrado = tablaUsuarios.buscar(dniBuscar);
    if (indiceEncontrado != -1) {
        std::cout << "\nUsuario con DNI " << dniBuscar << " encontrado en la Tabla Hash:\n";
        tablaUsuarios.imprimirUsuario(indiceEncontrado);
    } else {
        std::cout << "\nUsuario con DNI " << dniBuscar << " NO encontrado en la Tabla Hash.\n";
    }

    // Ejemplo de consulta por franja horaria en Arbol Rojo-Negro
    const int MAX_RESULTADOS_FRANJA = 10;
    Acceso resultadosFranja[MAX_RESULTADOS_FRANJA];
    int numResultados = arbolRN.consultarPorFranja(12, 14, resultadosFranja, MAX_RESULTADOS_FRANJA); // Por ejemplo, entre 12:00 y 14:00
    std::cout << "\n=== Accesos en la franja horaria de 12:00 a 14:00 (" << numResultados << " encontrados) ===\n";
    for (int i = 0; i < numResultados; ++i) {
        std::cout << "  Zona: " << resultadosFranja[i].zona << ", Hora: " << resultadosFranja[i].hora
                  << ", Cantidad: " << resultadosFranja[i].cantidad << std::endl;
    }
    std::cout << "------------------------------------------------------------------\n";


    return 0;
}

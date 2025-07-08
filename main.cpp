#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>

// Incluye tus archivos de cabecera personalizados
#include "Usuario.h"
#include "ArbolAVL.h"
#include "ArbolRojoNegro.h"
#include "Heap.h"
#include "HashTable.h"

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Instancias de las estructuras de datos
    ArbolAVL arbolAVL;
    ArbolRojoNegro arbolRN;
    Usuario heap[5000];
    int n_heap = 0;
    HashTable tablaUsuarios(5000); // Tabla Hash con tamaño inicial

    // --- Carga de datos desde usuarios.txt ---
    std::cout << "Cargando datos desde usuarios.txt...\n";
    std::ifstream archivo("data/usuarios.txt");

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir usuarios.txt. Asegurate que este en la ruta correcta (e.g., MiProyectoControlAcceso/data/usuarios.txt).\n";
        return 1;
    }

    std::string linea;
    int contador_usuarios = 0;

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dni, nombre, prioridad, zonaStr, horaCompleta;

        std::getline(ss, dni, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, prioridad, ',');
        std::getline(ss, zonaStr, ',');
        std::getline(ss, horaCompleta, ',');

        int horaIngreso = 0;
        try {
            horaIngreso = std::stoi(horaCompleta.substr(0, 2));
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Advertencia: Hora invalida para DNI " << dni << ". Se usara 0. " << ia.what() << '\n';
        } catch (const std::out_of_range& oor) {
            std::cerr << "Advertencia: Hora fuera de rango para DNI " << dni << ". Se usara 0. " << oor.what() << '\n';
        }

        arbolAVL.insertar(dni, zonaStr, horaIngreso);
        arbolRN.insertar(Acceso(zonaStr.c_str(), horaIngreso));

        Usuario u;
        u.dni = dni;
        u.nombreCompleto = nombre;
        u.prioridad = prioridad;
        u.zona = zonaStr[0];
        u.horaIngreso = horaCompleta;
        insertarHeap(heap, n_heap, u); // Usamos n_heap aquí

        Usuario* userHash = new Usuario(u.dni, u.nombreCompleto, u.prioridad, u.zona, u.horaIngreso);
        tablaUsuarios.insertar(dni, userHash);

        contador_usuarios++;
    }
    archivo.close();
    std::cout << "Carga completa de " << contador_usuarios << " usuarios.\n\n";
        // --- Encabezado decorado ---
        std::cout << R"(

 ________       ________      ________      ________      ________   _______       _____ ______
|\   ____\     |\   ___ \    |\   ____\    |\   __  \    |\   __  \ |\  ___ \     |\   _ \  _   \
\ \  \___|_    \ \  \_|\ \   \ \  \___|    \ \  \|\  \   \ \  \|\  \\ \   __/|    \ \  \\\__\ \  \
 \ \_____  \    \ \  \ \\ \   \ \  \        \ \   __  \   \ \   ____\\ \  \_|/__   \ \  \\|__| \  \
  \|____|\  \  __\ \  \_\\ \ __\ \  \____  __\ \  \ \  \ __\ \  \_____\ \  \_|\ \ __\ \  \    \ \  \
    ____\_\  \|\__\ \_______|\__\ \_______|\__\ \__\ \__|\__\ \__\ |\__\ \_______|\__\ \__\    \ \__\
   |\_________\|__|\|_______\|__|\|_______\|__|\|__|\|__\|__|\|__| \|__|\|_______\|__|\|__|     \|__|
   \|_________|

 ____________________________________________________________________________                                                 |
|                                                                            |
|         Sistema de Control de Accesos para Eventos Masivos                 |
|                          Grupo 4 - EDAII                                   |
|____________________________________________________________________________|

    )" << std::endl;


    // --- Menú interactivo por consola ---
    int opcion;
    do {
        std::cout << "--- Sistema de Control de Accesos ---\n";
        std::cout << "1. Mostrar proximo 5 accesos (por prioridad - Heap)\n";
        std::cout << "2. Consultar zona con mas entradas (Arbol Rojo-Negro)\n";
        std::cout << "3. Mostrar arbol AVL (vista 'echada')\n";
        std::cout << "4. Mostrar tabla Hash completa\n";
        std::cout << "5. Buscar usuario por DNI (Tabla Hash)\n";
        std::cout << "6. Consultar accesos por franja horaria (Arbol Rojo-Negro)\n";
        std::cout << "0. Salir\n";
        std::cout << "Ingrese su opcion: ";

        std::cin >> opcion;

        // Validar entrada numérica
        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero.\n";
            std::cin.clear(); // Limpiar el estado de error
            limpiarBuffer(); // Descartar la entrada incorrecta
            continue; // Volver a mostrar el menú
        }
        limpiarBuffer(); // Limpiar el buffer después de leer la opción

        switch (opcion) {
            case 1:
                mostrarTop5(heap, n_heap);
                break;
            case 2: {
                char zonaMax[20];
                arbolRN.zonaConMasEntradas(zonaMax, sizeof(zonaMax));
                std::cout << "\nZona con mas accesos: " << zonaMax << std::endl;
                break;
            }
            case 3:
                std::cout << "\n=== Contenido del Arbol AVL ===\n";
                arbolAVL.mostrar();
                break;
            case 4:
                std::cout << "\n=== Contenido de la Tabla Hash ===\n";
                tablaUsuarios.imprimir();
                break;
            case 5: {
                std::string dniBuscar;
                std::cout << "Ingrese el DNI a buscar: ";
                std::getline(std::cin, dniBuscar); // Leer el DNI completo

                int indiceEncontrado = tablaUsuarios.buscar(dniBuscar);
                if (indiceEncontrado != -1) {
                    std::cout << "Usuario con DNI " << dniBuscar << " encontrado:\n";
                    tablaUsuarios.imprimirUsuario(indiceEncontrado);
                } else {
                    std::cout << "Usuario con DNI " << dniBuscar << " NO encontrado.\n";
                }
                break;
            }
            case 6: {
                int inicioHora, finHora;
                std::cout << "Ingrese la hora de inicio de la franja (0-23): ";
                std::cin >> inicioHora;
                if (std::cin.fail() || inicioHora < 0 || inicioHora > 23) {
                    std::cout << "Hora de inicio invalida.\n";
                    std::cin.clear(); limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                std::cout << "Ingrese la hora de fin de la franja (0-23): ";
                std::cin >> finHora;
                if (std::cin.fail() || finHora < 0 || finHora > 23) {
                    std::cout << "Hora de fin invalida.\n";
                    std::cin.clear(); limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                const int MAX_RESULTADOS_FRANJA = 1000; // Puede ser necesario ajustar si hay muchos resultados
                Acceso resultadosFranja[MAX_RESULTADOS_FRANJA];
                int numResultados = arbolRN.consultarPorFranja(inicioHora, finHora, resultadosFranja, MAX_RESULTADOS_FRANJA);

                std::cout << "\n=== Accesos en la franja horaria de " << inicioHora << ":00 a " << finHora << ":00 (" << numResultados << " encontrados) ===\n";
                if (numResultados == 0) {
                    std::cout << "No se encontraron accesos en esta franja horaria.\n";
                } else {
                    for (int i = 0; i < numResultados; ++i) {
                        std::cout << "  Zona: " << resultadosFranja[i].zona << ", Hora: " << resultadosFranja[i].hora
                                  << ", Cantidad: " << resultadosFranja[i].cantidad << std::endl;
                    }
                }
                std::cout << "------------------------------------------------------------------\n";
                break;
            }
            case 0:
                std::cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                break;
        }
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get(); // Espera a que el usuario presione Enter
        std::cout << "\n"; // Salto de línea para mejor visualización
    } while (opcion != 0);

    return 0;
}

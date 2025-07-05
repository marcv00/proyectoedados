#ifndef USUARIO_H
#define USUARIO_H

#include <string>

// Definición global de la estructura Usuario
struct Usuario {
    std::string dni;
    std::string nombreCompleto;
    std::string prioridad;
    char zona; // Cambiado a char para representar la zona (e.g., 'A', 'B')
    std::string horaIngreso;

    // Constructor por defecto
    Usuario() : dni(""), nombreCompleto(""), prioridad(""), zona('\0'), horaIngreso("") {}

    // Constructor con parámetros
    Usuario(std::string d, std::string n, std::string p, char z, std::string h)
        : dni(d), nombreCompleto(n), prioridad(p), zona(z), horaIngreso(h) {}
};

#endif // USUARIO_H

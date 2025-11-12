#include "Tablero.hpp"
#include <iostream>

Tablero::Tablero(std::string tipoColor) {
    if (tipoColor == "clasico") {
        colorClaro = "\033[47m";
        colorOscuro = "\033[40m";
    } else if (tipoColor == "rosa") {
        colorClaro = "\033[105m";
        colorOscuro = "\033[45m";
    } else if (tipoColor == "azul") {
        colorClaro = "\033[104m";
        colorOscuro = "\033[44m";
    } else if (tipoColor == "verde") {
        colorClaro = "\033[102m";
        colorOscuro = "\033[42m";
    } else if (tipoColor == "morado") {
        colorClaro = "\033[95m";
        colorOscuro = "\033[35m";
    }
    inicializar();
}


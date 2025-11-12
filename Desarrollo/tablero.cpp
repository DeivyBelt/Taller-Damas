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

void Tablero::inicializar() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            casillas[i][j] = nullptr;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1){
                casillas[i][j] = new FichaSimple(i, j, 1, 'o', "\033[31m");
            }
        }
    }
    for (int i = 6; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1){
                casillas[i][j] = new FichaSimple(i, j, 2, 'x', "\033[37m");
            }
        }
    }
}

void Tablero::mostrar() {
    std::cout << "\n    ";
        for (int j = 0; j < 10; j++) {
        std::cout << " " << j << " ";
    }std::cout << "\n";
    
    for (int i = 0; i < 10; i++) {
        std::cout << " " << i << "  ";
        
        for (int j = 0; j < 10; j++)
            if ((i + j) % 2 == 0){
                std::cout << colorClaro << "   ";}
            else
                {std::cout << colorOscuro << "   ";}
        
            if (casillas[i][j] != nullptr) {
                std::cout << "\033[0m";
                casillas[i][j]->mostrar();
            } else {
                std::cout << "\033[0m";
            }
        }
        std::cout << "\033[0m\n";
    }
    std::cout << "\n";
}

bool Tablero::moverFicha(int filaOrigen, int colOrigen, int filaDestino, int colDestino) {
    if (casillas[filaOrigen][colOrigen] == nullptr)
        return false;
    Ficha* ficha = casillas[filaOrigen][colOrigen];
    if (ficha->mover(filaDestino, colDestino)) {
        casillas[filaDestino][colDestino] = ficha;
        casillas[filaOrigen][colOrigen] = nullptr;
        return true;
    }
    return false;
}

void Tablero::limpiar() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }
    }
}

Tablero::~Tablero() {
    limpiar();
}

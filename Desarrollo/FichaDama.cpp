#include "FichaDama.hpp"
#include <cmath>
#include <iostream>

FichaDama::FichaDama(int f, int c, int j, char s, std::string cor)
    : Ficha(f, c, j, s, cor) { 
        coronoDama = true; 
    }

bool FichaDama::mover(int nuevaFila, int nuevaColumna) {
    int difFila = std::abs(nuevaFila - fila);
    int difColumna = std::abs(nuevaColumna - columna);
    if (difFila == difColumna && difFila > 0) {
    fila = nuevaFila;
    columna = nuevaColumna;
    return true;
    }
    return false;
}

bool FichaDama::hayCaptura() {
    return false; 
}

bool FichaDama::puedeCapturarHacia(int filaDestino, int colDestino, int& filaCap, int& colCap) {
    int difFila = filaDestino - fila;
    int difColumna = colDestino - columna;

    if (abs(difFila) != abs(difColumna) || difFila == 0) {
        return false;
    }

    int dirFila = (difFila > 0) ? 1 : -1;
    int dirCol = (difColumna > 0) ? 1 : -1;

    filaCap = fila + dirFila;
    colCap = columna + dirCol;

    return true;    
}





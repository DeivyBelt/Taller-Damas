#include "FichaDama.hpp"
#include <cmath>
#include <iostream>

FichaDama::FichaDama(int f, int c, int j, char s, std::string col)
    : Ficha(f, c, j, s, col) { esDama = true; }

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



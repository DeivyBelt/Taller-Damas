#include "FichaSimple.hpp"
#include <iostream>
#include <cmath>

FichaSimple::FichaSimple(int f, int c, int j, char s, std::string cor)
    : Ficha(f, c, j, s, cor) {}

bool FichaSimple::mover(int nuevaFila, int nuevaColumna) {
    int difFila = nuevaFila - fila;
    int difColumna = nuevaColumna - columna;
    if (jugador == 1) {
        if (difFila == 1 && std::abs(difColumna) == 1) {
            fila = nuevaFila;
            columna = nuevaColumna;
            return true;
        }
    }

#include "FichaSimple.hpp"
#include <iostream>
#include <cmath>

FichaSimple::FichaSimple(int f, int c, int j, char s, std::string cor)
    : Ficha(f, c, j, s, cor) {}

bool FichaSimple::mover(int nuevaFila, int nuevaColumna) {
    int difFila = nuevaFila - fila;
    int difColumna = nuevaColumna - columna;
    
    if (abs(difFila)==1 && abs (difColumna)== 1) {
        if (jugador==1 && difFila > 0) {
            fila = nuevaFila;
            columna = nuevaColumna;
            return true;
        }

    else if (jugador == 2 && difFila < 0) {
            fila = nuevaFila;
            columna = nuevaColumna;
            return true;
        }
    }
    return false;
}

bool FichaSimple::hayCaptura() {
    return false;
}
bool FichaSimple::puedeCapturarHacia(int filaDestino, int colDestino, int& filaCap, int& colCap){
    int difFila=filaDestino-fila;
    int difColumna=colDestino-columna;

    if (abs(difFila)==2&&abs(difColumna)==2){
        filaCap=fila+difFila/2;
        colCap=columna+difColumna/2;

        if (jugador==1&& difFila>0)return true;
        if (jugador==2 && difFila<0)return true;
    }
    return false;
}
        

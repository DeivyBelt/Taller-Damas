#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <iostream>
#include <vector>
#include "Ficha.hpp"
#include "FichaSimple.hpp"
#include "FichaDama.hpp"

class tablero{
private:
    Ficha* casillas[10][10]; 
    std::string colorClaro;
    std::string colorOscuro;

public:
    Tablero(std::string tipoColor = "clasico");

    void inicializar();
    void mostrar();
    bool moverFicha(int filaOrigen, int colOrigen, int filaDestino, int colDestino);
    void limpiar();

    Tablero();
};

#endif

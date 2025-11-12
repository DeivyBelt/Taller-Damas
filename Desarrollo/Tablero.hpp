#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <iostream>
#include <vector>
#include "Ficha.hpp"
#include "FichaSimple.hpp"
#include "FichaDama.hpp"

class Tablero{
private:
    Ficha* casillas[10][10]; 
    std::string colorClaro;
    std::string colorOscuro;

public:
    Tablero(std::string tipoColor = "clasico");
    ~Tablero();

    void inicializar();
    void mostrar();
    bool moverFicha(int filaOrigen, int colOrigen, int filaDestino, int colDestino);
    void limpiar();

    bool posicionValida(int fila, int col) const;
    bool casillaVacia(int fila, int col) const;
    int propietarioDe(int fila, int col) const;
    int contarPiezas(int jugador) const;
    bool tieneMovimientos(int jugador) const;
    bool existeCapturaObligatoria(int jugador) const;

    Ficha* obtenerFicha(int fila, int col) const;
};

#endif

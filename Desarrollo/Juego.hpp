#ifndef JUEGO_HPP
#define JUEGO_HPP
#include "Tablero.hpp"
#include <iostream>

class Juego {
private:
    Tablero* tablero;       
    int turno;              
    bool partidaActiva;  
    std::string nombreJugador1; 
    std::string nombreJugador2; 
    std::string ultimoMovimiento; 

    void mostrarMenu();
    void mostrarReglas();
    void cambiarTurno();
    bool verificarVictoria();
    void limpiarPantalla(); 
    void delaySimple(int milisegundos);

public:
   Juego();
   ~Juego();

void iniciar(); 
void iniciarPartida();
void jugarTurno();

void setNombres(std::string n1, std::string n2); 
void setUltimoMovimiento(std::string mov);  
}
endif

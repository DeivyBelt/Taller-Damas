#ifndef JUEGO_HPP
#define JUEGO_HPP
#include "Tablero.hpp"
#include <iostream>

class Juego {

    Tablero* tablero;       
    int turno;              
    bool partidaEnCurso;     

    void mostrarMenu();
    void mostrarReglas();
    void cambiarTurno();
    bool verificarVictoria();

   Juego();
   Juego();

void iniciar(); 
void iniciarPartida()
void jugarTurno()
}
endif

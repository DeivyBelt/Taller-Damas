#include "Ficha.hpp"
#include <iostream>
using namespace std;

Ficha::Ficha(int f, int c, int j, char s, string cor){
  fila=f;
  columna=c;
  jugador=j;
  simbolo=s;
  color=cor;
  coronoDama=false;
}

int Ficha::getFila() const {
  return fila;
}
int Ficha::getColumna() const {
  return columna;
}
bool Ficha::getCoronoDama() const {
  return coronoDama;
}
int Ficha::getJugador() const {
  return jugador;
}
string Ficha::getColor() const {
  return color;
}
char Ficha::getSimbolo() const {
  return simbolo;
}

void Ficha::setPosicion(int nuevaFila, int nuevaColumna){
  fila=nuevaFila;
  columna=nuevaColumna;
}
void Ficha::coronar(){
  coronoDama=true;
  simbolo = 'D';
}
void Ficha::setColor(string nuevoColor){
  color=nuevoColor;  
}

void Ficha::mostrar(){
  cout << color << simbolo;
}

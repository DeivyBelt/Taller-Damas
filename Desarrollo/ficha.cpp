#include "ficha.hpp"
#include <iostream>
using namespace std;

ficha::ficha(int f, int c, int j, char s, std::string cor){
  fila=f;
  columna=c;
  jugador=j
  simbolo=s
  color=cor
  coronoDama=false;
}

int ficha::getfila() const {return fila;}
int ficha::getcolumna() const; {return columna;}
bool ficha::getcoronoDama() const; {return coronoDama;}
int ficha::getjugador() const; {return jugador;}
string ficha::getcolor() const; {return color;}
char ficha::getsimbolo() const; {return simbolo;}

void ficha::setposicion(int nuevafila, int nuevacolumna){
  fila=nuevafila;
  columna=nuevacolumna;
}
void coronar(){
  coronoDama=true;
}

void setcolor(std::string nuevocolor){
  color=nuevocolor;
}

void mostrar(){
  cout<<color<<simbolo<<"\033[0m";
}

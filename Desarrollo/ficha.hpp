#ifdef FICHA_HPP
#define FICHA_HPP

#include <string>

class ficha {
int fila; 
int columna; 
bool coronoDama; 
int jugador; 
std::string color; 
char simbolo;

ficha(int fila=0, int columna=0, int jugador=0, char simbolo= "o", std::string color="\033[37m");

virtual bool mover (int nuevafila, int nuevacolumna)=0
virtual bool hayCaptura ()=0

int fila() const;
int columna() const;
bool coronoDama() const;
int jugador() const;
std::string color() const;
char simbolo() const;

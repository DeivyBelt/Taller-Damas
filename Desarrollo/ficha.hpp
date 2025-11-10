#ifndef FICHA_HPP
#define FICHA_HPP

#include <string>

class ficha {
protected:
int fila; 
int columna; 
bool coronoDama; 
int jugador; 
std::string color; 
char simbolo;

public:
ficha(int f=0, int c=0, int j=0, char s= 'o', std::string cor="\033[37m");

virtual bool mover (int nuevafila, int nuevacolumna)=0
virtual bool hayCaptura ()=0

int getfila() const;
int getcolumna() const;
bool getcoronoDama() const;
int getjugador() const;
std::string getcolor() const;
char getsimbolo() const;

void setposicion(int nuevafila, int nuevacolumna);
void setcolor(std::string nuevocolor);
void coronar();
void mostrar();
};
#endif

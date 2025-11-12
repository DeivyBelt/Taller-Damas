#ifndef FICHA_HPP
#define FICHA_HPP

#include <string>

class Ficha {
protected:
  int fila; 
  int columna; 
  bool coronoDama; 
  int jugador; 
  std::string color; 
  char simbolo;
  
public:
  Ficha(int f=0, int c=0, int j=0, char s= 'o', std::string cor="\033[37m");
  virtual ~Ficha() = default;
virtual bool mover (int nuevaFila, int nuevaColumna)=0;
virtual bool hayCaptura ()=0;

int getFila() const;
int getColumna() const;
bool getCoronoDama() const;
int getJugador() const;
std::string getColor() const;
char getSimbolo() const;

void setPosicion(int nuevafila, int nuevacolumna);
void setColor(std::string nuevocolor);
void coronar();
void mostrar();
};
#endif

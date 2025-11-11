#ifndef DAMA_HPP
#define DAMA_HPP
#include "ficha.hpp"

class Dama:ficha {
public:  
  Dama(int f=0, int c=0, int j=0, string col="\033[");

bool mover(int nuevafila, int nuevacolumna)
bool haycaptura;
};


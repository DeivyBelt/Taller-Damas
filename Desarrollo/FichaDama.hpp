#ifndef FICHADAMA_HPP
#define FICHADAMA_HPP
#include "Ficha.hpp"

class FichaDama:public Ficha {
public:  
  FichaDama(int f=0, int c=0, int j=0, char s= 'D' std::string cor="\033[36m");

bool mover(int nuevafila, int nuevacolumna) override;
bool haycaptura() override;
};
#endif



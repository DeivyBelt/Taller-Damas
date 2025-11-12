#ifndef FICHASIMPLE_HPP
#define FICHASIMPLE_HPP
#include "Ficha.hpp"

class FichaSimple:public Ficha {
public:
  FichaSimple(int f=0, int c=0, int j=0, char s= 'o', std::string cor="\033[37m");

bool mover (int nuevaFila, int nuevaColumna) override;
bool hayCaptura ()override;
bool puedeCapturarHacia(int filaDestino, int colDestino, int& filaCap, int& colCap);
};
#endif



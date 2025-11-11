#ifndef FICHASIMPLE_HPP
#define FICHASIMPLE_HPP

#include "ficha.hpp"

class fichaSimple:public ficha {
public:
fichaSimple(int f=0, int c=0, int j=0, char s= 'o', std::string cor="\033[37m");

bool mover (int nuevafila, int nuevacolumna);
bool hayCaptura ();
};
#endif



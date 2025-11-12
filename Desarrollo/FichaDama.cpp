#include "FichaDama.hpp"
#include <cmath>
#include <iostream>

FichaDama::FichaDama(int f, int c, int j, char s, std::string col)
    : Ficha(f, c, j, s, col) { esDama = true; }


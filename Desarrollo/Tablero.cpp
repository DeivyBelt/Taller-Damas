#include "Tablero.hpp"
#include <iostream>

Tablero::Tablero(std::string tipoColor) {
    if (tipoColor == "clasico") {
        colorClaro = "\033[107m";       
        colorOscuro = "\033[40m";       
    } else if (tipoColor == "rosa") {
        colorClaro = "\033[48;5;218m";  
        colorOscuro = "\033[48;5;175m"; 
    } else if (tipoColor == "azul") {
        colorClaro = "\033[48;5;153m";  
        colorOscuro = "\033[48;5;110m"; 
    } else if (tipoColor == "verde") {
        colorClaro = "\033[48;5;157m";  
        colorOscuro = "\033[48;5;114m"; 
    } else if (tipoColor == "morado") {
        colorClaro = "\033[48;5;183m";  
        colorOscuro = "\033[48;5;141m"; 
    }
    nombreJugador1 = "Jugador 1";  
    nombreJugador2 = "Jugador 2";
    inicializar();  
}

void Tablero::inicializar() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            casillas[i][j] = nullptr; 
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1) {
                casillas[i][j] = new FichaSimple(i, j, 1, 'o', "\033[31m");
            }
        }
    }
    
    for (int i = 6; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1) {
                casillas[i][j] = new FichaSimple(i, j, 2, 'x', "\033[37m");
            }
        }
    }
}

void Tablero::mostrar() {
    std::cout << "\n"; 

    std::cout << "      "; 
    for (int j = 0; j < 10; j++) {
        std::cout << " " << (j + 1) << "  "; 
    }
    std::cout << "\n";

    std::cout << "    +";
    for (int j = 0; j < 10; j++) {
        std::cout << "---+"; 
    }
    std::cout << "\n";

    for (int i = 0; i < 10; i++) {
        std::cout << " " << (i + 1) << " |"; 

        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 0)
                std::cout << colorClaro;  
            else
                std::cout << colorOscuro;  

            if (casillas[i][j] != nullptr) {
                Ficha* ficha = casillas[i][j];
                std::cout << " ";
                std::cout << ficha->getColor() << ficha->getSimbolo();
                if ((i + j) % 2 == 0)
                    std::cout << colorClaro;
                else
                    std::cout << colorOscuro;
                std::cout << " ";
            } else {
                std::cout << "   ";
            }
            std::cout << "\033[0m" << "|";
        }
        std::cout << " " << (i + 1) << "\n";
        std::cout << "    +";
        for (int j = 0; j < 10; j++) {
            std::cout << "---+";
        }
        std::cout << "\n";
    }
    std::cout << "      ";
    for (int j = 0; j < 10; j++) {
        std::cout << " " << (j + 1) << "  ";
    }
    std::cout << "\n\n";
    
    std::cout << "\033[31mo\033[0m = Jugador 1 (Rojo)   |   ";
    std::cout << "\033[37mx\033[0m = Jugador 2 (Blanco)   |   ";
    std::cout << "D = Dama\n\n";
}

bool Tablero::posicionValida(int fila, int col) const {
    return fila >= 0 && fila < 10 && col >= 0 && col < 10;
}

bool Tablero::casillaVacia(int fila, int col) const {
    return casillas[fila][col] == nullptr;
}

int Tablero::propietarioDe(int fila, int col) const {
    if (!posicionValida(fila, col) || casillas[fila][col] == nullptr)
        return 0;  // Posición inválida o vacía
    return casillas[fila][col]->getJugador();  // 1 o 2
}

Ficha* Tablero::obtenerFicha(int fila, int col) const {
    if (!posicionValida(fila, col))
        return nullptr;
    return casillas[fila][col];
}

bool Tablero::caminoDespejadoDama(int filaOrigen, int colOrigen, int filaDestino, int colDestino) const {
    int difFila = filaDestino - filaOrigen;
    int difCol = filaDestino - colOrigen;

    if (abs(difFila) != abs(difCol))
        return false;  // No es diagonal
    
    int dirFila = (difFila > 0) ? 1 : -1; 
    int dirCol = (difCol > 0) ? 1 : -1;  

    int f = filaOrigen + dirFila;
    int c = colOrigen + dirCol;
    
    while (f != filaDestino) {  
        if (casillas[f][c] != nullptr) {
            return false; 
        }
        f += dirFila; 
        c += dirCol;
    }
    
    return true;  
}

bool Tablero::intentarCaptura(int filaOrigen, int colOrigen, int filaDestino, int colDestino, int jugador) {
    if (!posicionValida(filaOrigen, colOrigen) || !posicionValida(filaDestino, colDestino))
        return false;

    if (casillas[filaOrigen][colOrigen] == nullptr)
        return false;

    if (casillas[filaOrigen][colOrigen]->getJugador() != jugador)
        return false;

    if (!casillaVacia(filaDestino, colDestino))
        return false;
    
    Ficha* ficha = casillas[filaOrigen][colOrigen];
    int filaCap = -1, colCap = -1; 
    bool puedeCapturar = false;

    FichaSimple* fichaSimple = dynamic_cast<FichaSimple*>(ficha);
    FichaDama* fichaDama = dynamic_cast<FichaDama*>(ficha);

    if (fichaSimple != nullptr) {
        puedeCapturar = fichaSimple->puedeCapturarHacia(filaDestino, colDestino, filaCap, colCap);
    } else if (fichaDama != nullptr) {
        int difFila = filaDestino - filaOrigen;
        int difCol = filaDestino - colOrigen;

        if (abs(difFila) != abs(difCol))
            return false;

        int dirFila = (difFila > 0) ? 1 : -1;
        int dirCol = (difCol > 0) ? 1 : -1;

        int f = filaOrigen + dirFila;
        int c = colOrigen + dirCol;
        int fichasEnCamino = 0;
        
        while (f != filaDestino) {
            if (casillas[f][c] != nullptr) {
                if (casillas[f][c]->getJugador() != jugador) {
                    filaCap = f;
                    colCap = c;
                    fichasEnCamino++;
                } else {
                    return false;
                }
            }
            f += dirFila;
            c += dirCol;
        }

        puedeCapturar = (fichasEnCamino == 1);
    }

    if (puedeCapturar && posicionValida(filaCap, colCap)) {
        Ficha* fichaCapturada = casillas[filaCap][colCap];
        
        if (fichaCapturada != nullptr && fichaCapturada->getJugador() != jugador) {

            delete fichaCapturada;
            casillas[filaCap][colCap] = nullptr;

            ficha->setPosicion(filaDestino, colDestino);
            casillas[filaDestino][colDestino] = ficha;
            casillas[filaOrigen][colOrigen] = nullptr;

            if (ficha->getJugador() == 1 && filaDestino == 9 && !ficha->getCoronoDama()) {
                int jug = ficha->getJugador();
                std::string col = ficha->getColor();
                delete casillas[filaDestino][colDestino];
                casillas[filaDestino][colDestino] = new FichaDama(filaDestino, colDestino, jug, 'D', col);
                std::cout << "¡¡Ficha de " << nombreJugador1 << " coronada!!\n";
            }

            else if (ficha->getJugador() == 2 && filaDestino == 0 && !ficha->getCoronoDama()) {
                int jug = ficha->getJugador();
                std::string col = ficha->getColor();
                delete casillas[filaDestino][colDestino];
                casillas[filaDestino][colDestino] = new FichaDama(filaDestino, colDestino, jug, 'D', col);
                std::cout << "¡¡Ficha de " << nombreJugador2 << " coronada!!\n";
            }
            
            return true; 
        }
    }
    
    return false; 
}

bool Tablero::moverFicha(int filaOrigen, int colOrigen, int filaDestino, int colDestino) {
    if (!posicionValida(filaOrigen, colOrigen) || !posicionValida(filaDestino, colDestino))
        return false;

    if (casillas[filaOrigen][colOrigen] == nullptr)
        return false;

    if (!casillaVacia(filaDestino, colDestino))
        return false;

    Ficha* ficha = casillas[filaOrigen][colOrigen];

    if (ficha->getCoronoDama()) {
        if (!caminoDespejadoDama(filaOrigen, colOrigen, filaDestino, colDestino)) {
            return false;
        }
    }
    
    if (ficha->mover(filaDestino, colDestino)) {
        casillas[filaDestino][colDestino] = ficha;
        casillas[filaOrigen][colOrigen] = nullptr;

        if (!ficha->getCoronoDama()) {
            if (ficha->getJugador() == 1 && filaDestino == 9) {
                int jug = ficha->getJugador();
                std::string col = ficha->getColor();
                delete casillas[filaDestino][colDestino];
                casillas[filaDestino][colDestino] = new FichaDama(filaDestino, colDestino, jug, 'D', col);
                std::cout << "¡¡Ficha de " << nombreJugador1 << " coronada!!\n";
            }
            else if (ficha->getJugador() == 2 && filaDestino == 0) {
                int jug = ficha->getJugador();
                std::string col = ficha->getColor();
                delete casillas[filaDestino][colDestino];
                casillas[filaDestino][colDestino] = new FichaDama(filaDestino, colDestino, jug, 'D', col);
                std::cout << "¡¡Ficha de " << nombreJugador2 << " coronada!!\n";
            }
        }

        return true;
    }

    return false;
}


int Tablero::contarPiezas(int jugador) const {
    int contador = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (casillas[i][j] != nullptr && casillas[i][j]->getJugador() == jugador) {
                contador++;
            }
        }
    }
    return contador;
}

bool Tablero::tieneMovimientos(int jugador) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (casillas[i][j] != nullptr && casillas[i][j]->getJugador() == jugador) {

                int direcciones[4][2] = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
                
                for (int d = 0; d < 4; d++) {
                    int nuevaFila = i + direcciones[d][0];
                    int nuevaCol = j + direcciones[d][1];
                    
                    if (posicionValida(nuevaFila, nuevaCol) && casillaVacia(nuevaFila, nuevaCol)) {

                        if (casillas[i][j]->getCoronoDama()) {
                            return true;
                        }
                        if (jugador == 1 && direcciones[d][0] > 0) return true;
                        if (jugador == 2 && direcciones[d][0] < 0) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Tablero::existeCapturaObligatoria(int jugador) const {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (casillas[i][j] != nullptr && casillas[i][j]->getJugador() == jugador) {

                int direcciones[4][2] = {{-2,-2}, {-2,2}, {2,-2}, {2,2}};
                
                for (int d = 0; d < 4; d++) {
                    int filaDestino = i + direcciones[d][0];
                    int colDestino = j + direcciones[d][1];
                    int filaCap = i + direcciones[d][0] / 2;
                    int colCap = j + direcciones[d][1] / 2;
                    
                    if (posicionValida(filaDestino, colDestino) && 
                        posicionValida(filaCap, colCap) &&
                        casillaVacia(filaDestino, colDestino) &&
                        !casillaVacia(filaCap, colCap)) {
                        
                        if (casillas[filaCap][colCap]->getJugador() != jugador) {
                            if (casillas[i][j]->getCoronoDama()) {
                                return true;
                            }
                            if (jugador == 1 && direcciones[d][0] > 0) return true;
                            if (jugador == 2 && direcciones[d][0] < 0) return true;
                        }
                    }
                }
                
                if (casillas[i][j]->getCoronoDama()) {
                    int dirs[4][2] = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
                    for (int d = 0; d < 4; d++) {
                        int f = i + dirs[d][0];
                        int c = j + dirs[d][1];
                        bool encontroEnemigo = false;
                        
                        while (posicionValida(f, c)) {
                            if (casillas[f][c] != nullptr) {
                                if (casillas[f][c]->getJugador() != jugador && !encontroEnemigo) {
                                    encontroEnemigo = true;
                                } else {
                                    break;
                                }
                            } else if (encontroEnemigo) {
                                return true;
                            }
                            f += dirs[d][0];
                            c += dirs[d][1];
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Tablero::limpiar() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }
    }
}
Tablero::~Tablero() {
    limpiar();
}

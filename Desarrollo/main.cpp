#include "Juego.hpp"
#include <iostream>

// librería para Windows
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {

    #ifdef _WIN32
        // Configuración para Windows (poder usar caracteres especiales)
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        system("chcp 65001 > nul");
    #endif

    cout << "\n";
    cout << "     ¡¡BIENVENID@ A DAMAS INTERNACIONALES!!        \n";
    cout << "\n";

    cout << "Características del juego:\n";
    cout << "  * 2 jugadores humanos\n";
    cout << "  * 20 fichas por jugador\n";
    cout << "  * La capturas obligatorias\n";
    cout << "  * Pueden haber capturas multiples en un turno\n";
    cout << "  * Coronacion automatica en damas\n";
    cout << "  * Hay 5 opciones de colores para tu tablero\n";

    cout << "Presiona la tecla Enter para comenzar...";
    cin.get();

    string nombre1, nombre2;
    cout << "\nIngresa el nombre del Jugador 1: ";
    getline(cin, nombre1);
    cout << "Ingresa el nombre del Jugador 2: ";
    getline(cin, nombre2);

    Juego juego;

    juego.setNombres(nombre1, nombre2);

    juego.iniciar();

    cout << "\n";
    cout << "Gracias por jugar, esperamos te haya gustado:)\n";
    cout << "Hecho por Sofi y Deivy\n";
    cout << "\n";
    
    return 0;
}






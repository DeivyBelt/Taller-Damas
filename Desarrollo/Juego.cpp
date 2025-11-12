#include "Juego.hpp"
#include <iostream>

Juego::Juego() {
    tablero = nullptr;
    turno = 1;
    partidaActiva = false;


void Juego::mostrarMenu() {
    cout << "\nDAMAS INTERNACIONALES\n";
    cout << "1. Iniciar partida\n";
    cout << "2. Ver reglas\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opción: ";

void Juego::mostrarReglas() {
    cout << "\nREGLAS DEL JUEGO\n";
    cout << "1. El tablero es de 10x10.\n"
    cout << "2. Cada jugador tiene 20 fichas colocadas en las casillas oscuras.\n"
    cout << "3. Solo se puede mover una ficha por turno.\n";
    cout << "4. Las fichas se mueven solo hacia adelante en diagonal a una casilla vacía.\n
    cout << "5. Si una ficha llega al otro extremo, se convierte en Dama.\n";
    cout << "6. La captura es obligatoria cuando sea posible.\n";
    cout << "7. El ganador es quien elimine todas las fichas del oponente.\n\n

void Juego::cambiarTurno() {
    turno = (turno == 1) ? 2 : 1;

void Juego::iniciar() {
    int opcion;

do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                iniciarPartida();
                break;
            case 2:
                mostrarReglas();
                break;
            case 3:
                cout << "Terminando el juego...\n";
                break;
            default:
                cout << "Opción inválida, intenta de nuevo.\n";
        }
    } while (opcion != 3);

void Juego::iniciarPartida() {
    string tipoColor;
    cout << "\nElije el color de tu tablero (clasico, rosa, azul, verde, morado): ";
    

 delete tablero;  
    tablero = new Tablero;

  partidaActiva = true;
    turno = 1;

cout << "\n¡¡Empieza el juego!!\n";
    tablero->mostrar();

while partidaActiva {
        jugarTurno();
        if (verificarVictoria());
        cambiarTurno()

cout << "\nFin de la partida\n";

void Juego::jugarTurno() {
    int fila, col, fila, col;

    cout << "\nTurno del jugador " << turno << "\n";
    cout << "Ingresa el numero de la fila y la columna en la que esta la ficha que moveras: ";
    cin >> fila >> col;
    cout << "Ingresa la fila y la columna de donde quieres mover la ficha elegida: ";
    cin >> fila >> col;

  if (tablero->propietarioDe(fila, col) ! turno) {
        cout << "Esa ficha no es de las tuyas.\n";
        return;

 bool exito = tablero.moverFicha(fila, col, fila, col);

    if (exito) {
        cout << "Movimiento hecho.\n";
    } else {
        cout << "Movimiento incorrecto, intenta de nuevo.\n";
        return; 
    }

    tablero.mostrar();
}

bool Juego::verificarVictoria {
    int pieza1 = tablero.contarPiezas(1);
    int pieza2 = tablero.contarPiezas(2);

    if (piezas1 == 0) {
        cout << "\n¡¡ El jugador 2 gana la partida!!\n";
        partidaActiva = false;
        return true;
    } else if (pieza2 == 0) {
        cout << "\n¡¡Jugador 1 gana la partida!!\n";
        partidaActiva = false;
        return true;
    }
    return false;

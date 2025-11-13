#include "Juego.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

Juego::Juego() {
    tablero = nullptr;
    turno = 1;
    partidaActiva = false;
    nombreJugador1 = "";
    nombreJugador2 = "";
    ultimoMovimiento = "Ninguno";
}

Juego::~Juego() {
    delete tablero;
}

void Juego::setNombres(std::string n1, std::string n2) {
    nombreJugador1 = n1;
    nombreJugador2 = n2;
}

void Juego::setUltimoMovimiento(std::string mov) {
    ultimoMovimiento = mov;
}

void Juego::delaySimple(int milisegundos) {
    for (int i = 0; i < milisegundos * 1000; i++) {
    }
}

//   Limpia la consola antes de mostrar nueva información del juego.
//   Usando una directiva del preprocesador #ifdef para determinar 
//   el sistema operativo donde se ejecuta el programa.
//   En Windows ejecuta el comando del sistema "cls".
//   En Linux o macOS ejecuta el comando "clear".
void Juego::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Juego::mostrarMenu() {
    limpiarPantalla();
    cout << "\nDAMAS INTERNACIONALES\n";
    cout << "1. Iniciar partida\n";
    cout << "2. Ver reglas\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
}

void Juego::mostrarReglas() {    
    limpiarPantalla();
    cout << "\nREGLAS DEL JUEGO\n\n";

    cout << "OBJETIVO:\n";
    cout << "  Capturar todas las fichas del oponente o dejarlo\n";
    cout << "  sin movimientos validos.\n\n";
    
    cout << "TABLERO:\n";
    cout << "  Tablero  es de 10x10 casillas\n";
    cout << "  Cada jugador tiene 20 fichas al inicio\n";
    cout << "  Solo se juega en las casillas oscuras\n\n";
    
    cout << "MOVIMIENTOS:\n";
    cout << "  Jugador 1 (o) le pertenecen las fichas rojas. Ojito, mueve SOLO HACIA ABAJO\n";
    cout << "  Jugador 2 (x) le pertenecen las fichas blancas. Ojito, mueve SOLO HACIA ARRIBA\n";
    cout << "  El movimiento basico es en diagonal, unicamente 1 casilla se mueve\n";
    cout << "  Solo a casillas oscuras vacias\n\n";
    
    cout << "CAPTURAS:\n";
    cout << "  Saltar sobre una ficha enemiga a casilla vacia\n";
    cout << "  La ficha enemiga se elimina del tablero\n";
    cout << "  *** LAS CAPTURAS SON OBLIGATORIAS ***\n";
    cout << "  Si puedes capturar, SI O SI lo haces\n";
    cout << "  Puedes hacer CAPTURAS MULTIPLES en un turno\n\n";
    
    cout << "CORONACION:\n";
    cout << "  Al llegar al extremo opuesto la ficha se convierte en Dama reprensentada por la letra D)\n";
    cout << "  Las damas se mueven en CUALQUIER direccion diagonal\n";
    cout << "  Las damas pueden moverse CUALQUIER distancia\n";
    cout << "  Las damas tambien capturan fichas enemigas\n\n";
    
    cout << "PARA GANAR:\n";
    cout << "  Capturar todas las fichas de tu enemigo, O\n";
    cout << "  Dejar a tu enemigo sin movimientos validos\n\n";
    
    cout << "Presiona la tecla Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Juego::cambiarTurno() {
    turno = (turno == 1) ? 2 : 1;
}

void Juego::iniciar() {
    int opcion;

    do {
        mostrarMenu();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEntrada invalida. Presiona la tecla Enter...";
            cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                iniciarPartida();
                break;
            case 2:
                mostrarReglas();
                break;
            case 3:
                cout << "Saliendo del juego:(...\n";
                break;
            default:
                cout << "Opcion invalida. Intenta otra vez.\n";
                cout << "Presiona la tecla Enter...";
                cin.get();
        }
    } while (opcion != 3);
}

void Juego::iniciarPartida() {
    int numeroColor;
    string tipoColor;

    cout << "\nElige el color del tablero:\n";
    cout << "1. Clasico\n";
    cout << "2. Rosa\n";
    cout << "3. Azul\n";
    cout << "4. Verde\n";
    cout << "5. Morado\n";
    cout << "-> ";

    if (!(cin >> numeroColor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        numeroColor = 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (numeroColor) {
        case 1: tipoColor = "clasico"; break;
        case 2: tipoColor = "rosa"; break;
        case 3: tipoColor = "azul"; break;
        case 4: tipoColor = "verde"; break;
        case 5: tipoColor = "morado"; break;
        default: tipoColor = "clasico"; break;
    }

    delete tablero; 
    tablero = new Tablero(tipoColor);

    partidaActiva = true;
    turno = 1;

    cout << "\n¡¡Inicia el juego!!\n";
    cout << "Presiona la tecla Enter para comenzar la batalla...";
    cin.get();

    while (partidaActiva) {
        limpiarPantalla();
        tablero->mostrar();

        string nombreActual = (turno == 1) ? nombreJugador1 : nombreJugador2;
        cout << "\nEs tu turno " << nombreActual << " (Jugador " << turno << ")   \n";
        cout << "Último movimiento: " << ultimoMovimiento << "\n";
        cout << "Fichas de " << nombreJugador1 << " (o): " << tablero->contarPiezas(1) << "\n";
        cout << "Fichas de " << nombreJugador2 << " (x): " << tablero->contarPiezas(2) << "\n\n";
        
        bool capturaObligatoria = tablero->existeCapturaObligatoria(turno);
        if (capturaObligatoria) {
            cout << "              *** ¡¡OJITO¡¡***\n";
            cout << "*** UNA FICHA ENEMIGA ESTA MAL PARQUEADA ***\n";
            cout << "            *** ¡¡ELIMINALA!! ***\n\n";
        }

        cout << " Opciones disponibles:\n";
        cout << " Mover/Capturar: Ingresa la fila y columna de origen, y la fila y columna de destino (cada numero separado por un espacio, sin ningun caracter)\n";
        cout << " Para abandonar la partida ingresa: s\n";
        cout << " Para reiniciar la partida ingresa: r\n";
        cout << "-> ";

        string primeraDato;

        if (!(cin >> primeraDato)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n Uy ingresaste algo invalido. Presiana la tecla Enter para intentarlo de nuevo...";
            cin.get();
            continue;
        }

        if (primeraDato == "s") {
            cout << "\nSaliendo de la partida:(...\n";
            partidaActiva = false;
            break;
        } 

        else if (primeraDato == "r") {
            cout << "\nReiniciando la partida:):...\n";
            delete tablero;
            tablero = new Tablero(tipoColor);
            turno = 1;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Presiona la tecla Enter para continuar...";
            cin.get();
            continue;
        }
        // Se usa try-catch para manejar excepciones de stoi, que puede lanzar std::invalid_argument o std::out_of_range
        // Esto es útil porque stoi es una función estándar de C++ que convierte string a int de manera eficiente
        // y permite manejar errores de entrada no numérica sin necesidad de implementar conversión manual
        // entonces en lugar de dejar que el programa termine abruptamente con una excepción no manejada 
        // el catch captura cualquier excepción y muestra un mensaje de error al usuario, pidiendo la entrada nuevamente.
        int fO;
        try {
            fO = stoi(primeraDato);
        } catch (...) {
            cout << "\n Uy ingresaste algo invalido. Presiana la tecla Enter para intentarlo de nuevo...";
            cin.get();
            continue;
        }

        int cO, fD, cD;
        if (!(cin >> cO >> fD >> cD)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n Uy ingresaste algo invalido. Presiana la tecla Enter para intentarlo de nuevo...";
            cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Se guardan las coordenadas originales para el mensaje de ultimo movimiento
        int fO_orig = fO;
        int cO_orig = cO;
        int fD_orig = fD;
        int cD_orig = cD;

        fO--;
        cO--;
        fD--;
        cD--;

        
        if (fO < 0 || fO > 9 || cO < 0 || cO > 9 ||
            fD < 0 || fD > 9 || cD < 0 || cD > 9) {
            cout << "\n Las coordenadas que ingresaste no existen en el tablero, recuerda de 1 a 10.\n";
            cout << "Presiona la tecla Enter, y esta vez ingresa bien las coordenadas...";
            cin.get();
            continue;
        }

        if (tablero->propietarioDe(fO, cO) != turno) {
            cout << "\nEyy esa ficha no es tuya o quizas ni existe jmm.\n";
            cout << "Presiona la tecla Enter...";
            cin.get();
            continue;
        }

        bool movimientoExitoso = false;

        if (tablero->intentarCaptura(fO, cO, fD, cD, turno)) {
            cout << "\n*** ¡¡ LOGRASTE LA CAPTURA !! ***\n";
            cout << " La ficha de tu enemigo ya quedo en el olvido JUAJUAJUA.\n";
            movimientoExitoso = true;
            setUltimoMovimiento((turno == 1 ? nombreJugador1 : nombreJugador2) + " capturó de (" + to_string(fO+1) + "," + to_string(cO+1) + ") a (" + to_string(fD+1) + "," + to_string(cD+1) + ")");
            delaySimple(500); 

            while (tablero->existeCapturaObligatoria(turno)) {
                Ficha* fichaActual = tablero->obtenerFicha(fD, cD);
                if (fichaActual == nullptr || fichaActual->getJugador() != turno) {
                    break; 
                }
                
                cout << "\n¡¡ Increibleee, puedes realizar OTRA CAPTURA con la misma ficha!!\n";
                cout << "Presiona la tecla Enter para continuar tu captura...";
                cin.get();
                
                limpiarPantalla();
                tablero->mostrar();
                
                cout << "       ¡¡CAPTURA MULTIPLEEE!!     \n";
                cout << "Tu ficha capturadora esta en: (" << fD+1 << ", " << cD+1 << ")\n";
                cout << "Sigue capturando desde esa posición.\n\n";
                cout << "Ingresa las coordenadas de la nueva captura:\n";
                cout << "Entonces: fila y columna de destino -> ";

                int nuevaFD, nuevaCD;
                if (!(cin >> nuevaFD >> nuevaCD)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nEntrada invalida. Fin de capturas multiples. Tuki tuki... lulu\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                nuevaFD--;
                nuevaCD--;

                if (tablero->intentarCaptura(fD, cD, nuevaFD, nuevaCD, turno)) {
                    cout << "\n¡¡ LOGRASTE LA CAPTURA MULTIPLEEE !!\n";
                    fD = nuevaFD;
                    cD = nuevaCD;
                } else {
                    cout << "\n Es una captura invalida. Fin de capturas multiples, se te acabo la guachafita:(\n";
                    break;
                }
            }
        }
        else if (capturaObligatoria) {
            cout << "\n*** ¡¡¡ERROR!!! CAPTURA OBLIGATORIA ***\n";
            cout << "Debes capturar cuando es posible, si es que quieres ganar -_-\n";
            cout << "Presiona la tecla Enter para seguir y ponte pilas ehh...";
            cin.get();
            continue;
        }
        else if (tablero->moverFicha(fO, cO, fD, cD)) {
            cout << "\nSe realizo el movimiento:)\n";
            movimientoExitoso = true;
            // Actualizar último movimiento
            setUltimoMovimiento((turno == 1 ? nombreJugador1 : nombreJugador2) + " movió de (" + to_string(fO+1) + "," + to_string(cO+1) + ") a (" + to_string(fD+1) + "," + to_string(cD+1) + ")");
            delaySimple(500); // Delay de 0.5s
        }
        else {
            cout << "\n Es un movimiento invalido...\n";
            cout << "Recuerda: las fichas normales solo se mueven en diagonal\n";
            cout << "hacia adelante (Jugador 1 abajo, Jugador 2 arriba).\n";
            cout << "Presiona la tecla Enter, haz bien los movimientos...";
            cin.get();
            continue;
        }

        if (movimientoExitoso) {
            cout << "Presiona la tecla Enter para continuar...";
            cin.get();

            if (verificarVictoria()) {
                partidaActiva = false;
                cout << "\nPresiona la tecla Enter para volver al menu...";
                cin.get();
                break;
            }

            cambiarTurno();
        }
    }
    
    cout << "\n Se acabo esta linda partida:( ¡otra, otra!\n";
}

void Juego::jugarTurno() {
    int filaO, colO, filaD, colD;

    cout << "\nEs tu turno " << (turno == 1 ? nombreJugador1 : nombreJugador2) << "\n";
    cout << "Ingresa la fila y la columna de la ficha a mover: ";
    cin >> filaO >> colO;
    cout << "Ingresa la fila y la columna de destino: ";
    cin >> filaD >> colD;

    if (tablero->propietarioDe(filaO, colO) != turno) {
        cout << "Esa ficha no es tuya, ladron de fichas.\n";
        return;
    }

    bool exito = tablero->moverFicha(filaO, colO, filaD, colD);

    if (exito) {
        cout << "Se realizo el movimiento:)\n";
    } else {
        cout << "Ingresaste un movimiento invalido, intenta de nuevo.\n";
        return;
    }

    tablero->mostrar();
}

bool Juego::verificarVictoria() {
    int piezas1 = tablero->contarPiezas(1);
    int piezas2 = tablero->contarPiezas(2);

    if (piezas1 == 0) {
        limpiarPantalla();
        cout << "             ¡¡SE TERMINO EL JUEGO!!           \n";
        cout << "¡¡" << nombreJugador2 << " GANO LA PARTIDA!!\n\n";
        cout << nombreJugador1 << " perdisteeee.\n";
        cout << "20 fichas capturadas, ganar no es lo tuyo.\n\n";
        partidaActiva = false;
        return true;
    }

    else if (piezas2 == 0) {
        limpiarPantalla();
        cout << "             ¡JUEGO TERMINADO!            \n";
        cout << "¡¡" << nombreJugador1 << " GANO LA PARTIDA!!\n\n";
        cout << nombreJugador2 << " perdisteeee.\n";
        cout << "20 fichas capturadas, ganar no es lo tuyo.\n\n";
        partidaActiva = false;
        return true;
    }

    if (!tablero->tieneMovimientos(turno) && !tablero->existeCapturaObligatoria(turno)) {
        limpiarPantalla();
        cout << "           ¡¡SE TERMINO EL JUEGO!!          \n";

        string nombreGanador = (turno == 1) ? nombreJugador2 : nombreJugador1;
        string nombrePerdedor = (turno == 1) ? nombreJugador1 : nombreJugador2;
        cout << "      ¡¡" << nombreGanador << " GANO LA PARTIDA!!\n\n";
        cout << nombrePerdedor << " no tienes para donde mover.\n";
        cout << "¡¡Victoria por BLOQUEO!!\n\n";
        partidaActiva = false;
        return true;
    }
    
    return false;
}

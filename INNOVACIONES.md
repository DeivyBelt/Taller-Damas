1. Colores personalizables del Tablero
  ¿Para qué se implementó?
Se implemento para que el juego tenga una experiencia visual personalizada y       bonita, permitiendo que el usuario elija entre 5 colores para el tema de su        tablero. Esta el tema clasico, tema rosa, tema azul, tema verde y tema morado.

   ¿Por qué se consideró necesario?
+ Por que los juego deben ser visualmente atractivos para su total disfrute.

   ¿Cómo se llevó a cabo su implementación
+ Paso 1: Modificacion del Constructor de Tablero: Se agrego un parámetro     `std::string tipoColor` al constructor de `Tablero` (en `Tablero.hpp` y `Tablero.cpp`). Este parámetro se almacena como atributo privado `std::string colorClaro` y `std::string colorOscuro`, inicializados con códigos ANSI vacíos por defecto.

+ Paso 2: Mapeo de Colores con Switch**: Dentro del constructor, un bloque `switch` basado en `tipoColor` asigna códigos ANSI específicos.

+ Paso 3: Aplicacion en Mostrar: En `Tablero::mostrar()`, se calcula el patron de ajedrez con `(i + j) % 2 == 0` para casillas claras, pares, y oscuras, impares. Antes de imprimir cada casilla, se inserta el codigo ANSI correspondiente: `cout << colorClaro` para claras, `colorOscuro` para oscuras, seguido de "\033[0m" para resetear colores al final de la línea. Esto asegura que solo las casillas se coloreen, no el texto de las fichas.

+ Paso 4: Integración en Juego: En `Juego::iniciarPartida()`, antes de crear el `Tablero`, se muestra un menú. Se lee un `int numeroColor` con validación, usando `cin.clear()` si falla, y se mapea a un `std::string` con un switch similar. Luego, `tablero = new Tablero(tipoColor);`. Para reinicios ('r'), se reutiliza el mismo `tipoColor` para consistencia.

2. Mejoras en la experiencia de usuario
+ Paso 1: Limpieza de Pantalla: Método `void Juego::limpiarPantalla()` usa `#ifdef _WIN32 system("cls"); #else system("clear"); #endif`. Llamado antes de mostrar menú, tablero o mensajes de victoria.

+ Paso 2: Información en Tiempo Real: En el bucle de `iniciarPartida`, antes de input: `cout << "Es tu turno " << nombreActual << " (Jugador " << turno << ")\nÚltimo movimiento: " << ultimoMovimiento << "\nFichas de " << nombreJugador1 << " (o): " << tablero->contarPiezas(1) << "\n...";`. `ultimoMovimiento` se actualiza en `setUltimoMovimiento` con strings descriptivos.

+ Paso 3: Comandos Extras**: En input, `if(primeraDato == "s") { partidaActiva = false; break; }` para salir. `if(primeraDato == "r") { delete tablero; tablero = new Tablero(tipoColor); turno = 1; ... }` para reiniciar.

+ Paso 4: Si `tablero->existeCapturaObligatoria(turno)`, muestra "*** ¡¡OJITO!! *** UNA FICHA ENEMIGA ESTA MAL PARQUEADA *** ¡¡ELIMINALA!! ***"

4. Validacion de entradas y manejo de errores avanzado
+ Paso 1: Validación de Entradas Numéricas**: En `iniciarPartida()`, para coordenadas, se usa `cin >> variable` en un bucle `while(true)`. Si falla (`!cin`), se llama `cin.clear()` para resetear flags de error, `cin.ignore(numeric_limits<streamsize>::max(), '\n')` para descartar buffer inválido, y se muestra mensaje como "Uy ingresaste algo invalido. Presiona Enter para intentarlo de nuevo...". Luego `cin.get()` para pausa.

+ Parseo Seguro de Strings: Para la primera entrada (fila origen o comando), se lee como `std::string primeraDato`, se intenta `stoi(primeraDato)` en `try-catch` para capturar `invalid_argument` o `out_of_range`, mostrando mensaje si falla.

+ Paso 3: Validaciones Específicas: Después de ajustar índices (fO = stoi - 1), se verifica límites: `if(fO < 0 || fO > 9 || ...) { cout << "Coordenadas no existen..."; continue; }`. Propiedad: `if(tablero->propietarioDe(fO, cO) != turno) { cout << "Esa ficha no es tuya..."; continue; }`. Reglas: Si hay captura obligatoria, bloquea movimientos simples.

+ Paso 4: Mensajes Descriptivos y Reintentos: Cada error tiene mensaje único, por ejemplo, ("Movimiento invalido..."), seguido de pausa con `cin.get()`.


5. Gestion de memoria dinamica
   
  + Paso 1: Creación Dinámica: En `Tablero::inicializar()`, se itera el arreglo 10x10 y se asigna `tableroFichas[i][j] = new FichaSimple(jugador);` para posiciones iniciales, basado en el patron de damas: filas 0-3 para jugador 1, 6-9 para jugador 2, en columnas pares/impares. Durante coronación, `new FichaDama(jugador);`

  + Paso 2: Método de Limpieza: Se creo `void Tablero::limpiar()` que itera `for(int i=0; i<10; i++) for(int j=0; j<10; j++) if(tableroFichas[i][j]) { delete tableroFichas[i][j]; tableroFichas[i][j] = nullptr; }` y usa destructores virtuales para limpieza polimórfica.
  
+ Paso 3: Destructor Automático: El destructor `Tablero::~Tablero()` llama `limpiar();`, asegurando liberación al destruir el objeto.


   
       

   

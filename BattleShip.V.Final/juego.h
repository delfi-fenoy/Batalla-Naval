#ifndef juego
#define juego

///----------Librerias----------///
#include "pila.h"
#include "cuentas.h"

///----------Constante-----------///
#define constantedeX 10
#define constantedeY 3

///----------Struct----------///
typedef struct
{
    int barco2;
    int barco3;
    int barco4;
    int barco5;
}vidaBarcos;

///----------Funcion Principal----------///
stUsuario batallaNaval(char archivoUsuarios[], stUsuario usuario); // Funcion principal



///-----------------------Pre_Partida-----------------------///

///----------Elegir Tabla----------///
void elegirCrearTabla(int dim, int tablaUsuario[dim][dim]); // Elegir como armar la tabla

///----------Crear Tabla Manualmente----------///
void crearTablaUsuario(int dim, int tablaUsuario[dim][dim]); // Crear la tabla de Manera Manual
void pedirCoordenadasBarcos(int* barcoX, int* barcoY, char* forma, int barco); //Pedir coordenadas y direccion al usuario + comprobacion de direccion
void agregarBarcos (int barco,int dim, int laTabla[dim][dim]); // Agregar Barco
void colocarBarcosAlTablero(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma); // Agrega el Barco en la tabla del Usuario

///----------Comprobaciones Agregar Barcos----------///
int comprobacionSuperposicionBarcos(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma); //Comprueba que los barcos no se superpongan entre si
int comprobacionLimiteBarcos(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma); //Comprueba que los barcos no se pasen del limite del tablero

///---------Crear Tabla Rival----------///
void crearRivalBot (int dim, int tablaRival[dim][dim]); // Crea el Tablero del Rival
void agregarBarcosRival(int barco, int dim, int tablaRival[dim][dim]); // Agrega los barcos en el tablero Rival



///-------------------------Partida-------------------------///

int partidaBatallaNaval(int dim, int tablaUsuario[dim][dim], int tablaRival[dim][dim], int *ganador); // Partida Entera

///----------Mostrar Tablero----------///
void mostrarTablaUsuario(int dim, int laTabla[dim][dim]); // Mostra Tablero del Usuario
void mostrarTablaRival(int dim, int laTabla[dim][dim]);  // Mostra Tablero del Rival

///---------Mensajes al Jugador----------///
void mensajeDisparoAcertado(); // Printf´s Por si hay impacto por parte del jugador
void mensajeDisparoFallido(); // Printf´s Por el jugador falla
void mensajeDisparoEnemigo(); // Printf´s Por si el enemigo impacta

///---------Inicializar Partida----------///
vidaBarcos inicializarBarcos(); // Inicializa la Struct que contine las "vidas" de los barcos
Pila cargarPila(Pila vida); // Inicializa la barra de Vida del jugador

///--------BarcosDestruido----------///
void barcoDestruido(int dim, vidaBarcos *barcosTotales, Pila *barraVida, int *puntaje); // Avisa sobre los barcos destruidos y suma los puntajes
void recorrerTabla(int dim, int tabla[dim][dim], vidaBarcos *barcosTotales); // Recorre toda la tabla para comprobar la vida de los barcos

///---------Disparos----------///
int disparoJugador(int dim, int tablaRival[dim][dim], int *puntaje); // Disparo del Jugador
int ataqueEnemigo(int dim, int tablaUsuario[dim][dim]); // Disparo del Rival

///---------Comprobaciones de Disparo----------///
void pedirCoordenadasDisparo(int* disparoF, int* disparoC); // Pide las coordenas de donde sera el disparo
int comprobacionDisparoLimiteTablero(int disparoF, int disparoC, int dim); // Comprueba que el disparo no esta fuera del tablero
int comprobacionDisparoSuperposicion(int disparoF, int disparoC, int dim, int laTabla[dim][dim]); // Comprueba que el disparo no sea en una zona ya impactada

///----------Comprobacion para que no se ingresen letras----------///
int esNumeroValido(char cadena[]);
int comprobacionNumeroValido(char cadena[], int flag);

///-----------------------Post_Partida-----------------------///

///---------Titulos----------///
void tituloVictoria(); // Titulo diciendo Victoria
void tituloDerrota(); // Titulo diciendo Derrota

///---------PasarPuntaje----------///
stUsuario pasarPuntaje(char archivoUsuarios[], stUsuario usuario, int puntaje, int ganador); // Pasa el Puntaje al usuario



#endif // juego

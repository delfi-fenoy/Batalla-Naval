#ifndef cuentas
#define cuentas

///----------Librerias----------///
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

///----------Constantes-----------///
#define DIM_NOM_CON 21 // Dimension de nombre de usuario y contraseña
#define TOP_JUGADORES 5 // Cantidad de jugadores en el ranking (puntuacion global)

///----------Colores-----------///
#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T     "\x1b[31m"
#define ROJO_F     "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T "\x1b[33m"
#define AMARILLO_F  "\x1b[43m"
#define AZUL_T     "\x1b[34m"
#define AZUL_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define BLANCO_T   "\x1b[37m"
#define BLANCO_F   "\x1b[47m"

///----------ESTRUCTURAS----------///
typedef struct
{
    int victorias;
    int partidasJugadas;
    int mejorPuntaje;

}stEstadisticas;

typedef struct
{
    char nombre[DIM_NOM_CON];
    char contrasenia[DIM_NOM_CON];
    stEstadisticas estadisticas;
    int estado; //1-> activo, 0-> inactivo

}stUsuario;

///----------PROTOTIPADO----------///

///Crear cuenta
void crearCuenta(char archivoUsuarios[]); //que se repita mientras flag==0
stUsuario crearNombreUsuario(char archivoUsuarios[]);
int comprobacionTotalNombre(char nomNuevo[], char archivoUsuario[]);
stUsuario crearContrasenia(char archivoUsuarios[]);
int comprobacionContrasenia(char conNueva[]);

///Iniciar sesion
stUsuario iniciarSesion(char archivoUsuarios[], int* flag);
int comprobacionIniciarSesion(char archivoUsuarios[], stUsuario* ingreso);

///Modificar usuario
stUsuario modificarUsuario(char archivoUsuarios[], stUsuario usuario); //retorna struct de usuario actualizado
void modificarNombre(char nombre[], char archivoUsuarios[]);
void modificarContrasenia(char contrasenia[]);
int buscarPosicionEnARchivo(char archivoUsuarios[], char nombreUsuario[]); //retorna la pos del arch a modificar

///Dar de baja
int darDeBaja(char archivoUsuarios[], stUsuario A);
char preguntarDarDeBaja();
void comprobacionPreguntaSiONo(char* res);
int comprobacionDarDeBaja();

///Recuperar cuenta
void recuperarCuenta(char archivoUsuarios[]);

///Info del usuario
void infoDelUsuario(stUsuario usuario);

///Otros usuarios
//Elegir opcion (buscar jugador o ver lista de jugadores) y crear arreglo dinamico
void otrosUsuarios(char archivoUsuarios[]);
int pasarUsuariosAArregloDinamico(stUsuario** arregloUsuarios, char archivoUsuarios[]);
int contarRegistrosEnArchivo(char archivoUsuarios[]);
int copiarUsuarios(stUsuario arregloUsuarios[], char archivoUsuarios[]);
//buscar jugador por nombre de usuario y mostrarlo
void verJugador(stUsuario arregloUsuarios[], int validos);
int buscarJugador(stUsuario arregloUsuarios[], int validos, char nombreABuscar[], int* pos);
//ver lista de jugadores (ordenado por orden alfabetico o mejor puntaje)
void ordenacionSeleccionOrdenAlfabetico(stUsuario arregloUsuarios[], int validos);
int encontrarMenor(stUsuario arregloUsuarios[], int validos, int pos);
void ordenacionInsercionPorPuntaje(stUsuario arregloUsuarios[], int validos);
void insertar(stUsuario arregloUsuarios[], int i, stUsuario dato);
void mostrarListaJugadores(stUsuario arregloUsuarios[], int validos);

///Puntuación global
void puntuacionGlobal(char archivoUsuarios[]);
int cargarArregloRanking(stUsuario arregloRanking[], stUsuario arregloUsuarios[], int validosDin);
void separaciones(int puntaje);

///Mostrar usuario
void mostrarUsuario(stUsuario A);
void mostrarLosUsuarios(char archivoUsuarios[]);

#endif // cuentas

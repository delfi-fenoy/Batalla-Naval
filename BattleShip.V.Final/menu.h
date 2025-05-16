#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

///----------Librerias----------///
#include "juego.h"

///----------Constante-----------///
#define constantedeX 10
#define constantedeY 3

///----------FuncionesExtra---------///
void gotoxy(int x,int y); // Funcion GOTOXY, capacidad de ubicar texto donde sea

///----------PantallaPrincipal----------///
void tituloPrincipal(); // Titulo Principal
void pantallaPrincipal(); // La Pantalla Principal

///----------MenuPrincipal----------///
void tituloMenu(); // Diseño del Titulo Principal
void menuPrincipal(stUsuario A, char archivoUsuario[]); // Menu Principal

///----------MenuOpciones----------///
void tituloOpciones(); // Diseño del Titulo Opciones
void menuOpciones(stUsuario *A, char archivoUsuario[], int* flag); // Apartado Opciones


#endif // MENU_H_INCLUDED

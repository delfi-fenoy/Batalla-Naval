#include "menu.h"

///----------Funciones Extra----------///
void gotoxy(int x,int y) // Gotoxy
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

///----------PantallaPrincipal----------///
void tituloPrincipal() // Diseño del Titulo Principal
{

    gotoxy(constantedeX,constantedeY);
    printf("_______________________________________________");

    ///La I representa la longitud de las lineas verticales
    for (int i = 1; i < 12; i++)
    {
        gotoxy(constantedeX-1,constantedeY + i);
        printf("|");
        gotoxy(constantedeX+47,constantedeY + i);
        printf("|");

    }

    gotoxy(constantedeX,constantedeY + 1);
    printf(VERDE_T"  ____            _             _   _\n");
    gotoxy(constantedeX,constantedeY + 2);
    printf(" | __ )    __ _  | |_    __ _  | | | |   __ _\n");
    gotoxy(constantedeX,constantedeY + 3);
    printf(" |  _ \\   / _` | | __|  / _` | | | | |  / _` |\n");
    gotoxy(constantedeX,constantedeY + 4);
    printf(" | |_) | | (_| | | |_  | (_| | | | | | | (_| |\n");
    gotoxy(constantedeX,constantedeY + 5);
    printf(" |____/   \\__,_|  \\__|  \\__,_| |_| |_|  \\__,_|\n\n");

    gotoxy(constantedeX,constantedeY + 6);
    printf("      _   _                           _       \n");
    gotoxy(constantedeX,constantedeY + 7);
    printf("     | \\ | |   __ _  __   __   __ _  | |     \n");
    gotoxy(constantedeX,constantedeY + 8);
    printf("     |  \\| |  / _` | \\ \\ / /  / _` | | |   \n");
    gotoxy(constantedeX,constantedeY + 9);
    printf("     | |\\  | | (_| |  \\ V /  | (_| | | |    \n");
    gotoxy(constantedeX,constantedeY + 10);
    printf("     |_| \\_|  \\__,_|   \\_/    \\__,_| |_|  \n"RESET_COLOR);

    gotoxy(constantedeX,constantedeY + 11);
    printf("_______________________________________________");
}

void pantallaPrincipal() // La Pantalla Principal
{
    //Variables
    stUsuario A;
    int flag = 0; //para volver a pantalla principal al dar de baja cuenta
    int flag1; //para la validacion para que no se ingresen letras
    char cadena[20]; //variable para ingresar numeros en cada menu, luego se pasa a variable opcion
    char archivoUsuarios[20] = "ArchivoUsuarios.bin";
    int opcion;

    do
    {
        do
        {
            system("cls");
            tituloPrincipal();

            printf(VERDE_T"\n\n \t\t   ( Iniciar Sesion     = 1 )\n");
            printf("\t\t   ( Crear Cuenta       = 2 )\n");
            printf("\t\t   ( Recuperar Cuenta   = 3 )\n");
            printf("\t\t   ( Usuarios           = 4 )\n");
            printf("\t\t   ( Salir del juego    = 0 )\n\n"RESET_COLOR);

            printf("\t\t   ( %cQue hacemos? ) ==> ",168);
            scanf("%s", &cadena);

            flag1 = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

            opcion = comprobacionNumeroValido(cadena, flag1); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
        }
        while(flag1 == 1); //repetir mientras se ingresen letras

        system("cls");

        switch(opcion)
        {
        case 1: // Iniciar Sesion

            A = iniciarSesion(archivoUsuarios, &flag);

            if(flag == 1) // Si el usuario es valido y esta activo (estado = 1)
            {
                printf(VERDE_T"\n\nSesion iniciada con exito, Bienvenido/a %s\n\n"RESET_COLOR, A.nombre);
                system("pause");
                system("cls");
                menuPrincipal(A, archivoUsuarios);
            }

            break;

        case 2: // Creacion de Cuenta
            crearCuenta(archivoUsuarios);
            printf("\n");
            break;

        case 3:
            recuperarCuenta(archivoUsuarios);
            printf("\n");
            system("pause");
            break;

        case 4:
            printf("ARCHIVO\n");
            mostrarLosUsuarios(archivoUsuarios);
            printf("\n");
            system("pause");
            break;

        default:
            if (opcion != 0)
            {
                system("cls");
                printf("Error\n");
                system("pause");
                system("cls");
            }
            break;
        }//Switch

    }
    while (opcion != 0);  //Do-While

    ///Fin del Programa
    system("cls");
    printf (ROJO_T"Fin del Programa...\n");
}

///----------MenuPrincipal----------///
void tituloMenu() // Diseño del Titulo Principal
{
    gotoxy(constantedeX,constantedeY);
    printf(RESET_COLOR"_________________________________");

    ///La I representa la longitud de las lineas verticales
    for (int i = 1; i < 7; i++)
    {
        gotoxy(constantedeX-1,constantedeY + i);
        printf(RESET_COLOR"|");
        gotoxy(constantedeX+33,constantedeY + i);
        printf(RESET_COLOR"|");

    }

    gotoxy(constantedeX,constantedeY + 1);
    printf(VERDE_T"  __  __ \n");
    gotoxy(constantedeX,constantedeY + 2);
    printf(" |  \\/  |   ___   _ __    _   _ \n");
    gotoxy(constantedeX,constantedeY + 3);
    printf(" | |\\/| |  / _ \\ | '_ \\  | | | | \n");
    gotoxy(constantedeX,constantedeY + 4);
    printf(" | |  | | |  __/ | | | | | |_| | \n");
    gotoxy(constantedeX,constantedeY + 5);
    printf(" |_|  |_|  \\___| |_| |_|  \\__,_| \n"RESET_COLOR);

    gotoxy(constantedeX,constantedeY + 6);
    printf("_________________________________");
}

void menuPrincipal(stUsuario A, char archivoUsuario[]) // Menu Principal
{
    int flag=1;
    int opcion;
    int flag1; //para la validacion para que no se ingresen letras
    char cadena[20]; //variable para ingresar numeros en cada menu, luego se pasa a variable opcion

    do
    {
        do
        {
            system("cls");
            tituloMenu();

            printf(VERDE_T"\n\n\t      ( Jugar             = 1 )\n");
            printf("\t      ( Info del Usuario  = 2 )\n");
            printf("\t      ( Otros Usuarios    = 3 )\n");
            printf("\t      ( Puntuacion Global = 4 )\n");
            printf("\t      ( Opciones          = 5 )\n");
            printf("\t      ( Cerrar Sesion     = 0 )\n\n"RESET_COLOR);

            printf("\t      ( %cQue hacemos? ) ==> ",168);
            scanf("%s", &cadena);

            flag1 = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

            opcion = comprobacionNumeroValido(cadena, flag1); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
        }
        while(flag1 == 1);

        system("cls");

        switch(opcion)
        {
        case 1: // Jugar Batalla Naval
            system("cls");
            A = batallaNaval(archivoUsuario, A);
            break;

        case 2: // Usuario
            printf(VERDE_T"<===== Informacion del Usuario =====>\n\n"RESET_COLOR);
            infoDelUsuario(A);
            system("pause");
            break;

        case 3: // Otros Usuario (buscar jugador o lista de jugadores)
            otrosUsuarios(archivoUsuario);
            break;

        case 4: // Puntuacion Global
            printf(AMARILLO_T"<============ Puntuacion global ============>\n\n"RESET_COLOR);
            puntuacionGlobal(archivoUsuario);
            printf("\n\n");
            system("pause");
            break;

        case 5: // Opciones
            menuOpciones(&A,archivoUsuario, &flag);
            if(flag == 0) //si la cuenta se dio de baja con exito, en seccion 'Dar de baja'...
            {
                opcion = 0; //cambiar 'opcion' a 0 para cortar while y volver a PantallaPrincipal
            }
            break;

        default:
            if (opcion != 0)
            {
                system("cls");
                printf("Error\n\n");
                system("pause");
                system("cls");
            }
            break;
        }//Switch

    }
    while (opcion != 0);  //Do-While
    system("cls");
    printf(ROJO_T"Cerrando Sesion.");
    sleep(1);
    printf (".");
    sleep(1);
    printf ("."RESET_COLOR);
    sleep(1);
}

///----------MenuOpciones----------///
void tituloOpciones()   // Diseño del Titulo Opciones
{
    gotoxy(constantedeX,constantedeY);
    printf("_________________________________________________________");

    ///La I representa la longitud de las lineas verticales
    for (int i = 1; i < 8; i++)
    {
        gotoxy(constantedeX-1,constantedeY + i);
        printf(RESET_COLOR"|");
        gotoxy(constantedeX+57,constantedeY + i);
        printf(RESET_COLOR"|");

    }

    gotoxy(constantedeX,constantedeY + 1);
    printf(VERDE_T"   ___                   _\n");
    gotoxy(constantedeX,constantedeY + 2);
    printf("  / _ \\   _ __     ___  (_)   ___    _ __     ___   ___  \n");
    gotoxy(constantedeX,constantedeY + 3);
    printf(" | | | | | '_ \\   / __| | |  / _ \\  | '_ \\   / _ \\ / __| \n");
    gotoxy(constantedeX,constantedeY + 4);
    printf(" | |_| | | |_) | | (__  | | | (_) | | | | | |  __/ \\__ \\ \n");
    gotoxy(constantedeX,constantedeY + 5);
    printf("  \\___/  | .__/   \\___| |_|  \\___/  |_| |_|  \\___| |___/ \n");
    gotoxy(constantedeX,constantedeY + 6);
    printf("         |_|  \n"RESET_COLOR);

    gotoxy(constantedeX,constantedeY + 7);
    printf("_________________________________________________________");
}

void menuOpciones(stUsuario *A, char archivoUsuario[], int* flag) // Apartado Opciones
{
    int opcion;
    int flag1; //para la validacion para que no se ingresen letras
    char cadena[20]; //variable para ingresar numeros en cada menu, luego se pasa a variable opcion

    do
    {
        do
        {
            system("cls");
            tituloOpciones();

            printf(VERDE_T"\n\n\t\t      ( Modificar Usuario   = 1 )\n");
            printf("\t\t      ( Dar de baja cuenta  = 2 )\n");
            printf("\t\t      ( Regresar            = 0 )\n\n"RESET_COLOR);

            printf("\t\t      ( %cQue hacemos? ) ==> ",168);
            scanf("%s", &cadena);

            flag1 = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

            opcion = comprobacionNumeroValido(cadena, flag1); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
        }
        while(flag1 == 1);

        system("cls");

        switch(opcion)
        {
        case 1: // Modificar Usuario
            printf("<===== Modificar Usuario =====>\n\n");
            *A = modificarUsuario(archivoUsuario, *A);
            break;

        case 2: // Dar de Baja
            *flag = darDeBaja(archivoUsuario,*A);

            if(*flag == 0) // Si se dio de baja la cuenta con exito
            {
                opcion = 0; // Cambiar 'opcion' a 0 para cortar while y volver a menuPrincipal
            }
            break;

        default:
            if (opcion != 0)
            {
                system("cls");
                printf("Error\n\n");
                system("pause");
                system("cls");
            }
            break;
        } // Switch
    }
    while (opcion != 0);  // Do-While
}

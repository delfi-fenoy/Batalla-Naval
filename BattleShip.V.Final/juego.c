#include "juego.h"


///-----------------------------------------------------------Pre_Partida-----------------------------------------------------------///

stUsuario batallaNaval(char archivoUsuarios[], stUsuario usuario) // Funcion principal
{
    /// Tablas
    int tablaUsuario[10][10] = {};
    int tablaRival[10][10] = {};
    int dim = 10;

    ///Variables
    int ganador;
    int puntaje = 0;

    // Seleccionar como crear la tabla (aleatorio o manual)
    elegirCrearTabla(dim, tablaUsuario);

    // Crear la tabla de Rival
    crearRivalBot(dim, tablaRival);

    // Partida entera, retorna el puntaje
    puntaje = partidaBatallaNaval(dim, tablaUsuario, tablaRival, &ganador);

    // Ganador de la partida
    system("cls");
    if (ganador == 1) // Gana el Jugador
    {
        puntaje += 200;
        tituloVictoria();
        printf(AMARILLO_T"\n\t\t\t\t Felicidades Soldado %s!\n\n"RESET_COLOR, usuario.nombre);
        printf("\t\t\t\t Puntuacion Total = "AMARILLO_T"%d!\n\n\n"RESET_COLOR, puntaje);
        system("pause");

    }
    if (ganador == 0) // Pierde el Jugador
    {
        puntaje -= 100;
        tituloDerrota();
        printf(ROJO_T"\n\t\t Buen intento Soldado %s, ma%cana sera un dia mejor!\n"RESET_COLOR, usuario.nombre, 167);
        printf("\t\t\t   Puntuacion Total = "AMARILLO_T"%d\n\n\n"RESET_COLOR, puntaje);
        system("pause");
    }

    // Pasar puntos al Archivo
    usuario = pasarPuntaje(archivoUsuarios, usuario, puntaje, ganador);

    return usuario;
}

///----------Elegir Tabla----------///
void elegirCrearTabla(int dim, int tablaUsuario[dim][dim]) // Elegir como armar la tabla
{
    int flag;
    int opcion;
    char cadena[20]; //variable para ingresar numeros en cada menu, luego se pasa a variable opcion

    do
    {
        do
        {
            system("cls");
            printf(VERDE_T"<====== Las naves estan listas, empieza la batalla ======>\n\n"RESET_COLOR);
            printf(CYAN_T"\t    ( Colocar Manualmente = 1 ) \n");
            printf("\t    ( Aleatorio           = 2 ) \n\n"RESET_COLOR);

            printf("\t    ( %cQue hacemos? ) ==> ",168);
            scanf("%s", &cadena);

            flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

            opcion = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido

        }
        while(flag == 1);

        if (opcion == 1) // 1- Colocar de manera manual la tabla
        {
            crearTablaUsuario(dim,tablaUsuario);
            opcion = 0;
        }
        else if (opcion == 2) // 2- Colocar de manera automatica la tabla
        {
            crearRivalBot(dim, tablaUsuario);
            opcion = 0;
        }
        else // 1 o 2 != Error
        {
            system("cls");
            printf("Esa opcion no existe >:C\n\n");
            system("pause");
            system("cls");
        }
    }
    while (opcion != 0);
}

///----------Crear Tabla Manualmente----------///
void crearTablaUsuario(int dim, int tablaUsuario[dim][dim]) // Crear la tabla de Manera Manual
{
    system("cls");
    agregarBarcos(2,dim,tablaUsuario);
    agregarBarcos(3,dim,tablaUsuario);
    agregarBarcos(4,dim,tablaUsuario);
    agregarBarcos(5,dim,tablaUsuario);
}

void agregarBarcos (int barco,int dim, int laTabla[dim][dim]) // Agregar Barco
{
    int barcoX;
    int barcoY;
    char forma;
    int flag;

    do
    {
        system("cls");
        mostrarTablaUsuario(dim,laTabla);
        pedirCoordenadasBarcos(&barcoX, &barcoY, &forma, barco);

        flag = comprobacionSuperposicionBarcos(dim, laTabla, barco, barcoX, barcoY, forma);

        if(flag == 1) //en caso de barcos superpuestos
        {
            printf(ROJO_T"\n\n Los barcos no deben estar superpuestos.\n");
            printf(" Elige nuevamente.\n\n"RESET_COLOR);
            system("pause");
            system("cls");
        }
        else //flag == 0 - en caso de barcos no superpuestos
        {
            flag = comprobacionLimiteBarcos(dim, laTabla, barco, barcoX, barcoY, forma);

            if(flag == 1) //en caso de pasarse de dimension del tablero
            {
                printf(ROJO_T"\n\n El barco debe estar dentro del limite del tablero.\n");
                printf(" Elige nuevamente.\n\n"RESET_COLOR);
                system("pause");
                system("cls");
            }
            else //flag == 0 - en caso de no pasarse de dimension del tablero
            {
                colocarBarcosAlTablero(dim, laTabla, barco, barcoX, barcoY, forma);
            }
        }
    }
    while(flag != 0);
    system("cls");
}

void colocarBarcosAlTablero(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma) // Agrega el Barco en la tabla del Usuario
{
    for (int i = 0; i < barco ; i++) // Se agregan los barcos al tablero
    {
        if (forma == 'h') // Horizontal
        {
            laTabla[barcoX-1][barcoY+i-1] = barco;
        }
        else if (forma == 'v') // Vertical
        {
            laTabla[barcoX+i-1][barcoY-1] = barco;
        }
    }
}

void pedirCoordenadasBarcos(int* barcoX, int* barcoY, char* forma, int barco) // Pedir coordenadas y direccion al usuario + comprobacion de direccion
{
    int flag; //para la validacion para que no se ingresen letras
    char cadena[20]; //para ingresar coordenadas, luego se pasa a barcoX y barcoY

    // Se pide las coordenadas Filas y Columnas
    do
    {
        printf("\n\n Donde Quieres agregar tu barco de %d?\n\n", barco);

        printf(MAGENTA_T" ( Fila )    ==> "RESET_COLOR);
        scanf("%s", &cadena);

        flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

        *barcoX = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
    }
    while(flag == 1); //repetir mientras se ingresen letras

    do
    {
        printf(AMARILLO_T" ( Columna ) ==> "RESET_COLOR);
        scanf("%s", &cadena);

        flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

        *barcoY = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
    }
    while(flag == 1); //repetir mientras se ingresen letras

    do
    {
        printf(CYAN_T" ( Horizontal(h) o Vertical(v) )==> "RESET_COLOR);
        fflush(stdin);
        scanf("%c", &*forma);

        if( (*forma=='H') || (*forma=='V') ) // En caso de ponerlo en mayuscula, cambiarlo a minuscula
        {
            *forma = tolower(*forma); // Pasar a minuscula
        }
        if( (*forma!='h') && (*forma!='v') ) // En caso de ponerlo en mayuscula, cambiarlo a minuscula
        {
            printf("\nDireccion invalida.\n\n");
        }
    }
    while( (*forma!='h') && (*forma!='v') );
}

///----------Comprobaciones Agregar Barcos----------///
int comprobacionSuperposicionBarcos(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma) //Comprueba que los barcos no se superpongan entre si
{
    int flag = 0;
    int i = 0;

    while(flag==0 && i<barco)
    {
        if( ((forma == 'h') && (laTabla[barcoX-1][barcoY+i-1] != 0)) || ((forma == 'v') && (laTabla[barcoX+i-1][barcoY-1] != 0)) )
        {
            //Si los barcos se superponen, marcar error
            flag = 1;
        }
        i++;
    }
    return flag;
}

int comprobacionLimiteBarcos(int dim, int laTabla[dim][dim], int barco, int barcoX, int barcoY, char forma) //Comprueba que los barcos no se pasen del limite del tablero
{
    int flag = 0;
    int i = 0;

    while(flag==0 && i<barco)
    {
        if( ((forma == 'h') && (barcoY+i > dim)) || ((forma == 'v') && (barcoX+i > dim)) )
        {
            // Si se pasa de los limites de la tablero, marcar error
            flag = 1;
        }
        i++;
    }
    return flag;
}

///---------Crear Tabla Rival----------///
void crearRivalBot (int dim, int tablaRival[dim][dim]) // Crea el Tablero del Rival
{
    system("cls");
    printf(" Cargando...");

    agregarBarcosRival(2,dim,tablaRival);
    agregarBarcosRival(3,dim,tablaRival);
    agregarBarcosRival(4,dim,tablaRival);
    agregarBarcosRival(5,dim,tablaRival);
}

void agregarBarcosRival(int barco, int dim, int tablaRival[dim][dim]) // Agrega los barcos en el tablero Rival
{
    int barcoX;
    int barcoY;
    char forma;
    int valor;
    int flag;

    do
    {
        /// Crea valores Aleatorios
        srand(time(NULL));
        barcoX = (rand() %dim) + 1; // Fila
        barcoY = (rand() %dim) + 1; // Columna
        valor  = rand() %2; // H o V

        // Elegir Vertical o Horizotal de manera Aleatoria
        if (valor == 1)
        {
            forma = 'h';
        }
        else if (valor == 0)
        {
            forma = 'v';
        }

        flag = comprobacionSuperposicionBarcos(dim, tablaRival, barco, barcoX, barcoY, forma);

        if (flag == 0) // En caso de que no se superpongan.
        {
            flag = comprobacionLimiteBarcos(dim, tablaRival, barco, barcoX, barcoY, forma);

            if(flag == 0) // En de no pasarse de la dimension.
            {
                colocarBarcosAlTablero(dim, tablaRival, barco, barcoX, barcoY, forma);
            }
        }

    }
    while(flag != 0);
}




///-----------------------------------------------------------Partida-----------------------------------------------------------///

int partidaBatallaNaval(int dim, int tablaUsuario[dim][dim], int tablaRival[dim][dim], int *ganador) // Partida Entera
{
    /// Barra de Vida, Jugador y Rival
    Pila vidaJugador, vidaEnemigo;
    inicpila(&vidaJugador);
    inicpila(&vidaEnemigo);

    vidaJugador = cargarPila(vidaJugador);
    vidaEnemigo = cargarPila(vidaEnemigo);

    /// Barcos
    vidaBarcos usuarioBarcos, rivalBarcos;
    usuarioBarcos = inicializarBarcos();
    rivalBarcos = inicializarBarcos();

    /// Variables Juego
    int turno;
    int puntaje = 0;
    int puntajeRival = 0;

    /// Jugabilidad
    while(!pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo))
    {
        /// Disparo Jugador
        do
        {
            system("cls");

            // Muestra las Tablas
            printf("\n\t\t Tabla Rival \t\t\t Puntaje : %d \n\n" , puntaje);
//            mostrarTablaUsuario(dim,tablaRival); //en caso de quere ver donde estan los barcos del enemigo
            mostrarTablaRival(dim, tablaRival);
            printf("\n\t\t Tabla Usuario \n\n");
            mostrarTablaUsuario(dim, tablaUsuario);
            mostrar(&vidaEnemigo);
            turno = disparoJugador(dim, tablaRival, &puntaje);

            // Comprobacion de Barco hundido
            recorrerTabla(dim, tablaRival, &rivalBarcos);
            barcoDestruido(dim, &rivalBarcos, &vidaEnemigo, &puntaje);

            //Si Acierta el Tiro
            if (turno == 2 && !pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo))
            {
                mensajeDisparoAcertado();
            }

        }
        while(turno == 2 && !pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo)); // Que se repita mientras dispare a un barco

        if(!pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo))
        {
            // Si el jugador falla el tiro
            mensajeDisparoFallido();
        }

        /// Disparo Rival
        do
        {
            turno = ataqueEnemigo(dim, tablaUsuario);

            // Comprobacion de Barco hundido
            recorrerTabla(dim, tablaUsuario, &usuarioBarcos);
            barcoDestruido(dim, &usuarioBarcos, &vidaJugador, &puntajeRival);

            if (turno == 2 && !pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo))
            {
                mensajeDisparoEnemigo();
            }

        }
        while(turno == 2 && !pilavacia(&vidaJugador) && !pilavacia(&vidaEnemigo)); // Que se repita mientras dispare a un barco
    }

    /// Condicion de Victoria
    if (pilavacia(&vidaEnemigo))
    {
        *ganador = 1;
    }
    else if (pilavacia(&vidaJugador))
    {
        *ganador = 0;
    }

    return puntaje;
}

///----------Mostrar Tablero----------///
void mostrarTablaUsuario(int dim, int laTabla[dim][dim]) // Mostra Tablero del Usuario
{
    int f = 0;
    int c = 0;

    printf("\t    ");

    for (int i = 1; i < dim+1; i++) //crea los numeros superiores de la tabla (indica columnas)
    {
        if (i >= 10)
        {
            printf(AMARILLO_T"%d "RESET_COLOR, i);
        }
        else
        {
            printf(AMARILLO_T"%d  "RESET_COLOR, i);
        }
    }

    printf("\n");

    for (f=1; f < dim+1; f++) // Crea los numeros del costado de la tabla (indica filas)
    {
        if (f >= 10)
        {
            printf(MAGENTA_T"\t%d "RESET_COLOR, f);
        }
        else
        {
            printf(MAGENTA_T"\t%d  "RESET_COLOR, f);
        }

        for (c = 0; c < dim; c++) // Crea el contenido de la tabla (agua, barcos, Impactos)
        {
            if (laTabla[f-1][c] == -1) // Impacto de Agua
            {
                printf (VERDE_T" X "RESET_COLOR);
            }
            else if (laTabla[f-1][c] < -1)
            {
                printf (ROJO_T" %c "RESET_COLOR, 157); // Impacto de Barco
            }
            else if (laTabla[f-1][c] > 0)
            {
                printf (" %c ", 254 ); // Barcos
            }
            else
            {
                printf (CYAN_T" %c "RESET_COLOR, 254 ); // Agua
            }
        }
        printf ("\n");
    }
}

void mostrarTablaRival(int dim, int laTabla[dim][dim])  // Mostra Tablero del Rival
{
    int f = 0;
    int c = 0;

    printf("\t    ");

    for (int i = 1; i < dim+1; i++) //crea los numeros superiores de la tabla (indica columnas)
    {
        if (i >= 10)
        {
            printf(AMARILLO_T"%d "RESET_COLOR, i);
        }
        else
        {
            printf(AMARILLO_T"%d  "RESET_COLOR, i);
        }
    }

    printf("\n");

    for (f=1; f < dim+1; f++) //crea los numeros del costado de la tabla (indica filas)
    {
        if (f >= 10)
        {
            printf(MAGENTA_T"\t%d "RESET_COLOR, f);
        }
        else
        {
            printf(MAGENTA_T"\t%d  "RESET_COLOR, f);
        }

        for (c = 0; c < dim; c++) // Crea el contenido de la tabla (agua, barcos)
        {
            if (laTabla[f-1][c] == -1) // Impacto de Agua
            {
                printf (VERDE_T" X "RESET_COLOR, 158);
            }
            else if (laTabla[f-1][c] < -1) // Impacto de Barco
            {
                printf (ROJO_T" %c "RESET_COLOR, 157);
            }
            else // Agua
            {
                printf (CYAN_T" %c "RESET_COLOR, 254 );
            }
        }
        printf ("\n");
    }
}

///---------Mensajes al Jugador----------///
void mensajeDisparoAcertado() // Printf´s Por si hay impacto por parte del jugador
{
    int numRandom = rand() % 6 + 1; // Numero del 1 al 5

    switch (numRandom) // Switch para eleguir el mensaje
    {
        case 1:
            printf("\n%cImpacto directo!\n\n",173);
            break;

        case 2:
            printf("\n%cBlanco acertado!\n\n",173);
            break;

        case 3:
            printf("\n%cBuen tiro, impacto en un barco enemigo!\n\n",173);
            break;

        case 4:
            printf("\n%cTiro certero, has dado en el blanco!\n\n",173);
            break;

        case 5:
            printf("\n%cExcelente disparo!\n\n",173);
            break;

        default:
            printf("\n%cDisparo Acertado!\n\n",173);
            break;
    }
    system("pause");
}

void mensajeDisparoFallido() // Printf´s Por el jugador falla
{
    int numRandom = rand() % 5 + 1; // Numero del 1 al 5

    switch (numRandom)
    {
        case 1:
            printf("\n%cDisparo fallido!\n\n",173);
            break;

        case 2:
            printf("\n%cAgua! No has acertado ningun barco\n\n",173);
            break;

        case 3:
            printf("\n%cOh no, no has dado en el blanco!\n\n",173);
            break;

        case 4:
            printf("\n%cEl disparo se perdio en el mar!\n\n",173);
            break;

        case 5:
            printf("\n%cNada por aqui, intenta de nuevo!\n\n",173);
            break;

        default:
            printf("\n%cDisparo fallido!\n\n",173);
            break;
    }
    system("pause");
}

void mensajeDisparoEnemigo() // Printf´s Por si el enemigo impacta
{
    int numRandom = rand() % 5 + 1;

    switch (numRandom)
    {
        case 1:
            printf(ROJO_T"\n%cEl enemigo ha alcanzado uno de tus barcos!\n\n"RESET_COLOR,173);
            break;

        case 2:
            printf(ROJO_T"\n%cAlerta! El enemigo ha acertado en uno de tus barcos\n\n"RESET_COLOR,173);
            break;

        case 3:
            printf(ROJO_T"\n%cImpacto enemigo en tu flota!\n\n"RESET_COLOR,173);
            break;

        case 4:
            printf(ROJO_T"\n%cTu flota esta bajo ataque, han impactado un barco!\n\n"RESET_COLOR,173);
            break;

        case 5:
            printf(ROJO_T"\n%cEl enemigo ha encontrado su objetivo!\n\n"RESET_COLOR,173);
            break;
    }
    system("pause");
}

///---------Inicializar Partida----------///
vidaBarcos inicializarBarcos() // Inicializa la Struct que contine las "vidas" de los barcos
{
    vidaBarcos AUX;

    AUX.barco2 = 2;
    AUX.barco3 = 3;
    AUX.barco4 = 4;
    AUX.barco5 = 5;

    return AUX;
}

Pila cargarPila(Pila vida) // Inicializa la barra de Vida del jugador
{
    int i;

    for( i = 2 ; i < 6; i++ )
    {
        apilar(&vida, i);
    }

    return vida;
}

///--------BarcosDestruido----------///
void barcoDestruido(int dim, vidaBarcos *barcosTotales, Pila *barraVida, int *puntaje) // Avisa sobre los barcos destruidos y suma los puntajes
{
    //Comprobacion de que los barcos se hayan hundido, avisa sobre el derrivo
    if ((*barcosTotales).barco2 == 0)
    {
        printf("Se ha derribado el Barco de tama%co 2\n",164);
        (*barcosTotales).barco2 = -1; // Detiene que se repita el if
        *puntaje += 50; // Suma al puntaje
        desapilar(&*barraVida); // Desapila una vida
    }
    else if ((*barcosTotales).barco3 == 0)
    {
        printf("Se ha derribado el Barco de tama%co 3\n",164);
        (*barcosTotales).barco3 = -1;
        *puntaje += 75;
        desapilar(&*barraVida);
    }
    else if ((*barcosTotales).barco4 == 0)
    {
        printf("Se ha derribado el Barco de tama%co 4\n",164);
        (*barcosTotales).barco4 = -1;
        *puntaje += 100;
        desapilar(&*barraVida);
    }
    else if ((*barcosTotales).barco5 == 0)
    {
        printf("Se ha derribado el Barco de tama%co 5\n",164);
        (*barcosTotales).barco5 = -1;
        *puntaje += 150;
        desapilar(&*barraVida);
    }
}

void recorrerTabla(int dim, int tabla[dim][dim], vidaBarcos *barcosTotales) // Recorre toda la tabla para comprobar la vida de los barcos
{
    int f = 0;
    int c = 0;

    for (f = 0; f < dim ; f++)
    {
        for (c = 0; c < dim ; c++)
        {
            // Busca en la tabla el valor negativo de los barcos, los reemplaza por -6
            // Y le resta a barcosTotales un "punto de vida"
            if (tabla[f][c] == -2)
            {
                (*barcosTotales).barco2--;
                tabla[f][c] = -6;
            }

            else if (tabla[f][c] == -3)
            {
                (*barcosTotales).barco3--;
                tabla[f][c] = -6;
            }

            else if (tabla[f][c] == -4)
            {
                (*barcosTotales).barco4--;
                tabla[f][c] = -6;
            }

            else if (tabla[f][c] == -5)
            {
                (*barcosTotales).barco5--;
                tabla[f][c] = -6;
            }
        }
    }
}

///---------Disparos----------///
int disparoJugador(int dim, int tablaRival[dim][dim], int *puntaje) // Disparo del Jugador
{
    int disparoF;
    int disparoC;
    int flag;
    int turno = 0;

    do
    {
        pedirCoordenadasDisparo(&disparoF, &disparoC); // Pide las coordenadas del Disparo

        flag = comprobacionDisparoLimiteTablero(disparoF, disparoC, dim);

        if(flag == 1) // En caso de coordenadas fuera del tablero
        {
            printf("\n\t - Has disparado fuera del tablero.\n");
            printf("\n\t - Elige nuevamente.");
        }
        else //flag == 0 - En caso de coordenadas dentro del tablero
        {
            flag = comprobacionDisparoSuperposicion(disparoF, disparoC, dim, tablaRival); // Comprueba

            if(flag == 1) // Si ya se disparó en esa zona
            {
                printf("\n\t - Ya has disparado en esa posicion.\n");
                printf("\n\t - Elige nuevamente.");
            }
            else // Si la zona está habilitada
            {
                if (tablaRival[disparoF-1][disparoC-1] == 0) // Si disparó a Agua
                {
                    tablaRival[disparoF-1][disparoC-1] = -1;
                    *puntaje -= 5;
                    turno = 1;
                }
                else if (tablaRival[disparoF-1][disparoC-1] > 1) // Si disparó a un barco
                {
                    tablaRival[disparoF-1][disparoC-1] = tablaRival[disparoF-1][disparoC-1] * -1;
                    *puntaje += 10;
                    turno = 2;
                }
            }
        }
    }
    while(flag != 0);

    return turno;
}

int ataqueEnemigo(int dim, int tablaUsuario[dim][dim]) // Disparo del Rival
{
    int turno = 0;
    int disparoF;
    int disparoC;
    int flag = 0;

    do
    {
        disparoF = (rand() %dim) + 1;
        disparoC = (rand() %dim) + 1;

        flag = comprobacionDisparoSuperposicion(disparoF, disparoC, dim, tablaUsuario);

        if(flag == 0) // Si NO se disparó en esa zona
        {
            if (tablaUsuario[disparoF-1][disparoC-1] == 0) // Si disparó a Agua
            {
                tablaUsuario[disparoF-1][disparoC-1] = -1;
                turno = 1;
            }
            else if (tablaUsuario[disparoF-1][disparoC-1] > 1)
            {
                tablaUsuario[disparoF-1][disparoC-1] = tablaUsuario[disparoF-1][disparoC-1] * -1;
                turno = 2;
            }
        }
    }
    while(flag==1); //que se repita hasta disparar coordenada valida

    return turno;
}

///---------Comprobaciones de Disparo----------///
void pedirCoordenadasDisparo(int* disparoF, int* disparoC) // Pide las coordenas de donde sera el disparo
{
    int flag; //para la validacion para que no se ingresen letras
    char cadena[20]; //para ingresar coordenadas, luego se pasa a barcoX y barcoY

    do
    {
        printf("\n\n %cDonde Disparamos? \n\n",168);

        printf(MAGENTA_T" - Fila    ==> "RESET_COLOR);
        scanf("%s", &cadena);

        flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

        *disparoF = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor
    }
    while(flag == 1); //repetir mientras se ingresen letras

    do
    {
        printf(AMARILLO_T" - Columna ==> "RESET_COLOR);
        scanf("%s", &cadena);

        flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

        *disparoC = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor
    }
    while(flag == 1); //repetir mientras se ingresen letras
}

int comprobacionDisparoLimiteTablero(int disparoF, int disparoC, int dim) // Comprueba que el disparo no esta fuera del tablero
{
    int flag = 0;

    if( (disparoF-1 > dim) || (disparoC-1 > dim) )
    {
        // Si esa zona se encuentra fuera de los limites del tablero, retorna flag 1
        flag = 1;
    }

    return flag;
}

int comprobacionDisparoSuperposicion(int disparoF, int disparoC, int dim, int laTabla[dim][dim]) // Comprueba que el disparo no sea en una zona ya impactada
{
    int flag = 0;

    if(laTabla[disparoF-1][disparoC-1] < 0 ) ///cambiar condiciones < 0
    {
        // Si en esa zona ya se disparo, retorna flag 1
        flag = 1;
    }

    return flag;
}


///----------Comprobacion para que no se ingresen letras----------///
int esNumeroValido(char cadena[]) //Lee el numero ingresado y comprueba que no se hayan ingresado letras (en caso contrario, retorna 1)
{
    int flag = 0; //flag=0 -> no tiene letras
    int i = 0;
    // Recorremos cada carácter de la cadena
    while(cadena[i] != '\0' && flag == 0) //repetir hasta
    {
        if (!isdigit(cadena[i])) //en caso de encontrar una letra...
        {
            flag = 1;
        }
        i++;
    }
    //si todos los caracteres son dígitos, retornamos flag=0
    return flag;
}

int comprobacionNumeroValido(char cadena[], int flag) //Pasar valor a variable en caso de nro sin letras, o mostrar mensaje de error en lo contrario
{
    int opcion;
    if(flag == 1)
    {
        printf("\nError. No se deben ingresar letras.\n");
        printf("\n\n");
        system("pause");
    }
    else
    {
        opcion = atoi(cadena); //convertir cadena de caracteres que representa un número en su equivalente entero
    }
    return opcion;
}


///-----------------------------------------------------------Fin de Partida-----------------------------------------------------------///

///---------Titulos----------///
void tituloVictoria() // Titulo diciendo Victoria
{
    gotoxy(constantedeX,constantedeY);
    printf("____________________________________________________________________________");

    ///La I representa la longitud de las lineas verticales
    for (int i = 1; i < 8; i++)
    {
        gotoxy(constantedeX-1,constantedeY + i);
        printf(RESET_COLOR"|");
        gotoxy(constantedeX+76,constantedeY + i);
        printf(RESET_COLOR"|");

    }
    gotoxy(constantedeX,constantedeY + 1);
    printf(VERDE_T" __      __  _____    _____   _______    ____    _____    _____\n");
    gotoxy(constantedeX,constantedeY + 2);
    printf(" \\ \\    / / |_   _|  / ____| |__   __|  / __ \\  |  __ \\  |_   _|     /\\\n");
    gotoxy(constantedeX,constantedeY + 3);
    printf("  \\ \\  / /    | |   | |         | |    | |  | | | |__) |   | |      /  \\\n");
    gotoxy(constantedeX,constantedeY + 4);
    printf("   \\ \\/ /     | |   | |         | |    | |  | | |  _  /    | |     / /\\ \\\n");
    gotoxy(constantedeX,constantedeY + 5);
    printf("    \\  /     _| |_  | |____     | |    | |__| | | | \\ \\   _| |_   / ____ \\\n");
    gotoxy(constantedeX,constantedeY + 6);
    printf("     \\/     |_____|  \\_____|    |_|     \\____/  |_|  \\_\\ |_____| /_/    \\_\\"RESET_COLOR);

    gotoxy(constantedeX,constantedeY + 7);
    printf("____________________________________________________________________________\n");
}

void tituloDerrota() // Titulo diciendo Derrota
{
    gotoxy(constantedeX,constantedeY);
    printf("___________________________________________________________________");

    ///La I representa la longitud de las lineas verticales
    for (int i = 1; i < 8; i++)
    {
        gotoxy(constantedeX-1,constantedeY + i);
        printf(RESET_COLOR"|");
        gotoxy(constantedeX+67,constantedeY + i);
        printf(RESET_COLOR"|");

    }

    gotoxy(constantedeX,constantedeY + 1);
    printf(ROJO_T"  _____    ______   _____    _____     ____    _______\n");
    gotoxy(constantedeX,constantedeY + 2);
    printf(" |  __ \\  |  ____| |  __ \\  |  __ \\   / __ \\  |__   __|     /\\ \n");
    gotoxy(constantedeX,constantedeY + 3);
    printf(" | |  | | | |__    | |__) | | |__) | | |  | |    | |       /  \\ \n");
    gotoxy(constantedeX,constantedeY + 4);
    printf(" | |  | | |  __|   |  _  /  |  _  /  | |  | |    | |      / /\\ \\ \n");
    gotoxy(constantedeX,constantedeY + 5);
    printf(" | |__| | | |____  | | \\ \\  | | \\ \\  | |__| |    | |     / ____ \\ \n");
    gotoxy(constantedeX,constantedeY + 6);
    printf(" |_____/  |______| |_|  \\_\\ |_|  \\_\\  \\____/     |_|    /_/    \\_\\ "RESET_COLOR);

    gotoxy(constantedeX,constantedeY + 7);
    printf("___________________________________________________________________\n");
}

///---------PasarPuntaje----------///
stUsuario pasarPuntaje(char archivoUsuarios[], stUsuario usuario, int puntaje, int ganador) // Pasa el Puntaje al usuario
{
    int pos = buscarPosicionEnARchivo(archivoUsuarios, usuario.nombre); // Busco la posicion del Usuario

    FILE* buff = fopen(archivoUsuarios, "r+b");

    if(buff)
    {
        if (ganador == 1)
        {
            usuario.estadisticas.victorias += 1; // +1 Si gana la partida
        }

        usuario.estadisticas.partidasJugadas += 1; // +1 partida jugadas

        if (usuario.estadisticas.mejorPuntaje < puntaje) // Si el puntaje nuevo, es mayor que el anterior
        {
            usuario.estadisticas.mejorPuntaje = puntaje; // Se intercambia
        }

        fseek(buff, sizeof(stUsuario)*(pos-1), SEEK_SET); // Se posiciona en el usuario a editar
        fwrite(&usuario, sizeof(stUsuario), 1, buff); // Sobre-Escribe los nuevos datos

        fclose(buff);
    }
    else // Si el archivo, no se abre
    {
        printf("\nError.");
    }

    return usuario;

}








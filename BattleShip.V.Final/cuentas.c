#include "cuentas.h"

///-----------------------------------------------------------Iniciar_Sesion-----------------------------------------------------------///
stUsuario iniciarSesion(char archivoUsuarios[], int* flag) // Ingresar nombre y contraseña, retorna info de usuario completo
{
    // Variables a Utilizar
    stUsuario ingreso;

    // Pedimos los datos
        printf(VERDE_T"<====== Iniciar Sesion ======>\n\n"RESET_COLOR);
        printf(CYAN_T" (Ingrese nombre de usuario ) ==> "RESET_COLOR);
        fflush(stdin);
        gets(ingreso.nombre);

        printf(CYAN_T" (Ingrese su contrase%ca ) ==> "RESET_COLOR,164);
        fflush(stdin);
        gets(ingreso.contrasenia);

        *flag = comprobacionIniciarSesion(archivoUsuarios, &ingreso);

        if(*flag == 0) // Si el usuario es incorrecto (nombre o contraseña)
        {
            printf(ROJO_T"\nUsuario o contrase%ca incorrecto.\n"RESET_COLOR,164);
            system("pause");
            system("cls");
        }

    if(ingreso.estado == 0) // En caso de ingresar usuario dado de baja...
    {
        printf(ROJO_T"\nEste usuario se encuentra dado de baja.\n"RESET_COLOR);
        *flag = 0; // Cambiar flag a 0 para que no entre a 'menuPrincipal'
        system("pause");
        system("cls");
    }

    return ingreso;
}

int comprobacionIniciarSesion(char archivoUsuarios[], stUsuario* ingreso) //Comprobacion de nombre y contraseña, retorna info de usuario
{
    int flag = 0;
    stUsuario aux;
    FILE* buff = fopen(archivoUsuarios, "rb");

    if(buff)
    {
        while((flag == 0) && (fread(&aux, sizeof(stUsuario), 1, buff) >0))
        {
            if( (strcmp(aux.nombre, (*ingreso).nombre) == 0) && (strcmp(aux.contrasenia, (*ingreso).contrasenia) == 0) ) //deben coincidir nombre y contraseña
            {
                (*ingreso).estado = aux.estado;
                (*ingreso).estadisticas.mejorPuntaje = aux.estadisticas.mejorPuntaje;
                (*ingreso).estadisticas.partidasJugadas = aux.estadisticas.partidasJugadas;
                (*ingreso).estadisticas.victorias = aux.estadisticas.victorias;
                flag = 1;
            }
        }
        fclose(buff);
    }

    return flag;
}




///-----------------------------------------------------------Crear_Cuenta-----------------------------------------------------------///
void crearCuenta(char archivoUsuarios[]) // Guarda el nombre y contraseña en el archivo
{
    FILE* buff = fopen(archivoUsuarios, "ab");
    stUsuario aux;

    if(buff)
    {
        aux = crearNombreUsuario(archivoUsuarios);
        aux = crearContrasenia(archivoUsuarios);
        aux.estado = 1;
        aux.estadisticas.mejorPuntaje = 0;
        aux.estadisticas.victorias = 0;
        aux.estadisticas.partidasJugadas = 0;

        fwrite(&aux, sizeof(stUsuario), 1, buff);

        fclose(buff);
    }
}

stUsuario crearNombreUsuario(char archivoUsuarios[]) // Lee el nombre y llama a la funcion de comprobacion
{
    stUsuario A;
    int flag;

    do
    {
        printf(VERDE_T"<====== Crear Cuenta ======>\n\n"RESET_COLOR);
        printf(CYAN_T" (Ingrese nombre de usuario (max. %d)) ==> "RESET_COLOR,DIM_NOM_CON-1); // Max de caracteres: dimension -1 (para /0)
        fflush(stdin);
        gets(A.nombre);

        if( (strlen(A.nombre)) == 0) // Si el usuario no ingresa nada
        {
            printf(ROJO_T"\nNombre vacio!\n"RESET_COLOR);
            system("pause");
            system("cls");
        }
        else
        {
            flag = comprobacionTotalNombre(A.nombre, archivoUsuarios);

            if(flag == 0)
            {
                printf(ROJO_T"\nNombre muy extenso.\n"RESET_COLOR);
                system("pause");
                system("cls");
            }
            else if (flag == -1)
            {
                printf(ROJO_T"\nNombre ya existente.\n"RESET_COLOR);
                system("pause");
                system("cls");
            }
        }
    }
    while(flag != 1);

    return A;
}

int comprobacionTotalNombre(char nomNuevo[], char archivoUsuario[]) //Comprueba que el nombre ingresado no se pase de caracteres y que no exista en el archivo
{
    FILE* buf = fopen(archivoUsuario, "rb");
    stUsuario A;
    int flag = 1;
    ///flag = -1 (nombre ya existente) / flag = 0 (nombre extenso) / flag = 1 (está Bien)

    if (buf != NULL)
    {
        if( (strlen(nomNuevo)) >= DIM_NOM_CON) //Comprobar que el nombre no se pase de caracteres maximos
        {
            flag = 0;
        }
        else
        {
            while (fread(&A, sizeof(stUsuario), 1, buf ) > 0) //Comprobar que el nombre no exista en el archivo
            {
                if((strcmp(nomNuevo, A.nombre)) == 0) //tiene en cuenta mayusculas y minusculas
                {
                    flag = -1;
                }
            }
        }
        fclose(buf);
    }
    return flag;
}

stUsuario crearContrasenia(char archivoUsuarios[]) //Lee la contraseña y llama a la funcion de comprobacion
{
    int flag;
    stUsuario A;

    do
    {
        printf(CYAN_T" (Ingrese contrase%ca (max. %d)) ==> "RESET_COLOR,164, DIM_NOM_CON-1);
        fflush(stdin);
        gets(A.contrasenia);

        if( (strlen(A.contrasenia)) == 0) //Si no se ingresa nada
        {
            flag = 0; //repetir ciclo while
            printf(ROJO_T"\nContrase%ca vacia!\n"RESET_COLOR,164);
            system("pause");
            system("cls");
        }
        else
        {
            flag = comprobacionContrasenia(A.contrasenia);

            if(flag == 0)
            {
                printf(ROJO_T"\nContrase%ca muy extensa!\n"RESET_COLOR,164);
                system("pause");
                system("cls");
            }
        }
    }
    while(flag == 0);

    return A;
}

int comprobacionContrasenia(char conNueva[]) //Comprobacion que no se hayan ingresado mas del max de caracteres
{
    int flag = 0;
    ///flag = 0 (contraseña extensa) / flag = 1 (contraseña valida)

    if( (strlen(conNueva)) < DIM_NOM_CON)
    {
        flag = 1;
    }
    return flag;
}




///-----------------------------------------------------------Dar_De_Baja-----------------------------------------------------------///
int darDeBaja(char archivoUsuarios[], stUsuario A) //En caso que la rta sea si, se da de baja el usuario
{
    //inicializar rta con 'n'
    int flag = 1;
    char res = preguntarDarDeBaja();

    if(res == 's') //si el usuario ingresa que si
    {
        do
        {
            flag = comprobacionDarDeBaja(); //flag == 0 (captcha incorrecto) / flag == 1 (captcha correcto)

            if(flag == 1) //si el captcha es correcto...
            {
                int pos = buscarPosicionEnARchivo(archivoUsuarios, A.nombre); //retornar posicion de usuario para sobrescribirlo

                FILE* buff = fopen(archivoUsuarios, "r+b");

                if(buff)
                {
                    A.estado = 0;
                    fseek(buff, sizeof(stUsuario) * (pos-1), SEEK_SET); //poner cursor en posicion del usuario
                    fwrite(&A, sizeof(stUsuario), 1, buff); //sobrescribir el usuario en el archivo

                    fclose(buff);

                    printf(ROJO_T"\nUsuario dado de baja con exito.\n\n"RESET_COLOR);
                    system("pause");
                    system("cls");
                }
                else
                {
                    printf(ROJO_T"\nError con el archivo.\n"RESET_COLOR);
                }
            }
            else //flag == 0 - si el captcha es incorrecto...
            {
                system("cls");
                printf(ROJO_T" Numero incorrecto\n\n"RESET_COLOR);
                printf(CYAN_T" ( Quieres intentarlo de nuevo? (s/n) ) ==> "RESET_COLOR);
                fflush(stdin);
                scanf("%c",&res);
                comprobacionPreguntaSiONo(&res);

                if(res == 'n')
                {
                    flag = 1; //si el usuario no quiere intentar de nuevo, cambia flag para cortar while
                }
                system("cls");
            }
        }
        while(flag == 0); //  que se repita mientras captcha sea incorrecto, y el usuario quiera seguir intentando ----   && res == 's' -> mal

        if(flag == 1 && res == 's') //si se dio de baja con exito
        {
            flag = 0; //cambiar flag para volver a pantallaPrincipal una vez dada de baja la cuenta
        }
    }
    return flag;
}

char preguntarDarDeBaja() //Preguntar al usuario si desea dar de baja su cuenta
{
    char res;

    do
    {
        printf(ROJO_T"<====== Dar de Baja ======>\n\n"RESET_COLOR);
        printf(CYAN_T" ( Desea dar de baja su cuenta? (s/n) ) ==> "RESET_COLOR);
        fflush(stdin);
        scanf("%c",&res);

        comprobacionPreguntaSiONo(&res);
    }
    while( (res!='s') && (res!='n') ); //repetir hasta ingresar rta valida

    return res;
}

void comprobacionPreguntaSiONo(char* res) //Comprueba que la respuesta a una pregunta de s/n sea valida
{
        if( (*res=='S') || (*res=='N') ) //si se ingresa rta valida en mayuscula
        {
                *res = tolower(*res); //cambiar a minuscula
        }
        else if( (*res!='s') && (*res!='n') ) //si se ingresa rta invalida
        {
            printf(ROJO_T"\n Opcion invalida.\n");
            printf(" Ingrese su respuesta nuevamente.\n\n"RESET_COLOR);
            system("pause");
            system("cls");
        }
}

int comprobacionDarDeBaja() // Comprobacion captcha para dar de baja
{
    int flag = 0;
    int res;
    srand(time(NULL));
    int numRandom = rand() %10000 + 1000; //generar numero random entre 1000 y 9999

    printf("\n ( Ingrese el numero en pantalla para confirmar ) \n");
    printf(AMARILLO_T"\t\t ==> %d\n"RESET_COLOR,numRandom);
    printf("\t\t ==> ");
    scanf("%d",&res);

    if(numRandom == res) //si el usuario ingreso correctamente el numero...
    {
        flag = 1; //glag cambia a 1 para dar de baja su cuenta
    }

    return flag;
}


///----------Recuperar_Cuenta----------///
void recuperarCuenta(char archivoUsuarios[]) //Recuperar cuenta dada de baja anteriormente
{
    stUsuario ingreso;
    int flag;
    int pos;
    FILE* buff;

    printf(VERDE_T"<====== Recuperar cuenta ======>\n\n"RESET_COLOR);
    printf(CYAN_T" (Ingrese nombre de usuario a recuperar ) ==> "RESET_COLOR);
    fflush(stdin);
    gets(ingreso.nombre);

    printf(CYAN_T" (Ingrese su contras%ca ) ==> "RESET_COLOR,164);
    fflush(stdin);
    gets(ingreso.contrasenia);

    flag = comprobacionIniciarSesion(archivoUsuarios, &ingreso); //comprobar que el usuario y contraseña existan y coincidan

    if(flag == 1) //si el usuario y contraseña son correctos...
    {
        pos = buscarPosicionEnARchivo(archivoUsuarios, ingreso.nombre);

        if(ingreso.estado == 0) //si el usuario esta dado de baja, cambia su estado a activo y lo guarda en el archivo
        {
            ingreso.estado = 1;

            buff = fopen(archivoUsuarios, "r+b");
            fseek(buff, sizeof(stUsuario)*(pos-1), SEEK_SET);
            fwrite(&ingreso, sizeof(stUsuario), 1, buff);

            fclose(buff);

            printf(AMARILLO_T"\n Usuario recuperado con exito! \n"RESET_COLOR);
        }
        else //ingreso.estado == 1, si el usuario ya estaba activo...
        {
            printf("\n El usuario ya se encuentra activo \n");
        }
    }
    else //flag == 0, si el usuario y/o contraseña es/son incorrectos...
    {
        printf(ROJO_T"\n Usuario o contrase%ca incorrecto \n"RESET_COLOR,164);
    }

    printf("\n");
    system("pause");
    system("cls");
}




///-----------------------------------------------------------Modificar_Usuario-----------------------------------------------------------///
stUsuario modificarUsuario(char archivoUsuarios[], stUsuario usuario) //Ingresar que opcion quiere modificar, y sobrescribir datos
{
    int flag; //para la validacion para que no se ingresen letras
    char cadena[20]; //variable para ingresar numeros en cada menu, luego se pasa a variable opcion
    int opcion; //campo que se desea modificar (nom. o con.)
    int pos = buscarPosicionEnARchivo(archivoUsuarios, usuario.nombre);
    FILE* buff = fopen(archivoUsuarios, "r+b"); //modo para modificar archivo

    if(buff)
    {
        do
        {
            do
            {
                system("cls");
                printf(VERDE_T"<===== Modificar Usuario =====>\n\n"RESET_COLOR);
                printf(CYAN_T" ( Nombre de usuario = 1 )\n");
                printf(" ( Contrase%ca        = 2 )\n",164);
                printf(" ( Volver atras      = 0 )\n\n"RESET_COLOR);
                printf("( %cQue modificamos? ) ==> ",168);

                scanf("%s",&cadena);

                flag = esNumeroValido(cadena); //llamar funcion que compruebe que no se ingresaron letras

                opcion = comprobacionNumeroValido(cadena, flag); //dar mensaje si se ingresaron letras, o pasar valor a variable en caso de ser valido
            }
            while(flag == 1); //repetir mientras se ingresen letras

            switch(opcion)
            {
                case 1:
                    modificarNombre(usuario.nombre, archivoUsuarios);
                    break;

                case 2:
                    modificarContrasenia(usuario.contrasenia);
                    break;
            }

            ///sobrescribir registro
            if(opcion==1 || opcion==2) //en caso de opcion valida, modificar archivo
            {
                fseek(buff, sizeof(stUsuario)*(pos-1), SEEK_SET);
                fwrite(&usuario, sizeof(stUsuario), 1, buff);
            }
        }
        while(opcion==1 || opcion==2); //terminar cuando se ingrese opcion invalida

        fclose(buff);
    }
    else
    {
        printf(ROJO_T"\nError."RESET_COLOR);
    }

    return usuario;
}

void modificarNombre(char nombre[], char archivoUsuarios[]) //Leer nombre de usuario nuevo
{
    char nombreNuevo[DIM_NOM_CON];
    int flag;

//    do
//    {
        system("cls");
        printf(CYAN_T" (Nombre de usuario nuevo (max. %d)) ==> "RESET_COLOR, DIM_NOM_CON-1);
        fflush(stdin);
        gets(nombreNuevo);

        if( (strlen(nombreNuevo)) == 0) //Si el usuario no ingresa nada
        {
            flag = 0; //para que pida ingresar nombre nuevamente
            printf(ROJO_T"\nNombre vacio.\n"RESET_COLOR);
        }
        else
        {
            flag = comprobacionTotalNombre(nombreNuevo, archivoUsuarios);

            if(flag == 0)
            {
                printf(ROJO_T"\nNombre muy extenso.\n\n"RESET_COLOR);
            }
            else if (flag == -1)
            {
                printf(ROJO_T"\nUsuario Ya Existente.\n\n"RESET_COLOR);
            }
            else //flag==1 - en caso de inrgesar nuevo nombre valido
            {
                strcpy(nombre, nombreNuevo);
                printf(VERDE_T"\nNombre modificado con exito.\n\n"RESET_COLOR);
            }
            system("pause");
            system("cls");
        }
//    }
//    while(flag != 1); //flag == 1 -> nombre valido - mover else abajo si se use este do while
}

void modificarContrasenia(char contrasenia[]) //Leer contraseña nueva
{
    int flag;
    char contraNueva[DIM_NOM_CON];

    do
    {
        system("cls");
        printf(CYAN_T" ( Ingrese contrase%ca (max. %d) ) ==> "RESET_COLOR,164, DIM_NOM_CON-1);
        fflush(stdin);
        gets(contraNueva);

        if( (strlen(contraNueva)) == 0) //Si no se ingresa nada
        {
            flag = 0; //para que pida ingresar contraseña nuevamente
            printf(ROJO_T"\nContrase%ca vacia.\n"RESET_COLOR,164);
        }
        else
        {
            flag = comprobacionContrasenia(contraNueva);

            if(flag == 0)
            {
                printf(ROJO_T"\nContrase%ca muy extensa.\n"RESET_COLOR,164);
            }
        }
    }
    while(flag == 0); //flag != 0 -> contraseña valida

    strcpy(contrasenia, contraNueva);
}

int buscarPosicionEnARchivo(char archivoUsuarios[], char nombreUsuario[]) //Buscar la posicion del usuario en el archivo (a traves del nombre) para luego modificarlo
{
    FILE* buff = fopen(archivoUsuarios, "rb");
    int flag = 0;
    stUsuario aux;
    int pos;

    if(buff)
    {
        while( (flag==0) && (fread(&aux, sizeof(stUsuario), 1, buff) >0) )
        {
            if( (strcmp(aux.nombre, nombreUsuario)) == 0)
            {
                flag = 1;
                pos = ftell(buff) / sizeof(stUsuario);
            }
        }
    }
    return pos;
}




///-----------------------------------------------------------Mostrar_Usuario-----------------------------------------------------------///
void infoDelUsuario(stUsuario usuario) //Mostrar informacion de un unico usuario
{
    printf(VERDE_T"||============================================||\n"RESET_COLOR);
    printf("\t( Nombre de usuario   = %s )\n",usuario.nombre);
    printf("\t( Partidas jugadas    = %d )\n",usuario.estadisticas.partidasJugadas);
    printf("\t( Victorias           = %d )\n",usuario.estadisticas.victorias);
    printf("\t( Mejor puntaje       = %d )\n",usuario.estadisticas.mejorPuntaje);
    printf(VERDE_T"||============================================||\n\n"RESET_COLOR);
}

void mostrarUsuario(stUsuario A) // Mostrar un Usuario Viejo
{
    printf("\n--------------------------------\n");
    printf("Usuario     ->  %s\n",A.nombre);
    printf("Contrasenia ->  %s\n",A.contrasenia);
    printf("Estado      ->  %d",A.estado);
    printf("\n--------------------------------\n");
    printf("Puntaje     ->  %ld\n",A.estadisticas.mejorPuntaje);
    printf("Victorias   ->  %d\n",A.estadisticas.victorias);
    printf("Partidas    ->  %d",A.estadisticas.partidasJugadas);
    printf("\n--------------------------------\n");
}

void mostrarLosUsuarios(char archivoUsuarios[]) // Mostrar todos los usuarios del Archivo
{
    FILE* buff = fopen(archivoUsuarios, "rb");
    stUsuario aux;

    if(buff)
    {
        while( (fread(&aux, sizeof(stUsuario), 1, buff)) > 0)
        {
            mostrarUsuario(aux);
            printf("\n");
        }
        fclose(buff);
    }
    else
    {
        printf("\nError.\n");
    }
}





///-----------------------------------------------------------Otros_Usuarios-----------------------------------------------------------///
void otrosUsuarios(char archivoUsuarios[]) //Ver otros usuarios (buscar o lista)
{
    int opcion;
    stUsuario* arregloUsuarios;
    int validos = pasarUsuariosAArregloDinamico(&arregloUsuarios, archivoUsuarios); //llamar funcion de pasar registros de archivo a arreglo dinamico

    do
    {
        printf(VERDE_T"<===== Otros usuarios =====>\n\n"RESET_COLOR);
        printf(CYAN_T" ( Buscar jugador         = 1 )\n");
        printf(" ( Ver lista de jugadores = 2 )\n");
        printf(" ( Regresar               = 0 )\n\n"RESET_COLOR);

        printf(" ( %cQue hacemos? ) ==> ",168);
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1: // Buscar jugador especifico
            printf(VERDE_T"<=======Buscar jugador========>\n\n"RESET_COLOR);
            verJugador(arregloUsuarios, validos);
            system("pause");
            system("cls");
            break;

        case 2: // Ver lista de jugadores completa
            listaDeJugadores(arregloUsuarios, validos);
            break;

        default:
            if (opcion != 0) //en caso de ingresar opcion invalida
            {
                printf("Error. Opcion invalida.\n\n");
                system("pause");
                system("cls");
            }
            break;
        }
    }
    while(opcion != 0); //cortar al ingresar 0 (regresar)
}

int pasarUsuariosAArregloDinamico(stUsuario** arregloUsuarios, char archivoUsuarios[]) //Crea arreglo dinamico para pasar usuarios
{
    int cantidadRegistros = contarRegistrosEnArchivo(archivoUsuarios);

    *arregloUsuarios = (stUsuario*)malloc(sizeof(stUsuario) * cantidadRegistros);

    int validos = copiarUsuarios(*arregloUsuarios, archivoUsuarios);

    return validos;
}

int contarRegistrosEnArchivo(char archivoUsuarios[]) //Cuenta la cantidad total de registros en el archivo
{
    int cantidadRegistros = 0;
    FILE* buff = fopen(archivoUsuarios, "rb");

    if(buff)
    {
        fseek(buff, 0, SEEK_END); //posicionar cursor al final
        cantidadRegistros = ftell(buff) / sizeof(stUsuario); //leer cantidad de bytes en archivo y dividirlo por tamaño de tipo de dato

        fclose(buff);
    }

    return cantidadRegistros;
}

int copiarUsuarios(stUsuario arregloUsuarios[], char archivoUsuarios[]) //Pasa los usuarios del archivo al arreglo ya creado
{
    stUsuario usuario;
    int validos = 0;
    FILE* buff = fopen(archivoUsuarios, "rb");

    if(buff)
    {
        while( (fread(&usuario, sizeof(stUsuario), 1, buff)) >0)
        {
            arregloUsuarios[validos] = usuario; //copiar registro
            validos++; //avanzar en array
        }

        fclose(buff);
    }
    return validos;
}


///----------Buscar_Jugador----------///
void verJugador(stUsuario arregloUsuarios[], int validos) //Mostrar registro que el usuario ingresa (por nombre), o muestra msj de error si no existe
{
    int pos = 0; //posicion del registro en el archivo
    char nombreABuscar[DIM_NOM_CON];

    printf(CYAN_T" (Ingrese el nombre de usuario que desea buscar ) ==> "RESET_COLOR);
    fflush(stdin);
    gets(nombreABuscar);

    int flag = buscarJugador(arregloUsuarios, validos, nombreABuscar, &pos); //llamar funcion que busque el nombre de usuario ingresado

    if(flag == 1) //en caso de haberlo encontrado
    {
        printf("\n");
        infoDelUsuario(arregloUsuarios[pos]);
    }
    else //en caso de no haberlo encontrado
    {
        printf(ROJO_T"\nError. Usuario inexistente\n\n"RESET_COLOR);
    }
}

int buscarJugador(stUsuario arregloUsuarios[], int validos, char nombreABuscar[], int* pos) //Buscar un unico jugador segun nombre de usuario en un arreglo
{
    int flag = 0;
    int i = 0;

    while( (flag==0) && (i<validos) ) //repetir mientras siga habiendo validos, y no haya encontrado el nombre a buscar
    {
        if( (strcmpi(nombreABuscar, arregloUsuarios[i].nombre) ==0) && (arregloUsuarios[i].estado == 1) ) //si el usuario existe y esta activo, mostrarlo
        {
            flag = 1; //cortar ciclo while
            *pos = i; //guardar posicion del registro encontrado
        }
        i++; //avanzar en array
    }
    return flag;
}


///----------Lista_Jugadores----------///
void listaDeJugadores(stUsuario arregloUsuarios[], int validos) //Ver lista de jugadores validos (orden alfabetico o de mejor a peor puntaje)
{
    int opcion;
    do
    {
        printf(VERDE_T"<======= Lista de jugadores ========>\n\n"RESET_COLOR);
        printf(MAGENTA_T"\t Ordenar por...\n\n"RESET_COLOR);
        printf(CYAN_T" ( Orden alfabetico     = 1 )\n");
        printf(" ( Puntaje              = 2 )\n");
        printf(" ( Regresar             = 0 )\n"RESET_COLOR);

        printf("\n ( %cQue hacemos? ) ==> ",168);
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 1: // Buscar jugador especifico
            printf(VERDE_T"<======= Orden alfabetico ========>\n\n"RESET_COLOR);
            ordenacionSeleccionOrdenAlfabetico(arregloUsuarios, validos); //ordenar arreglo segun orden alfabetico
            mostrarListaJugadores(arregloUsuarios, validos); //mostrar lista
            system("pause");
            system("cls");
            break;

        case 2: // Ver lista de jugadores completa
            printf(VERDE_T"<======= Mejor a peor puntaje ========>\n\n"RESET_COLOR);
            ordenacionInsercionPorPuntaje(arregloUsuarios, validos); //ordenar arreglo de mejor a peor puntaje
            mostrarListaJugadores(arregloUsuarios, validos); //mostrar lista
            system("pause");
            system("cls");
            break;

        default:
            if (opcion != 0) //en caso de ingresar opcion invalida
            {
                printf("Error. Opcion invalida.\n\n");
                system("pause");
                system("cls");
            }
            break;
        }
    }
    while(opcion != 0); //cortar al ingresar 0 (regresar)
}

void ordenacionSeleccionOrdenAlfabetico(stUsuario arregloUsuarios[], int validos) //Ordenar arreglo por orden alfabetico (seleccion)
{
    int posMenor;
    stUsuario aux; //variable auxiliar para hacer el intercambio
    int i = 0;

    while(i < validos-1) //validos -1, ya que no hace falta comparar cuando quede un solo dato
    {
        posMenor = encontrarMenor(arregloUsuarios, validos, i); //llamar funcion para encontrar el menor dato
        //intercambio valores
        aux = arregloUsuarios[posMenor];
        arregloUsuarios[posMenor] = arregloUsuarios[i];
        arregloUsuarios[i] = aux;

        i++;
    }
}

int encontrarMenor(stUsuario arregloUsuarios[], int validos, int pos) //Buscar la posicion del menor dato (alfabeticamente) del arreglo
{
    char menor[DIM_NOM_CON];
    strcpy(menor, arregloUsuarios[pos].nombre); //para comparar valores con arreglo[0] en primera vuelta
    int posMenor = pos; //para guardar la pos del menor valor, comenzar con arreglo[0] para comparar con resto
    int i = pos+1; //para no comparar arregloUsuarios[pos], el cual se lo establece como el menor

    while(i < validos) //comparar todos los validos
    {
        if(strcmpi(menor, arregloUsuarios[i].nombre) >0) //si 'menor' es mayor a 'arregloUsuarios[i].nombre'...
        {
            strcpy(menor, arregloUsuarios[i].nombre); //en caso de cumplirse la condicion, modificar valores de 'menor' y 'posMenor'
            posMenor = i;
        }
        i++; //avanzar en el array
    }
    return posMenor;
}

void ordenacionInsercionPorPuntaje(stUsuario arregloUsuarios[], int validos) //Ordenar arreglo por puntaje (insercion)
{
    int i = 0;

    while(i < validos-1) //validos -1, ya que no hace falta comparar cuando quede un solo dato
    {
        insertar(arregloUsuarios,i,arregloUsuarios[i+1]); //funcion para insertar usuario de array desordenado en el subarreglo ordenado
                                                        //'arregloUsuario[i+1]' para comparar dato con el subarreglo ordenado
        i++; //avanzar en el array
    }
}

void insertar(stUsuario arregloUsuarios[], int i, stUsuario dato) //Insertar dato en sub-arreglo ordenado
{
    while(i >= 0 && dato.estadisticas.mejorPuntaje > arregloUsuarios[i].estadisticas.mejorPuntaje) //repetir mientras los puntajes del sub-arreglo ordenado sean menores que el dato a insertar
    {
        arregloUsuarios[i+1] = arregloUsuarios[i]; //pivoteo
        i--;
    }

    arregloUsuarios[i+1] = dato; //insertar dato en pos correcto del arreglo
}

void mostrarListaJugadores(stUsuario arregloUsuarios[], int validos) //Muestra la lista de jugadores en el orden seleccionado anteriormente
{
    for(int i=0; i<validos; i++)
    {
        if(arregloUsuarios[i].estado == 1) //mostrar solo si el usuario NO esta dado de baja
        {
            infoDelUsuario(arregloUsuarios[i]);
        }
    }
}




///-----------------------------------------------------------Puntuacion_Global-----------------------------------------------------------///
void puntuacionGlobal(char archivoUsuarios[]) //Funcion principal del ranking (top 5 mejores puntajes), llama a las demas funciones
{
    /*1- creo arreglo dinamico
    2- lo ordeno por puntaje (din)
    3- crear arreglo estatico
    4- pasar primeros cinco de din a est

    1- creo arreglo dinamico
    2- lo ordeno por puntaje (din)
    3- mostrarlo -> for(int i=0; i<TOP_JUGADORES; i++)*/

    stUsuario arregloRanking[TOP_JUGADORES]; //arreglo estatico para mostrar el ranking
    stUsuario* arregloUsuarios;

    int validosDin = pasarUsuariosAArregloDinamico(&arregloUsuarios, archivoUsuarios); //pasar registros de archivo a arreglo dinamico
    ordenacionInsercionPorPuntaje(arregloUsuarios, validosDin); //ordenar arreglo dinamico segun puntaje

    int validosRanking = cargarArregloRanking(arregloRanking, arregloUsuarios, validosDin);

    mostrarRankingRecursivo(arregloRanking, validosRanking);
}

int cargarArregloRanking(stUsuario arregloRanking[], stUsuario arregloUsuarios[], int validosDin) //Pasa los primeros cinco registros (si es que hay) del arr din a un arreglo estatico (dimension preestablecida)
{
    int validosRanking = 0;

    while( (validosRanking<TOP_JUGADORES) && (validosRanking<validosDin) ) //repetir mientras no se llegue a la dim del arreglo estatico (TOP_JUGADORES), y mientars haya registros en el arreglo din
    {
        arregloRanking[validosRanking] = arregloUsuarios[validosRanking]; //pasar registro a arreglo est
        validosRanking++;
    }

    return validosRanking;
}

void mostrarRankingRecursivo(stUsuario arregloRanking[], int validos) // Mostrar el ranking de manera recursiva
{

    if(0 == validos-1) //condicion de corte
    {
        printf(AMARILLO_T"\t %d%c\t %d"RESET_COLOR "\t %s\n  ", validos, 167, arregloRanking[validos-1].estadisticas.mejorPuntaje, arregloRanking[validos-1].nombre); //solucion trivial
        for (int i = 0; i < 40 ;i++)
        printf(AMARILLO_T"%c", 238);
        printf("\n"RESET_COLOR);
    }
    else
    {
        mostrarRankingRecursivo(arregloRanking, validos-1); //llamada recursiva (validos-1 -> acercamiento de corte)
        printf(AMARILLO_T"\t %d%c"RESET_COLOR CYAN_T"\t %d"RESET_COLOR "\t %s\n", validos, 167, arregloRanking[validos-1].estadisticas.mejorPuntaje, arregloRanking[validos-1].nombre); //solucion trivial
    }
}

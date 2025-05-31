#include <iostream>
#include <stdio.h>
#include <time.h>

const int N = 20;

struct fecha        //fecha de nacimiento
{
    int dia;
    int mes;
    int anio;
};

struct jugador      //datos del jugador
{
    long int CI;
    char nombre[N];
    char apellido[N];
    char alias[N];
    struct fecha nacimiento;
    bool activo;
    int saldo;
};

struct jugadores    //arreglo de jugadores
{
    struct jugador arrJu[N];
    int tope;
};

struct apuesta      //datos de la apuesta
{
    int valor_apuesta;
    int saldo;
    bool resultado;
    int player[N];
};

struct apuestas     //arreglo de las apuestas
{
    struct apuesta arrAp[N];
    int tope;
};


//CABEZALES


bool sonIguales(char a[], char b[]);    //funcion que compara dos strings

int existeAlias(char alias[], struct jugadores jug);    //funcion que busca un alias en el arreglo de jugadores y devuelve la posicion valida, si existe

void crearJugador(struct jugador &j);   //carga un jugador con sus datos personales

void imprimirJugador(struct jugador j); //imprime los datos de un jugador

void imprimirTodosJugadores(struct jugadores jug);  //imprime todos los jugadores del arreglo de jugadores

void altaJugador(char alias[], struct jugador j, struct jugadores &jug);    //da de alta un jugador

void bajaJugador(char alias[], struct jugadores &jug);      //da de baja un jugador

void modificarJugador(char alias[], struct jugadores &jug);     //modifica un jugador

void menuGestionUsuarios(char alias[], struct jugador j, struct jugadores &jug);    //menu de gestion de usuarios

void menuConsultas();       //menu de las consultas

void menuApuestas(int opcion, int &resultado, int &apuesta, int &saldo, int cantidadAciertos, bool &acertar, bool orgullo);        //menu de las apuestas

void imprimirTablero(); //procedimiento que imprime el tablero

void seleccionarJugada(int apuesta, int saldo, int &resultado);  //procedimiento para seleccionar la jugada

void resultadoJugada(int resultado, int opcion, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);  //actua segun el resultado del procedimiento anterior

void estafa(int opcion, int resultado, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);     //LA GRAN ESTAFA!

void imprimirResultado(int resultado, bool acertar, int saldo);  //imprime el resultado

void juego(int opcion, int &resultado, int &apuesta, int &saldo, int cantidadAciertos, bool &acertar, bool orgullo);    //EL JUEGO

//PROGRAMA PRINCIPAL
int main()
{
    /*struct jugador j;
    struct jugadores jug;
    char alias[N];

    crearJugador(j);
    imprimirJugador(j);
    altaJugador(alias, j, jug);
    imprimirTodosJugadores(jug);
    */

    char alias[N];
    struct jugador j;
    struct jugadores jug;

    int seleccion, opcion, resultado, apuesta, saldo, cantidadAciertos;
    bool acertar, orgullo;

    do
    {
        
        scanf("%d", &seleccion);
        switch(seleccion){
            case 1:
                menuGestionUsuarios(alias, j, jug);
                break;
            case 2:
                menuConsultas();
                break;
            case 3:
                menuApuestas();
            default:
                printf("4. Salir.\n");
        }
    } while (seleccion != 4);
    


    return 0;
}



//IMPLEMENTACIONES
void menuGestionUsuarios(char alias[], struct jugador j, struct jugadores &jug)
{
    int num;
    do
    {
        printf("\n\n-----Gestion de usuarios----- \n\n1. Alta de jugador.\n2. Baja de jugador.\n3. Modificacion de jugador.\n4. Volver.\n");
        printf("\n");
        printf("Seleccione 1, 2, 3 o 4 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1: altaJugador(alias, j, jug); 
                break;
            case 2: bajaJugador(alias, jug); 
                break;
            case 3: modificarJugador(alias, jug); 
                break;
            case 4: 
                printf("Volver.\n"); 
                break;
            default: 
                printf("Opcion invalida.\n");
        }

    } while(num != 4);

}

void menuConsultas()
{
    int num;
    do
    {
        printf("\n\n-----Consultas----- \n\n1. Listado de jugadores.\n2. Listado de todas las apuestas.\n3. Listado de apuestas por jugador.\n4. Volver.\n");
        printf("\n");
        printf("Seleccione 1, 2, 3 o 4 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1: listadoJugadores(); //FALTA HACER
                break;
            case 2: listadoTodasApuestas(); //FALTA HACER
                break;
            case 3: listadoApuestasJugador(); //FALTA HACER
                break;
            case 4: 
                printf("Volver.\n"); 
                break;
            default: 
                printf("Opcion invalida.\n");
        }

    } while(num != 4);
}

void menuApuestas(int opcion, int &resultado, int &apuesta, int &saldo, int cantidadAciertos, bool &acertar, bool orgullo)
{
    int num;
    do
    {
        printf("\n\n-----Apuestas----- \n\n1. Jugar.\n2. Volver.\n");
        printf("\n");
        printf("Seleccione 1 o 2 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1: juego(opcion, resultado, apuesta, saldo, cantidadAciertos, acertar, orgullo); 
                break;
            case 2:
                printf("Volver.\n"); 
                break;
            default: 
                printf("Opcion invalida.\n");
        }

    } while(num != 2);
}


bool sonIguales(char a[], char b[])
{
    int i=0;
    while((a[i]==b[i]) && (a[i]!='\0') && (b[i]!='\0'))
        i++;
    return ((a[i]=='\0') && (b[i]=='\0'));
}

int existeAlias(char alias[], struct jugadores jug)
{
    int i=0;
    while((i<=jug.tope) && (!sonIguales(alias, jug.arrJu[i].alias)))
        i++;
    return i;
}

//andres
//{pepe, juan, ana, pepita, ....}
//


void crearJugador(struct jugador &j)
{
    printf("Ingrese su CI: ");
    scanf("%d", &j.CI);
    printf("\n");
    printf("Ingrese su nombre, apellido y alias: ");
    scanf("%s %s %s", &j.nombre, &j.apellido, &j.alias);
    printf("\n");
    printf("Ingrese su fecha de nacimiento: ");
    scanf("%d %d %d", &j.nacimiento.dia, &j.nacimiento.mes, &j.nacimiento.anio);
    printf("\n");
    j.activo = true;
    j.saldo = 1000;
}

void imprimirJugador(struct jugador j)
{
    printf("CI: %d\n", j.CI);
    printf("nombre: %s\n", j.nombre);
    printf("apellido: %s\n", j.apellido);
    printf("alias: %s\n", j.alias);
    printf("fecha de nacimiento: %d/%d/%d\n", j.nacimiento.dia, j.nacimiento.mes, j.nacimiento.anio);
    printf("saldo: %d\n", j.saldo);
}

void imprimirTodosJugadores(struct jugadores jug)
{
    for (int i=0; i<=jug.tope; i++)
    {
        if(jug.arrJu[i].activo)             //imprime solo los jugadores activos
        {
            imprimirJugador(jug.arrJu[i]);
            printf("\n");
        }
    }
}

void altaJugador(char alias[], struct jugador j, struct jugadores &jug)
{
    scanf("%s", &alias);
    if (existeAlias(alias, jug) < jug.tope)
    {
        printf("Ese alias ya existe.\n");
        jug.arrJu[existeAlias(alias, jug)].activo = true;
    }
    else
    {
        jug.tope++;
        jug.arrJu[jug.tope] = j;
        printf("Nuevo jugador ingresado.\n");
    }
}

void bajaJugador(char alias[], struct jugadores &jug)
{
    scanf("%s", &alias);
    if((existeAlias(alias, jug) < jug.tope) && (jug.arrJu[existeAlias(alias, jug)].activo))
    {
        jug.arrJu[existeAlias(alias, jug)].activo = false;
        printf("Jugador dado de baja.\n");
    }
    else
        printf("El jugador ya estaba dado de baja.\n");
}

void modificarJugador(char alias[], struct jugadores &jug){ 
	//scanf("%s", &alias);
	if((existeAlias(alias, jug) <= jug.tope)){
		
		int i;
		/*printf("que datos quieres modificar?\n");
			printf("1-CI\n2-Nombre\n3-Apellido\n4-Fecha de Nacimiento\n5-Salir\n");
			scanf("%d",&i);*/

        int e = existeAlias(alias, jug);
		do{
			printf("1-CI\n2-Nombre\n3-Apellido\n4-Fecha de Nacimiento\n5-Salir\n");
			scanf("%d", &i);
			switch(i){
				case 1 :
					printf("Ingrese nueva cedula:\n");
					scanf("%d", &jug.arrJu[e].CI);
					break;
				case 2 :
					printf("Ingrese nuevo nombre:\n");
					scanf("%s", &jug.arrJu[e].nombre);
					break;	
				case 3 :
					printf("Ingrese nuevo apellido:\n");
					scanf("%s", &jug.arrJu[e].apellido);
					break;
				case 4:
					printf("Ingrese nueva fecha de nacimiento");
					scanf("%d %d %d", &jug.arrJu[e].nacimiento.dia, &jug.arrJu[e].nacimiento.mes, &jug.arrJu[e].nacimiento.anio);
			}	
			
		}while(i != 5);
	}else{
		printf("El alias ingresado no existe!\n");
	}
}

void juego(int opcion, int &resultado, int &apuesta, int &saldo, int cantidadAciertos, bool &acertar, bool orgullo){

    int opcion, resultado, apuesta;

    printf("Bienvenido/a, a continuacion comenzaremos a jugar.\n ");
    printf("Para cada jugada debes indicar con un '1', '2', o '3', en qué copa se encuentra la bola. Recuerda que también puedes optar por retirarte indicándolo con un '4'.\n");
    printf("Ahora dime, ¿cuánto dinero tienes disponible?\n");

    int saldo;
    scanf("%d", &saldo);

    int cantidadAciertos = 0;
    bool acertar = false;
    bool orgullo = false;

    do {
        imprimirTablero();
        scanf("%d", &opcion);

        if (opcion != 4) 
        {
            printf("Apuesta?\n");
            scanf("%d", &apuesta);

            seleccionarJugada(apuesta, saldo, resultado);

            if (cantidadAciertos < 2)
            {
                resultadoJugada(resultado, opcion, apuesta, saldo, cantidadAciertos, acertar);
                imprimirResultado(resultado, acertar, saldo);
            }
            else 
            {
                estafa(opcion, resultado, apuesta, saldo, cantidadAciertos, acertar);
                imprimirResultado(resultado, acertar, saldo);
            }

            orgullo = ((apuesta > 200) && !acertar);

        }

    } while (((opcion != 4) || orgullo) && saldo >= 50);

    if (opcion == 4)
        printf("Nos vemos la proxima.");
    else if (saldo < 50)
        printf("Para jugar hay que pagar amigo.");

}


void imprimirTablero(){
    printf("O O O\n");
    printf("1 2 3\n");
    printf("Copa?:\n");
}


void seleccionarJugada(int apuesta, int saldo, int &resultado){

    if ((saldo >= apuesta) && (saldo >= 50)){
        srand(time(NULL));
        resultado = (rand() % 3) + 1;
    }
    else 
        printf("Para jugar hay que pagar amigo.\n");

}


void resultadoJugada(int resultado, int opcion, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar){
    if ((opcion == resultado) && (cantidadAciertos < 2)){
        acertar = true;
        cantidadAciertos++;
        saldo = saldo + apuesta;
    }
    else {
        acertar = false;
        cantidadAciertos = 0;
        saldo = saldo - apuesta;
    }
}


void estafa(int opcion, int resultado, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar){
    acertar = false;
    cantidadAciertos = 0;
    resultado = (opcion % 3) + 1;
    saldo = saldo - apuesta;
}


void imprimirResultado(int resultado, bool acertar, int saldo){
    switch(resultado){
        case 1:
            printf(". O O\n");
            break;
        case 2:
            printf("O . O\n");
            break;
        case 3:
            printf("O O .\n");       
    }
    if (acertar)
        printf("Ha acertado. Saldo: %d\n", saldo);
    else
        printf("No ha acertado. Saldo: %d\n", saldo);
}


//bubbleSort(int arr[], int n)






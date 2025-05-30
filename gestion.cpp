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




//PROGRAMA PRINCIPAL
int main()
{
    struct jugador j;
    struct jugadores jug;
    char alias[N];

    crearJugador(j);
    imprimirJugador(j);
    altaJugador(alias, j, jug);
    imprimirTodosJugadores(jug);
    return 0;
}



//IMPLEMENTACIONES

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
    while((!sonIguales(alias, jug.arrJu[i].alias)) && (i<jug.tope))
        i++;
    return i;
}

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



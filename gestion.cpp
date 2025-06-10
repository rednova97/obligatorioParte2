#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int N = 40;

struct fecha        //fecha de nacimiento
{
    int dia;
    int mes;
    int anio;
};

struct apuesta      //datos de la apuesta
{
    int montoPorApuesta;       
    int saldoResultante;    //saldo resultante de cada apuesta
    int saldoActual;        //saldo luego de terminar
    bool resultado;         //resultado de cada apuestas
};

struct apuestas     //arreglo de las apuestas
{
    struct apuesta arrAp[N];
    int tope;
};

struct jugador      //datos del jugador
{
    long int CI;
    char nombre[N];
    char apellido[N];
    char alias[N];
    struct fecha nacimiento;
    bool activo;
    int saldo = 1000;
    struct apuestas listadoDeApuestas;
};

struct jugadores    //arreglo de jugadores
{
    struct jugador arrJu[N];
    int tope;
};




            //CABEZALES
bool sonIguales(char a[], char b[]);    //funcion que compara dos strings

int existeAlias(char alias[], struct jugadores jug);    //funcion que busca un alias en el arreglo de jugadores y devuelve la posicion valida, si existe

bool fechaValida(int dia, int mes, int anio); // valida la fecha 

bool cedulaValida(long int cedula); // valida la cedula 

void crearJugador(struct jugador &j);   //carga un jugador con sus datos personales

void imprimirJugador(struct jugador j); //imprime los datos de un jugador

void imprimirTodosJugadores(struct jugadores jug);  //imprime todos los jugadores del arreglo de jugadores

void altaJugador(struct jugador j, struct jugadores &jug);    //da de alta un jugador

void bajaJugador(char alias[], struct jugadores &jug);      //da de baja un jugador

void modificarJugador(char alias[], struct jugadores &jug);     //modifica un jugador

void menuGestionUsuarios(char alias[], struct jugador &j, struct jugadores &jug);    //menu de gestion de usuarios

void menuConsultas(char alias[], struct jugadores jug);       //menu de las consultas

void menuApuestas(char alias[], struct jugadores &jug, int &resultado, int &apuesta, int &saldo, bool &acertar, int x);

bool AmenorqueB(char a[], char b[]);        //compara dos strings y devuelve si a es menor alfabeticamente que b

void bubbleSort(int n, int indices[], struct jugadores jug);          //ordena dos strings alfabeticamente

void listadoJugadores(struct jugadores jug);                //imprime el listado de jugadores

void listadoApuestasJugador(char alias[], struct jugadores jug, int pos);    //imprime las apuestas por jugador

void listadoTodasApuestas(struct jugadores jug);        //imprime todas las apuestas de cada jugador

void imprimirTablero(); //procedimiento que imprime el tablero

void seleccionarJugada(int apuesta, int saldo, int &resultado, int x);  //procedimiento para seleccionar la jugada

void resultadoJugada(int resultado, int opcion, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);  //actua segun el resultado del procedimiento anterior

void estafa(int opcion, int resultado, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);     //LA GRAN ESTAFA!

void imprimirResultado(int resultado, bool acertar, int saldo);  //imprime el resultado

void juego(int x, int pos, struct jugadores &jug);    //EL JUEGO

//PROGRAMA PRINCIPAL
int main()
{
    

    char alias[N];
    struct jugador j;
    struct jugadores jug;

    int seleccion, resultado, apuesta, saldo, x;
    bool acertar;
    
    srand(time(NULL));
    x = rand();

    jug.tope = -1;

    do
    {
        printf("------MENU PRINCIPAL------\n\n1. Gestion de usuarios.\n2. Consultas.\n3. Apuestas.\n4. Salir.\n");
        scanf("%d", &seleccion);
        switch(seleccion){
            case 1:
                menuGestionUsuarios(alias, j, jug);
                break;
            case 2:
                menuConsultas(alias, jug);
                break;
            case 3:
                menuApuestas(alias, jug, resultado, apuesta, saldo, acertar, x);
                break;
            default:
                printf("4. Salir.\n");
        }
    } while (seleccion != 4);
    


    return 0;
}



//IMPLEMENTACIONES
void menuGestionUsuarios(char alias[], struct jugador &j, struct jugadores &jug)
{
    int num;
    do
    {
        printf("\n\n-----Gestion de usuarios----- \n\n1. Alta de jugador.\n2. Baja de jugador.\n3. Modificacion de jugador.\n4. Volver.\n");
        printf("\n");
        printf("Seleccione 1, 2, 3 o 4 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1: 
                printf("Cargue los datos de su jugador.\n");
                crearJugador(j);
                altaJugador(j, jug); 
                break;
            case 2: 
                printf("Ingrese el alias del jugador que desea dar de baja.\n");
                scanf("%s", alias);
                bajaJugador(alias, jug); 
                break;
            case 3: 
                printf("Ingrese el alias del jugador que desea modificar.\n");
                scanf("%s", alias);
                modificarJugador(alias, jug); 
                break;
            case 4: 
                printf("Volviendo...\n"); 
                break;
            default: 
                printf("Opcion invalida.\n");
        }

    } while(num != 4);

}

void menuConsultas(char alias[], struct jugadores jug)
{
    int num;
    do
    {
        printf("\n\n-----Consultas----- \n\n1. Listado de jugadores.\n2. Listado de todas las apuestas.\n3. Listado de apuestas por jugador.\n4. Volver.\n");
        printf("\n");
        printf("Seleccione 1, 2, 3 o 4 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1: listadoJugadores(jug);
                break;
            case 2: listadoTodasApuestas(jug); 
                break;
            case 3: 
            {
                printf("Ingrese el alias del jugador que desea ver sus apuestas: ");
                scanf("%s", alias);
                printf("\n");
                int pos = existeAlias(alias, jug);
                if (jug.arrJu[pos].listadoDeApuestas.tope == -1)
                    printf("Aun no ha jugado.\n");
                else
                    listadoApuestasJugador(alias, jug, pos); 
                break;
            }
            case 4: 
                printf("Volver.\n"); 
                break;
            default: 
                printf("Opcion invalida.\n");
        }

    } while(num != 4);
}

void menuApuestas(char alias[], struct jugadores &jug, int &resultado, int &apuesta, int &saldo, bool &acertar, int x)
{
    int num;
    do
    {
        printf("\n\n-----Apuestas----- \n\n1. Jugar.\n2. Volver.\n");
        printf("\n");
        printf("Seleccione 1 o 2 segun lo que desee hacer.\n");
        scanf("%d", &num);

        switch(num) {
            case 1:
            {
                printf("Ingrese su alias para jugar: ");
                scanf("%s", alias);
                int pos = existeAlias(alias, jug);
                if(pos <= jug.tope)
                {   
                    
                    juego(x, pos, jug); 
                }
                else
                    printf("Ese alias no existe o no se encuentra.\n");
                break;
            }
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


void crearJugador(struct jugador &j)
{
    
    printf("Ingrese su nombre, apellido y alias: ");
    scanf("%s %s %s", j.nombre, j.apellido, j.alias);
    printf("\n");
    printf("Ingrese su fecha de nacimiento: ");
    scanf("%d %d %d", &j.nacimiento.dia, &j.nacimiento.mes, &j.nacimiento.anio);
    while (!fechaValida(j.nacimiento.dia, j.nacimiento.mes, j.nacimiento.anio) )
    {
        printf("Ingrese una fecha valida\n");
        scanf("%d %d %d", &j.nacimiento.dia, &j.nacimiento.mes, &j.nacimiento.anio);
    }
    printf("\n");
    printf("Ingrese su CI: ");
    scanf("%ld", &j.CI);
    while (!cedulaValida(j.CI))
    {
        printf("Ingrese una cedula valida\n");
        scanf("%ld", &j.CI);
    }
    printf("\n");
    j.activo = true;
    j.saldo = 1000;
    j.listadoDeApuestas.tope = -1;
}

void imprimirJugador(struct jugador j)
{
    printf("CI: %ld\n", j.CI);
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

bool fechaValida(int dia, int mes, int anio)
{
    if((anio > 2025) || (anio) < 1900)
        return false;
    else if((mes < 1) || (mes) > 12)
        return false;
    else if ((dia > 31) || (dia <1))
        return false;
    else 
    {
        switch (mes)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return true;
                break;
            case 4: case 6: case 9: case 11:
                if(dia <= 30)
                    return true;
                else
                    return false;
                break;
            case 2: 
                if(dia > 29)
                    return false;
                else 
                    if(((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)))
                    return true;
                else if(dia == 29)
                    return false;
                else
                    return true;
        }
    }
}

bool cedulaValida(long int cedula)
{
    if((cedula >= 10000000) && (cedula<= 99999999))
        return true;
    else
        return false;
}

void altaJugador(struct jugador j, struct jugadores &jug)
{
    int pos = existeAlias(j.alias, jug);
    if (pos <= jug.tope)
    {
        printf("Ese alias ya existe.\n");
        if (!jug.arrJu[pos].activo)
        {
            jug.arrJu[pos].activo = true;
            printf("El jugador ha sido dado de alta (anteriormente inactivo).\n");
        }
        else
            printf("El jugador ya existe y esta activo. No se realizo ningun cambio.\n");
    }
    else
    {
        if (jug.tope < N - 1)                   // controlar si hay espacio en el arreglo
        {         
            jug.tope++;
            jug.arrJu[jug.tope] = j;
            printf("Nuevo jugador ingresado.\n");
        } else {
            printf("No hay espacio para mas jugadores.\n");
        }
    }
}

void bajaJugador(char alias[], struct jugadores &jug)
{
    int pos = existeAlias(alias, jug);    
    if((pos <= jug.tope) && (jug.arrJu[pos].activo))
    {
        jug.arrJu[pos].activo = false;
        printf("Jugador dado de baja.\n");
    }
    else
        printf("El jugador ya estaba dado de baja o no ha sido ingresado aun.\n");
}

void modificarJugador(char alias[], struct jugadores &jug){ 
	//scanf("%s", &alias);

    int pos = existeAlias(alias, jug);
	if(pos <= jug.tope){
		int i;
		do{
			printf("Digite el numero segun lo que desee hacer: \n\n1-Nombre\n2-Apellido\n3-Fecha de Nacimiento\n4-CI\n5-Salir\n");
			scanf("%d", &i);
			switch(i){
				case 1 :
					printf("Ingrese nuevo nombre:\n");
					scanf("%s", jug.arrJu[pos].nombre);
					break;	
				case 2 :
					printf("Ingrese nuevo apellido:\n");
					scanf("%s", jug.arrJu[pos].apellido);
					break;
				case 3 :
					printf("Ingrese nueva fecha de nacimiento");
					scanf("%d %d %d", &jug.arrJu[pos].nacimiento.dia, &jug.arrJu[pos].nacimiento.mes, &jug.arrJu[pos].nacimiento.anio);
					break;
				case 4:
                    printf("Ingrese nueva cedula:\n");
					scanf("%ld", &jug.arrJu[pos].CI);
			}	
			
		}while(i != 5);
	}else{
		printf("El alias ingresado no existe!\n");
	}
}

bool AmenorqueB(char a[], char b[])
{
    int i=0;
    while ((a[i]==b[i]) && (a[i]!='\0') && (b[i]!='\0'))
        i++;
    if ((a[i]=='\0') && (b[i]!='\0'))       //si entra a este if es porque ambos strings tienen sus primeras letras iguales y A es mas corto q B
        return true;    
    if ((a[i]!='\0') && (b[i]=='\0'))       //si entra a este if es porque ambos strings tienen sus primeras letras iguales y A es mas largo q B
        return false;          
    else                                    //si entra a este else es porque ambos strings son igual de largo y entonces hay que fijarse cual va primero alfabeticamente
        return (a[i] < b[i]);       
}

void bubbleSort(int n, int indices[], struct jugadores jug)
{
    int temp;
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-1; j++)
            if (!AmenorqueB(jug.arrJu[indices[j]].alias, jug.arrJu[indices[j+1]].alias))        //compara dos alias del arreglo de jugadores
            {
                temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
}

void listadoJugadores(struct jugadores jug)
{
    
    int indices[N];
    int cantActivos = 0;    //guardaremos la cantidad de jugadores activos

    for (int i=0; i<=jug.tope; i++)     //llenamos el arreglo de indices que luego vamos a usar en bubblesort
    {
        if (jug.arrJu[i].activo)
        {
            indices[cantActivos] = i;       //guardamos el indice del jugador activo
            cantActivos++;
        }
    }

    bubbleSort(cantActivos, indices, jug);  //ordenamos los alias de los jugadores activos

    for (int i=0; i< cantActivos; i++)
    {
        imprimirJugador(jug.arrJu[indices[i]]);
        printf("\n");
    }
    printf("\n");
}

void listadoApuestasJugador(char alias[], struct jugadores jug, int pos)
{

    if (pos > jug.tope)
        printf("Ese alias no existe.\n");
    else
    {
        printf("%s\n", jug.arrJu[pos].alias);
        for (int j=0; j<=jug.arrJu[pos].listadoDeApuestas.tope; j++)
        {
            printf("Aposto: %d\n", jug.arrJu[pos].listadoDeApuestas.arrAp[j].montoPorApuesta);
            if(jug.arrJu[pos].listadoDeApuestas.arrAp[j].resultado)
                printf("Acerto jugada.\n");
            else
                printf("No acerto.\n");
            printf("Saldo resultante: %d\n", jug.arrJu[pos].listadoDeApuestas.arrAp[j].saldoResultante);
        }
        printf("Saldo actual: %d\n", jug.arrJu[pos].listadoDeApuestas.arrAp[jug.arrJu[pos].listadoDeApuestas.tope].saldoActual);
        printf("\n");
    }
    
}

void listadoTodasApuestas(struct jugadores jug)
{
    for (int i=0; i<= jug.tope; i++)
    {
        if (jug.arrJu[i].listadoDeApuestas.tope == -1)
            printf("El jugador %s aun no ha jugado.\n", jug.arrJu[i].alias);
        else
            listadoApuestasJugador(jug.arrJu[i].alias, jug, i);
    }
    printf("\n");
}

void juego(int x, int pos, struct jugadores &jug)
{

    int opcion;

    printf("Bienvenido/a, a continuacion comenzaremos a jugar.\n ");
    printf("Para cada jugada debes indicar con un '1', '2', o '3', en qué copa se encuentra la bola. Recuerda que tambien puedes optar por retirarte indicandolo con un '4'.\n");

    int cantidadAciertos = 0;
    bool acertar;
    int apuesta, resultado;
    bool orgullo = false;


    do {
        imprimirTablero();
        scanf("%d", &opcion);

        if (opcion != 4) 
        {
            printf("Apuesta?\n");
            scanf("%d", &apuesta);

            seleccionarJugada(apuesta, jug.arrJu[pos].saldo, resultado, x);

            if (cantidadAciertos < 2)
            {
                resultadoJugada(resultado, opcion, apuesta, jug.arrJu[pos].saldo, cantidadAciertos, acertar);
                imprimirResultado(resultado, acertar, jug.arrJu[pos].saldo);
            }
            else 
            {
                estafa(opcion, resultado, apuesta, jug.arrJu[pos].saldo, cantidadAciertos, acertar);
                imprimirResultado(resultado, acertar, jug.arrJu[pos].saldo);
            }

            orgullo = ((apuesta > 200) && !acertar);

            
            jug.arrJu[pos].listadoDeApuestas.tope++;
            int i = jug.arrJu[pos].listadoDeApuestas.tope;
            jug.arrJu[pos].listadoDeApuestas.arrAp[i].montoPorApuesta = apuesta;
            jug.arrJu[pos].listadoDeApuestas.arrAp[i].resultado = acertar;
            jug.arrJu[pos].listadoDeApuestas.arrAp[i].saldoResultante = jug.arrJu[pos].saldo;
            jug.arrJu[pos].listadoDeApuestas.arrAp[i].saldoActual = jug.arrJu[pos].saldo;

        }

    } while (((opcion != 4) || orgullo) && jug.arrJu[pos].saldo >= 50);

    if (opcion == 4)
        printf("Nos vemos la proxima.\n");
    else if (jug.arrJu[pos].saldo < 50)
        printf("Para jugar hay que pagar amigo.\n");

}

void imprimirTablero(){
    printf("O O O\n");
    printf("1 2 3\n");
    printf("Copa?:\n");
}

void seleccionarJugada(int apuesta, int saldo, int &resultado, int x){

    if ((saldo >= apuesta) && (saldo >= 50)){
        resultado = (x % 3) + 1;
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









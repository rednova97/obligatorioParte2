#include <iostream>
#include <stdio.h>
#include <time.h>

void imprimirTablero(); //procedimiento que imprime el tablero

void seleccionarJugada(int apuesta, int saldo, int &resultado);  //procedimiento para seleccionar la jugada

void resultadoJugada(int resultado, int opcion, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);  //actua segun el resultado del procedimiento anterior

void estafa(int opcion, int resultado, int apuesta, int &saldo, int &cantidadAciertos, bool &acertar);     //LA GRAN ESTAFA!

void imprimirResultado(int resultado, bool acertar, int saldo);  //imprime el resultado


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



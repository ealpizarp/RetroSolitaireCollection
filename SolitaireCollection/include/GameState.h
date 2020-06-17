#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <iostream>
#include"ArrayStack.h"
#include"LinkedList.h"
#include"LinkedStack.h"
#include"ArrayList.h"
#include"DLinkedList.h"
#include"SolitarioS.h"
#include"Carta.h"
#include<string>
#include<time.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>
#include<limits>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Aqui se definen los valores de escaneo ASCII de cada caracter que se utiliza en esta clase

#define KEY_ONE 49
#define KEY_TWO 50
#define KEY_THREE 51
#define KEY_FOUR 52
#define KEY_FIVE 53
#define KEY_SIX 54
#define KEY_SEVEN 55
#define KEY_EIGHT 56
#define KEY_NINE 57
#define KEY_U 117
/*
=======================================================================================================================================================================================================
                                                                            Tecnológico de Costa Rica

                                                                    Proyecto Programado de Estructuras de Datos.
Autores:Eric Alpizar P.
        David González A.

Fecha de ultima modificación: 17/06/2020


Descripción de la clase:
El proposito de la clase es manejar todos los diferentes estados del modo de juego golf solitaire y todos sus funciones privadas
que se requieren para el funcionamiento correcto del juego. De la misma manera que el Spider Solitaire hace uso de diferentes
estructuras de datos vistas en clase tales como pilas, listas de arreglos y listas doblemente enlazadas.
=======================================================================================================================================================================================================
*/



class GameState
{
    public:
    GameState(){
    };


    ~GameState(){};

    /*
    Nombre del método: getPuntajeGolf()
    Descripción: Esta funcion se encarga de retornar el puntaje golf acumulado segun el numero de partida\
     donde se encuentre el jugador
    Salida: int
    Cambios dentro de la función: ninguno
    */
    int getPuntajeGolf(){
    return puntajeGolf;
    }

    /*
    Nombre del método: playGolfSolitaire()
    Descripción: Esta es la funcion mas extensa de esta clase, se encarga de inicializar todas las estructuras necesarias para
    el funcionamiento requerido, utiliza todos los metodos privados de esta clase, utiliza estructuras de control tales como el
    switch para manejar los diferentes casos. En esta funcion se realizan todas las salidas de texto que el usuario visualiza cuando
    esta jugando.
    Salida: void
    Cambios dentro de la función: Se realizan todas las manipulaciones necesarias en tiempo de ejcucion
    */
    void playGolfSolitaire(){

    srand(time(NULL));
    LinkedStack<int> DeckState;                     //Aqui inicializamos las pilas de registro que van a servir para la funcionalidad del undo
    LinkedStack<Carta> CardsState;
    LinkedStack<int> OpcRegister;


    int value = 0;
    ArrayList<int> TotalCards(52);                  //Aqui se hace la inicializacion del mazo de 52 cartas del cual vamos a estar sacando las cartas
    for(int j = 0; j< 13; j++){
    for(int i =0; i< 4; i++){
    TotalCards.insert(value);
    }
    TotalCards.goToPos(rand() % TotalCards.getSize());
    value+=1;
    }


    int size = 52;
    string symbols[4] = {"\u2665", "\u2663", "\u2666", "\u2660"};
    ArrayStack<Carta> pilas [7];                      //Se inicializa el arreglo de pilas que vamos a estar utilizando para las cartas mostradas
    for(int i = 0; i<7; i++){
    for(int j = 0; j< 5; j++){
    int pos = rand() % size;
    TotalCards.goToPos(pos);
    Carta tarjeta = Carta(TotalCards.remove(), symbols[rand()%3]);
    size--;
    pilas[i].push(tarjeta);
    }
    }


int opc = 0;                            //Se crean variables necesarias para el switch
int jugadas = 0;                      //Contador de jugadas por el usuario


TotalCards.goToPos(rand()%13);
int ValorActual = TotalCards.remove();      //Sacamos una carta del mazo del una carta para comenzar jugando
printDeck(pilas, ValorActual);

TotalCards.goToStart();
Carta cartaActual;
do{                                                            //Empezamos la estructura de control do{}while() para manejar una ronda de juego.

string randSimbol = symbols[rand()%3];      //Guardamos en la variable un simbolo aleatorio para la carta actual
gotoxy(24,27);

if(ValorActual == 10){
    cout<<"J";
}
else if(ValorActual == 11){
    cout<<"Q";
}
else if(ValorActual == 12){
    cout<<"K";
}
else if(ValorActual == 0){
    cout<<"A";
}

                        // Se imprimen las numeros de carta con simbologia especial
else{
cout<<ValorActual+1;
}
gotoxy(21,30);
cout<<randSimbol;
gotoxy(27, 30);
cout<<randSimbol;
gotoxy(32,31);
cout<<"Cartas restantes: "<<TotalCards.getSize();                   //Imprimimos cuantas cartas restantes quedan
gotoxy(32,29);
cout<<"Sacar Carta del mazo: 8";
gotoxy(32,28);
cout<<"Undo: u";
gotoxy(32,25);
cout<<"Digite su siguiente jugada en el teclado ";

gotoxy(32,27);
cout<<"Movimientos: "<<jugadas;

if(TotalCards.getSize() == 0 && verificarFinalJuego(ValorActual, pilas) || emptyStack(pilas)){
    setPuntajeGolf(calcularPuntaje(pilas,TotalCards));
    gotoxy(32, 33);
    cout<<"El juego ha terminado, su puntaje es de: "<< calcularPuntaje(pilas,TotalCards);
    opc = 9;
}


switch(getch()){                                  //Se genera un switch con la funcion getch() la cual recibe un char de la letra que se este apretando en el teclado
case KEY_ONE:
    if (verificarJugada(ValorActual, pilas, 0)){       //Verifica el movimiento que intenta realizar el jugador
        DeckState.push(ValorActual);                    //Registra con que valor se realizo el movimiento
        cartaActual = pilas[0].pop();                    //Saca la carta que se descarto del deck
        CardsState.push(cartaActual);                   //Registra  la carta que se saco del deck
        ValorActual = cartaActual.getNumero();    //Le asigna al al valor actual la carta que acaba de ser sacada por el jugador
        system("CLS");                                       //Limpia la pantalla
        printDeck(pilas, ValorActual);                  // Imprime todo, con la nuevas estructuras de datos actualizadas
        jugadas++;                                          //Suma el numero de jugadas
        OpcRegister.push(0);                             //Hace un registro de la opcion que se utilizo
    }
        else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }

    break;

case KEY_TWO:
    if (verificarJugada(ValorActual, pilas, 1)){
        DeckState.push(ValorActual);
        cartaActual = pilas[1].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(1);

    }
    else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }

    break;

case KEY_THREE:

      if (verificarJugada(ValorActual, pilas, 2)){
        DeckState.push(ValorActual);
        cartaActual = pilas[2].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(2);

    }
    else{

        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }
    break;



case KEY_FOUR:
        if (verificarJugada(ValorActual, pilas, 3)){
        DeckState.push(ValorActual);
        cartaActual = pilas[3].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(3);

    }
    else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }
    break;


case KEY_FIVE:

        if (verificarJugada(ValorActual, pilas, 4)){
        DeckState.push(ValorActual);
        cartaActual = pilas[4].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(4);

    }
    else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }
    break;

case KEY_SIX:
        if (verificarJugada(ValorActual, pilas, 5)){
        DeckState.push(ValorActual);
        cartaActual = pilas[5].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(5);

    }
    else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
    }
    break;

case KEY_SEVEN:
        if (verificarJugada(ValorActual, pilas, 6)){
        DeckState.push(ValorActual);
        cartaActual = pilas[6].pop();
        CardsState.push(cartaActual);
        ValorActual = cartaActual.getNumero();
        system("CLS");
        printDeck(pilas, ValorActual);
        jugadas++;
        OpcRegister.push(6);

    }
    else{
        gotoxy(32,26);
        cout<<"No es una jugada valida, intente otra";
        system("cls");
        printDeck(pilas, ValorActual);
    }
    break;

case KEY_EIGHT:
    if(TotalCards.getSize() == 0){
        gotoxy(32,26);
        cout<<"No hay mas cartas en el mazo disponibles";
        system("PAUSE");
        system("cls");
        printDeck(pilas, ValorActual);

    }
        else{
            TotalCards.goToPos(rand() % TotalCards.getSize());
            DeckState.push(ValorActual);
            ValorActual = TotalCards.remove();
            system("cls");
            printDeck(pilas, ValorActual);
            OpcRegister.push(12);
        }
        break;

case KEY_U:

     if((CardsState.getSize() == 0 && OpcRegister.getSize() == 0) || DeckState.getSize() == 0){     //Valida si hay Movimientos previos registrados
            gotoxy(32,26);
            cout<<"No hay movimientos previos registrados";
        }

      else if(OpcRegister.topValue() == 12){        //Condicion que se ejecuta si la ultima opcion registrada es sacar mazo de cartas
            ValorActual = DeckState.pop();             //El valor actual pasa a ser el valor actual anterior
            TotalCards.append(ValorActual);           //A el mazo le ingresamos la carta donde deshicimos el movimiento
            system("cls");
            printDeck(pilas, ValorActual);
            if (OpcRegister.getSize() != 0){
                OpcRegister.pop();                          //Sacamos de la pila la ultima opcion registrada
            }
        }

        else{
            pilas[OpcRegister.pop()].push(CardsState.pop());        //Se saca el registro de la ultima opcion y devuelve al deck la ultima carta que fue sacada
            ValorActual = DeckState.pop();                                 //El valor actual toma el ultimo valor registrado
            system("cls");
            printDeck(pilas, ValorActual);
            jugadas--;                                                              //Resta el numero de jugadas
        }

        break;


case KEY_NINE:
    opc = 9;
    break;

default:

    gotoxy(32,26);
    cout << "Porfavor escoja una opcion valida!" << endl;
    break;
}

}while(opc != 9);
gotoxy(32, 33);
cout<<"Gracias por jugar!"<<endl;

    }





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    private:


        bool VerificaTamPila(ArrayStack<Carta> pilas[]){
        for(int i =0; i<10; i++){
        if(pilas[i].getSize() == 0){
                return false;
        }
        }
        return true;
        }

      /*
    Nombre del método: VerificarJugada()
    Entradas: entero de valor actual, un arreglo de pilas de arreglos, un entero de posicion
    Descripción: En este metodo se realizan las verificaciones y validaciones necesarias para corroborar que la jugada
    que el jugador esta deseando hacer sea valida.
    Salida: Valor booleano
    Cambios dentro de la función: Se leen y comparan los datos de la pila respectiva con el valor actual.
    */
    bool verificarJugada(int ValorActual, ArrayStack<Carta> pilas[], int pos){
    if(pilas[pos].getSize() == 0){
        return false;
    }

    else if((ValorActual == 0 && pilas[pos].topValue().getNumero() == 1) || (ValorActual == 12 && pilas[pos].topValue().getNumero() == 0) || (ValorActual == 0 && pilas[pos].topValue().getNumero() == 12)){
          return true;
    }

    else if(((ValorActual == (pilas[pos].topValue().getNumero()-1))) || (ValorActual == (pilas[pos].topValue().getNumero()+1))){
       return true;
    }

    else{
       return false;
    }
}


      /*
    Nombre del método: verificaFinalJuego()
    Descripción: Esta funcion se encarga de revisar si el juego ya ha terminado.
    Salida: Valor booleano
    Cambios dentro de la función: Se hacen comparaciones y lectura de datos de el estado de la partida actual
    */

bool verificarFinalJuego(int ValorActual, ArrayStack<Carta> pilas[]){
    int contador = 0;                                                     //Se incializa un contador
    for (int i=0; i< 6; i++){
        if(verificarJugada(ValorActual, pilas, i)){                //Se verifica si hay alguna jugada valida que el jugador pueda realizar en todas las pilas
            return false;
        }
        else if(pilas[i].getSize() != 0){                              //Verifica si se da el caso de que todas las pilas esten vacias
            contador++;
        }
    }
    if(contador == 0){
        return true;
    }
            return true;
}

      /*
    Nombre del método: emptyStack()
    Descripción: Esta funcion se encarga de revisar si las pilas que conforman al deck estan vacias
    Salida: Valor booleano
    Cambios dentro de la función: Solo se leen y comparan datos
    */


bool emptyStack(ArrayStack<Carta> pilas[]){
 int contador = 0;
for (int i=0; i< 7; i++){
if(pilas[i].getSize() != 0){            //Revisa en todas las pulas existentes si su tamano es diferente a 0
            contador++;
        }
}
    if(contador == 0){
        return true;
    }
            return false;
}

  /*
    Nombre del método: calcularPuntaje()
    Descripción: Calcula el puntaje obtenido por el jugador segun cuantas cartas descarto, y si le quedaron
    cartas todavia disponibles en el mazo
    Salida: Valor entero
    Cambios dentro de la función: Se crea una variable donde se guardan los puntos, solo lee de las estructuras de datos
    no genera cambios.
    */

    int calcularPuntaje(ArrayStack<Carta> pilas[], ArrayList<int> TotalCards){
    int puntaje = 0;
    for(int i =0; i< 7; i++){
        puntaje += pilas[i].getSize();  //Suma la cantidad de cartas que esten en el deck
    }

    if(TotalCards.getSize() != 0){
        puntaje -= TotalCards.getSize();    //Si todavia existen cartas en el mazo, cuentan como un numero negativo
    }

    return puntaje;
}

  /*
    Nombre del metodo: read_input()
    Descripción: Este metodo se encarga de realizar validaciones cuando se le solicita un entero al usuario. Para este metodo nos
    basamos en el que esta publicado en StackOverflow https://stackoverflow.com/questions/16934183/integer-validation-for-input
    Salida: Valor entero
    Cambios dentro de la función: Se le hacen validaciones a lo que ha sido ingresado por el usuario.
    */


int read_input()
{
    int input = -1;
    bool valid= false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Opcion invalida porfavor reingrese la opcion." << endl;
        }
    } while (!valid);

    return (input);
}

    /*
    Nombre del metodo: printDeck()
    Parametros: Arreglo de pilas de arreglos, Entero del valor actual
    Descripción: En este metodo se hace la impresion de el deck con los valores actuales que
    tengan las estructuras de datos.
    Salida: void
    Cambios dentro de la función: Solo se leen los datos de las estructuras, no se realiza ningun cambio
    */

void printDeck (ArrayStack<Carta> pilas[], int ValorActual){
     string symbols[4] = {"\u2665", "\u2663", "\u2666", "\u2660"};
    cout<< R"(
     ██████╗  ██████╗ ██╗     ███████╗    ███████╗ ██████╗ ██╗     ██╗████████╗ █████╗ ██╗██████╗ ███████╗
    ██╔════╝ ██╔═══██╗██║     ██╔════╝    ██╔════╝██╔═══██╗██║     ██║╚══██╔══╝██╔══██╗██║██╔══██╗██╔════╝
    ██║  ███╗██║   ██║██║     █████╗      ███████╗██║   ██║██║     ██║   ██║   ███████║██║██████╔╝█████╗
    ██║   ██║██║   ██║██║     ██╔══╝      ╚════██║██║   ██║██║     ██║   ██║   ██╔══██║██║██╔══██╗██╔══╝
    ╚██████╔╝╚██████╔╝███████╗██║         ███████║╚██████╔╝███████╗██║   ██║   ██║  ██║██║██║  ██║███████╗
     ╚═════╝  ╚═════╝ ╚══════╝╚═╝         ╚══════╝ ╚═════╝ ╚══════╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝╚══════╝
)"<<'\n';

    int x = 20;
    for(int i =0; i<7; i++){
    pilas[i].print(x);              //Imprime el deck de cartas en pantalla
    x+=10;
    }

    x = 19;
    int y = 20;

for(int i = 0; i < 7; i++){
        gotoxy(x,y);
        x+= 10;
        cout<<"["<<i+1<<":"<<pilas[i].getSize()<<"]";           //Se realiza la impresion de las coordenadas
        gotoxy(x-10, 22);
        cout<<"opc: "<<i+1;                                                 //Se hacen las impresiones de las opciones
}
cout<< R"(
                    _________
                   |         |
                   |         |
                   |         |
                   |         |
                   |         |
                   |         |
                   |         |
                    ~~~~~~~~~

)"<<'\n';

gotoxy(22, 24);
cout<<"Actual";

gotoxy(32,30);
cout<<"Abandonar: 9";

Carta cartaActual;
string randSimbol = symbols[rand()%3];

gotoxy(21,30);
cout<<randSimbol;

gotoxy(27, 30);
cout<<randSimbol;


gotoxy(32,25);
cout<<"Digite su siguiente jugada: ";

}


    /*
    Nombre del metodo: SetPuntajeGolf()
    Parametros: Entero de puntajeGolf
    Descripción: Asigna al atributo privado puntajeGolf el valor acumulativo de cada partida
    Salida: void
    Cambios dentro de la función: Se le suma el puntaje de una partida, cada vez que es invocado el metodo
    */
void setPuntajeGolf(int puntajeGolf){
this->puntajeGolf += puntajeGolf;
}

int puntajeGolf = 0;                    //Declaracion de atributo privado de la clase


};

#endif // GAMESTATE_H

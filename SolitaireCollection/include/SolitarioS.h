#ifndef SOLITARIOS_H
#define SOLITARIOS_H
#include <iomanip>//hace uso de setw(). Tabulador de la consola
#include <limits> // Se hace uso de numeric_limits<T>
#include "Stack.h"
#include "LinkedStack.h"
#include "ArrayList.h"
#include "time.h"//hace uso de rand()
#include "Gotoxy.h"
/*
=======================================================================================================================================================================================================
                                                                            Tecnológico de Costa Rica

                                                                    Proyecto Programado de Estructuras de Datos.
Autores:Eric Alpizar P.
        David González A.

Fecha de ultima modificación: 17/06/2020


Descripción de la clase:
SolitarioS es la clase principal encargada del funcionamiento y lógica del juego de solitario versión spider. Para el funcionamiento correcto de la clase SolitarioS
se hacen usos de otras clases creadas que contienen varias estructuras de datos como Listas Enlazadas, Pilas y ArrayList, A su vez utiliza bibliotecas del mismo lenguaje.
=======================================================================================================================================================================================================
*/


using namespace std;

class SolitarioS
{
private:
    ///////////////////////////////////////////////////////////////////////////////Atributos de la clase SolitarioS///////////////////////////////////////////////////////////////////////////////////////////
    Stack<LinkedList<int>*> *historialMazo;//guarda el mazo actual, para en un futuro devolverlo cuando se use retroceder
    Stack<LinkedList<int>**> *historialColumnas;//guarda las columnas para usarlas en un futuro cuando se use undo
    LinkedList<int>* mazo; // mazo que ejecuta el juego
    LinkedList<int>** columnas; // columnas que se ejecutan en el juego. //puntero a punteros de listas
    int noVisibles[10] = {5,5,5,5,4,4,4,4,4,4};//arreglo de enteros que indica cuantas cartas son la que estan boca abajo en cada columna.
    int historialNoVisibles[10] = {5,5,5,5,4,4,4,4,4,4};
public:
    ////////////////////////////////////////////////////////////////////////////////Métodos de la clase SolitarioS/////////////////////////////////////////////////////////////////////////////////////
    //Constructor
    //Inicializa las variables usando memoria dinámica
    SolitarioS()
    {
        historialMazo = new LinkedStack<LinkedList<int>*>();
        historialColumnas = new LinkedStack<LinkedList<int>**>();
        mazo = new LinkedList<int>();
        columnas = new LinkedList<int>*[10]; // arreglo de DlinkedList con las cartas
        //crea cada una de las 10 columnas que contienen LinkedList, las inicializa
        for(int i = 0; i < 10; i++)
        {
            columnas[i] = new LinkedList<int>();
        }
    }
    //Destructor
    //Elimina la memoria dinámica de las variables utilizadas
    ~SolitarioS()
    {
        delete historialMazo;
        delete [] historialColumnas;
        delete mazo;
        delete columnas;
    }

    /*
    Nombre del método: guardadEstado()
    Descripción: Función que se encarga de guardar el estado o historial de las cartas modificadas dentro del juego.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican las variables historialMazo, historialColumnas.
    */
    void guardarEstado()
    {
        historialMazo->push(mazo->clone());//Guarda el estado del mazo actual del juego
        LinkedList<int>** columnasClone = new LinkedList<int>*[10];//Se quiere hacer un clon que son 10 punteros a LinkedList
        //Ciclo for donde a cada uno de los elementos de columnasClone le asignamos el clone de una columna
        for(int i = 0; i < 10; i++)
        {
            columnasClone[i] = columnas[i]->clone();//guarda en cada uno de los elementos de columnasClone, un clon de la columna
            historialNoVisibles[i] = noVisibles[i];//guardo el estado de las cartas que son no visibles
        }
        historialColumnas->push(columnasClone);//Guardo la copia del estado de las columnas dentro de la pila llamada historialColumnas.
    }

    /*
    Nombre del método: crearBaraja()
    Descripción: Función que crea baraja de 2 naipes. Cada uno de 52 cartas.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican la variable mazo.
    */
    void crearBaraja()
    {
        //En el juego hay 2 naipes de 52 cartas
        for(int naipe = 0; naipe < 2; naipe++)
        {
            //Cada naipe esta conformado por 4 palos
            for(int palo = 0; palo < 4; palo++)
            {
                //Por cada palo se tienen 13 cartas.
                for(int carta = 1; carta < 14; carta++)
                {
                    //agregamos a mazo la carta.
                    mazo->append(carta);
                }
            }
        }
    }

    /*
    Nombre del método: barajar()
    Descripción: Función que revuelve las cartas dentro de mazo.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican la variable mazo.
    */
    void barajar()
    {
        srand(time(0));
        for(int i = 0; i < 200; i++)
        {
            mazo->goToPos(rand() % mazo->getSize());//del mazo de cartas se coloca en una posicion aleatoria
            mazo->append(mazo->remove());//en esa posicion aleatoria le inserta lo que se borra del mazo
        }
        mazo->goToPos(0); //me aseguro que la posicion del current regrese al inicio, ya que se ha estado moviendo para barajar.
    }

    /*
    Nombre del método: distribuir()
    Descripción: Función que distribuye las cartas en cada columnas.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican la variable mazo y columnas.
    */
    void distribuir()
    {
        //Las primeras 4 columnas se inicializan con 6 cartas
        for(int posicion = 0; posicion < 4; posicion++)
        {
            for(int cartas = 0; cartas <6; cartas++)
            {
                columnas[posicion]->insert(mazo->remove());//se saca del mazo una carta y esa se inserta en la columna.
            }
            columnas[posicion]->goToStart();
        }
        //Las restantes 6 columnas se inicializan con 5 cartas
        for(int posicion = 4; posicion < 10; posicion++)
        {
            for(int cartas = 0; cartas < 5; cartas++)
            {
                columnas[posicion]->insert(mazo->remove());//se sacan del mazo las cartas y se van insertando en las columnas correspondientes
            }
            columnas[posicion]->goToStart();//la posicion del current regresa al inicio de la lista LinkedList
        }
    }

    /*
    Nombre del método: inicializar()
    Descripción: Función que inicializa la baraja y comlumnas
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se llaman a las funciones crearVaraja, barajar, distribuir y guardarEstado.
    */
    void inicializar()
    {
        crearBaraja();
        barajar();
        distribuir();
        guardarEstado();
    }

    /*
    Nombre del método: repartirCartas()
    Descripción: Función que reparte del mazo de cartas, una carta a cada columna.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican las variables mazo y columnas, y se llama a la función guardarEstado.
    */
    void repartirCartas()
    {
        mazo->goToStart();
        //verifica si alguna de las columnas está vacía. Si está vacía no se pueden repartir cartas.
        for(int posicion = 0; posicion < 10; posicion++)
        {
            if(columnas[posicion]->getSize() == 0)
            {
                throw runtime_error("No se pueden repartir cartas. Hay columnas vacias");
            }
        }
        //Agrega a cada columna una carta nueva del mazo.
        for(int posicion = 0; posicion < 10; posicion++)
        {
            columnas[posicion]->goToStart();             //pongo el current al inicio de la lista doblemente enlazada, para que haga el insert del elemento en el inicio.
            columnas[posicion]->insert(mazo->remove());
        }
        //Guarda el estado del juego
        guardarEstado();
        cout << "JUGADA GUARDADA" << endl;
    }

    /*
    Nombre del método: escaleraCompleta()
    Descripción: Función que verifica si hay una escalera completa.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifica la variable columnas.
    */
    void escaleraCompleta()
    {
        //ciclo for para irme moviendo entre las columnas
        for(int posicion = 0; posicion < 10; posicion++)
        {
            int contador = 13; // para formar una escalera completa tienen que ser 13 cartas, por eso contador empieza en 13 y en el ciclo va verificando si es escalera, dentro del ciclo contador se va restando a 1
            if(columnas[posicion]->getSize() >= contador) // verifica que la columna tenga 13 o mas cartas, de lo contrario no puede haber una escalera completa
            {
                bool escalera = true;
                columnas[posicion]->goToPos(contador-1); // current apunta a la carta 13 de la columna
                //ciclo for para irme moviendo entre las cartas y verificar si existe alguna escalera completa.
                int cartaComparar = columnas[posicion]->getElement(); // se toma el elemento de la carta de "arriba"
                for(int i = contador; i > 1; i--)
                {
                    cartaComparar = columnas[posicion]->getElement();
                    columnas[posicion]->previous();//muevo el current a la carta de "abajo" ya que me servira para comparar: Carta de arriba con la carta de abajo
                    if(cartaComparar - columnas[posicion]->getElement() != 1)
                    {
                        escalera = false;
                        break;
                    }
                }
                if(escalera == true)
                {
                    //ciclo que va eliminando de la columna las 13 cartas que son escalera
                    for(int i = 0; i < 13; i++)
                    {
                        columnas[posicion]->remove();
                    }
                    cout << "ESCALERA COMPLETA" << endl;
                }
            }
        }
    }

    /*
    Nombre del método: mover()
    Descripción: Función que mueve las cartas entre columnas.
    Parámetros de entrada: tres números enteros, uno es la posición de la columna Origen, otro la posición de la columna a mover la carta y por último cantidad de cartas a mover
    Salida: void
    Cambios dentro de la función: Se modifica la variable columnas, se llaman a los métodos guardarEstado y escaleraCompleta.
    */
    //Método encargado de mover una o varias cartas de una columna a otra.
    void mover(int columnaOrigen, int columnaDestino, int cantidad)
    {
        //Validación de las posiciones de columnas
        if(columnaOrigen <= 0 || columnaOrigen > 10)
        {
            throw runtime_error("Columna origen incorrecta.");
        }
        if(columnaDestino <= 0 || columnaDestino > 10)
        {
            throw runtime_error("Columna destino incorrecta.");
        }

        //Validacion de que la cantidad de cartas sea correcta
        if(cantidad <= 0 || cantidad > columnas[columnaOrigen-1]->getSize())
        {
            throw runtime_error("Cantidad incorrecta de cartas");
        }

        //mover modifica las columnas
        columnas[columnaOrigen-1]->goToPos(cantidad-1); // me coloco en la posición donde hay la cantidad de cartas que el usuario solicitó para mover. Nota: la función goToPos empieza desde por ¿ 0, por eso se colocó (cantidad-1)

        //verifico si las cartas tienen alguna relacion de mini escalera entre ellas.
        bool escalera = true;   // nos sirve para comprobar si hay alguna escalera valida.
        int cartaComparar = columnas[columnaOrigen-1]->getElement();
        int cartaEnganche = cartaComparar;   //carta de enganche nos ayuda a verificar si la carta se puede unir a otra columna

        //se entra al ciclo si la cantidad de cartas a mover es mayor a 1
        for(int i = cantidad; i > 1; i--)
        {
            cartaComparar = columnas[columnaOrigen-1]->getElement();
            columnas[columnaOrigen-1]->previous();//me retrocedo para poder comparar la cartaComparar con la carta que le sigue
            if(cartaComparar - columnas[columnaOrigen-1]->getElement() != 1)
            {
                cout << " NO ES UNA ESCALERA." << endl;
                escalera = false;
                break;
            }
        }
        if(escalera != false)
        {
            columnas[columnaDestino-1]->goToStart();//Me aseguro que current esté apuntando al inicio, para que no tener problemas de que no encuentra elementos.

            //validar pasarse a otra columna
            if (columnas[columnaDestino-1]->getSize() == 0 || columnas[columnaDestino-1]->getElement() - cartaEnganche == 1)
            {
                cout << "APROBADO PARA CAMBIAR" << endl;
                for(int recorrerCartas = 0; recorrerCartas < cantidad; recorrerCartas++)
                {
                    columnas[columnaDestino-1]->insert(columnas[columnaOrigen-1]->remove());
                    columnas[columnaDestino-1]->next();
                }

                //cartas ocultas
                if(noVisibles[columnaOrigen-1] != 0)
                {
                    noVisibles[columnaOrigen-1]--;//al arreglo de cartas ocultas le resto uno, para que cuando imprima en pantalla muestre en pantalla el tope
                }
                columnas[columnaDestino-1]->goToStart();   //se coloca el current al inicio de la lista para insertar en esa posición
                columnas[columnaOrigen-1]->goToStart();
                guardarEstado();//Guarda el estado del juego, ya que hay cambios
            }else{
                cout << "NO SE PUEDE CAMBIAR" << endl;  //en este caso es cuando se escoge mover 1 carta y que esa carta no sea compatible con la carta que se encuentra en la posicion de llegada
            }
        }
        columnas[columnaDestino-1]->goToStart();//a la columna destino pongo al current apuntar al inicio por si alguna otra funcion necesita modificar esa columna

        //Método que se encarga de verificar si existiera alguna escalera completa en alguna de las columnas. En caso de que exista, la elimina de la columna.
        escaleraCompleta();
    }

    /*
    Nombre del método: deshacer()
    Descripción: Función que retrocede una jugada
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Se modifican toda mazo, columnas y noVisibles.
    */
    void deshacer()
    {
        //basta con escoger ya sea historialMazo o historialColumnas para verificar si esta alguna vacia
        if(historialMazo->isEmpty())
        {
            cout << "ESTADO INICIAL DEL JUEGO." << endl;
            throw runtime_error("Pila de estados vacia.");
        }else{
            delete mazo;//Borra el mazo viejo.
            mazo = historialMazo->pop();//al mazo le asigna el estado anterior que tenia el mazo de cartas

            //ciclo que va borrando el contenido de cada posicion del arreglo y a la vez va asignando las cartas no visibles
            for(int i = 0; i < 10; i++)
            {
                delete columnas[i];
                noVisibles[i] = historialNoVisibles[i];
            }
            delete []columnas; // borra el arreglo.
            columnas = historialColumnas->pop();
        }
    }


    /*
    Nombre del método: imprimirBaraja()
    Descripción: Función encargada de lo visual, imprime la baraja
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: No hay.
    */
    void imprimirBaraja()
    {
        //Representacion del mazo de cartas
        if(!mazo->atEnd())
        {
            cout << "Cartas restantes: " << mazo->getSize();
            cout << R"(
         ________
        |        |
        |        |
        |        |
        |        |
        |        |
        |        |
        |________|

        )" << '\n';
        }else{
            cout << "Cartas restantes: " << mazo->getSize();
            cout << R"(
         __    __
        |        |





        |__    __|

        )" << '\n';
        }
    }

    /*
    Nombre del método: escaleraCompleta()
    Descripción: Función visual, muestra en pantalla las columnas.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Hace llamada de la funcion print, la cuál es un método especial para el programa Solitario de la pila enlazada(LinkedStack).
    */
    void imprimirColumnas()
    {
        LinkedStack<int> pila;//se crea una pila que almacena los elementos de la columna para que los imprima de forma inversa en pantalla
        int coordenadaX = 25, coordenadaY = 20;//nos serviran para acomodar en la pantalla los elementos por medio del eje x and y.
        cout << "| "
             << left << setw(18) << "Numero de columna"
             << "|"
             << right << setw(5) << "1" << right << setw(5)
             << "|"
             << right << setw(5) << "2" << right << setw(5)
             << "|"
             << right << setw(5) << "3" << right << setw(5)
             << "|"
             << right << setw(5) << "4" << right << setw(5)
             << "|"
             << right << setw(5) << "5" << right << setw(5)
             << "|"
             << right << setw(5) << "6" << right << setw(5)
             << "|"
             << right << setw(5) << "7" << right << setw(5)
             << "|"
             << right << setw(5) << "8" << right << setw(5)
             << "|"
             << right << setw(5) << "9" << right << setw(5)
             << "|"
             << right << setw(5) << "10" << right << setw(5)
             << "|" << '\n';
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;


        for(int posicion = 0; posicion < 10 ; posicion++)
        {
            if(!columnas[posicion]->atEnd())
            {
                //mete dentro de la pila los elementos de las columnas
                for(columnas[posicion]->goToStart(); !columnas[posicion]->atEnd(); columnas[posicion]->next())
                {
                    pila.push(columnas[posicion]->getElement());//dentro de la pila se agregan los elementos de la columna[posicion]
                }
                columnas[posicion]->goToStart(); // se coloca current al inicio.
                cout << endl;
                //cartas ocultas
                ////metodo que imprime una columna, recibe la coordenada x de la pantalla, la coordenada y de la pantalla y la cantidad de cartas que no deben verse. Gracias a las coordenadas se pueden visualizar las columnas una al lado de otra
                pila.print2(coordenadaX, coordenadaY, noVisibles[posicion], columnas[posicion]->getSize());//es para imprimir las cartas ocultas y las no ocultas
                coordenadaX = coordenadaX + 10; // para poder visualizar las columnas una al lado de otra es necesario modificar la coordenada x, asi en este caso la siguiente impresion sera mas a la derecha de la pasada
            }else{
                //en caso de que la columna este vacia entonces nada mas imprime un espacio en blanco en la posicion de esa columna
                pila.print(coordenadaX, coordenadaY);//tambien se puede usar pila.print2...
                coordenadaX = coordenadaX + 10;//se modifica la coordenadaX para que a la siguiente llamada de la funcion print, esta imprima mas a la derecha la columna que le sigue.
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }

    /*
    Nombre del método: verificarGane()
    Descripción: Función que simplemente indica un mensaje al ganar el juego.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: no Hay.
    */
    //Método que indica si ganó el jugador
    void verificarGane()
    {
        bool gane = true;
        for(int posicion = 0; posicion < 10; posicion++)
        {
            if(!columnas[posicion]->atEnd())
            {
                gane = false;
            }
        }
        if(gane != false)
        {
            cout << "FELICIDADES, GANASTE!!! ''IMAGINA LAS CARTAS BRINCANDO''" << endl << endl << endl;
        }
    }

    /*
    Nombre del método: imprimirJuego()
    Descripción: Función visual, que llama a las funciones de imprimir cada contenido.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Hace llamada de la funcion imprimirBaraja, imprimirColumnas y verificarGane.
    */
    void imprimirJuego()
    {
        system("cls");//Pone la consola en negro, borrando cualquier visible cosa anterior
        //Título
        cout << R"(
                                              __           __
                                             (    '_/_ _  (    /'_/_ '_ _
                                            __)/)/(/(-/  __)()(/ /(/// (-
                                              /

        )";
        imprimirBaraja();
        imprimirColumnas();
        verificarGane();
    }

    /*
    Nombre del método: jugar()
    Descripción: Función encargada en llamar al método que inicializa el juego y a su vez es la encargada de la entrada del usuario.
    Parámetros de entrada: No recibe
    Salida: void
    Cambios dentro de la función: Hace llamada de la función inicializar, imprimirJuego, mover, repartirCartas, deshacer.
    */
    void jugar()
    {
        inicializar(); // Se inicializa la baraja, y las columnas con las cartas para jugar.
        bool ciclo = true;
        do{
            imprimirJuego();
            int opcion = 0;
            if(!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Opciones: " << endl;
            cout << "3. Repartir cartas." << endl;
            cout << "2. Deshacer." << endl;
            cout << "1. Continuar" << endl;
            cout << "99. Salir del juego." << endl;
            cin >> opcion;
            if(opcion == 3)
            {
                try{
                    repartirCartas();
                }
                catch(runtime_error e){
                    cout << "ERROR: " << e.what() << endl;
                }
                imprimirJuego();
            }
            if(opcion == 2)
            {
                try{
                    deshacer();
                }
                catch(runtime_error e){
                    cout << "ERROR: " << e.what() << endl;
                }
                imprimirJuego();

            }
            if(opcion == 99)
            {
                cout << "SALIENDO DEL JUEGO" << endl;
                break;
            }
            int origen = 0;
            int destino = 0;
            int cartas = 0;
            cout << "Indique Columna Origen: " << endl;
            cin >> origen;
            cout << "Indique Columna destino: " << endl;
            cin >> destino;
            cout << "Indique cantidad de cartas a mover: " << endl;
            cin >> cartas;
            try{
                mover(origen, destino, cartas);
            }
            catch(runtime_error e){
                cout << "ERROR: " << e.what() << endl;
            }
        }
        while(ciclo);
    }
};

#endif // SOLITARIOS_H

#ifndef GOTOXY_H
#define GOTOXY_H
#include<windows.h>
#include <iostream>
/*
=======================================================================================================================================================================================================
                                                                            Tecnológico de Costa Rica

                                                                Proyecto Programado de Estructuras de Datos.

Fecha de ultima modificación: 10/06/2020


Descripción de la clase:
La creacion de esta clase fue gracias el foro en stack overflow:
https://stackoverflow.com/questions/1670891/how-can-i-print-a-string-to-the-console-at-specific-coordinates-in-c
donde se muestra la utilizacion de la funcion gotoxy()
=======================================================================================================================================================================================================
*/


class Gotoxy
{
    public:

    void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
    }

    protected:

    private:
};

#endif // GOTOXY_H

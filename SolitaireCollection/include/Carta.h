#ifndef CARTA_H
#define CARTA_H
#include <iostream>

using namespace std;

class Carta
{
    public:

        Carta(int numero = 0, string simbolo = " ") {
        this->numero = numero;
        this->simbolo = simbolo;
        }
        ~Carta() {}


        friend ostream& operator<<(ostream& os, const Carta& other);


        int getNumero(){
            return numero;
        }
        void setNumero(int numero){
            this->numero=numero;
        }

        string getSimbolo(){
            return simbolo;
        }

        void setSimbolo(string simbolo){
            this->simbolo = simbolo;
        }

    private:
        int numero;
        string simbolo;
};


     ostream& operator <<(ostream& os, const Carta& other){
         if(other.numero == 10){
            os<< "J " <<other.simbolo<<"\n";
         }
         else if (other.numero == 11){
            os << "Q "<<other.simbolo<<"\n";
         }
         else if(other.numero == 12){
            os<<"K "<<other.simbolo<<"\n";
         }
         else if(other.numero == 0){
            os<<"A "<<other.simbolo<<"\n";
         }
         else{
        os << other.numero+1 << " "<< other.simbolo<<"\n";
         }
        return os;
        }

#endif // CARTA_H

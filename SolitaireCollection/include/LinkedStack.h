#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include"Node.h"
#include<iostream>

template <typename T>

class LinkedStack:  public Stack<T>
{
    private:
        Node<T> * top;
        int size;
    public:
        LinkedStack(){
        top = nullptr;
        size = 0;
        }
        ~LinkedStack(){
        clear();
        }
        void push(T element){
        top = new Node<T>(element, top);
        size++;
        }

        T pop(){
        if(size ==0){
            throw runtime_error("Stack underflow");
        }
        T result = top->element;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
        return result;
        }


        T topValue(){
        if(top == 0) throw runtime_error("Stack is empty");
        return top->element;
        }

        void clear(){
        Node<T> * temp;
        while(top != nullptr){
            temp = top;
            top = top->next;
            delete temp;
        }   }

        bool isEmpty(){
        return top==nullptr;
        }

        int getSize(){
        return size;
        }

        void print(){
        int SizeTopValue = size;
        Node<T>* temp = top;
        while(SizeTopValue > 0){
            std::cout<< top->element;
            top = top->next;
            SizeTopValue--;
        }
        std::cout<<std::endl;
        top = temp;
        }

          bool grouping(std::string symbols)
    {
        LinkedStack<char> S;
        int a = 0;
        int b = 0;
        for (int i = 0; i < symbols.length(); i++)
        {
            if(symbols[i] == '{' || symbols[i] == '[' || symbols[i] == '(')
            {
                S.push(symbols[i]);
                std::cout << "Agregando el caracter: " << symbols[i] << std::endl;
            }else{
                if (symbols[i] == '}' || symbols[i] == ']' || symbols[i] == ')')
                {
                    std::cout << "Comparando el caracter: " << symbols[i] << std::endl;
                    if (!S.isEmpty())
                    {
                        a = S.pop();
                        b = symbols[i];
                        if (a!=(b-1) && a!=b-2)
                        {
                            return false;
                        }
                    }else{
                        std::cout << "Stack is empty" << std::endl;
                        return false;
                    }
                }
            }
        }
        if (S.isEmpty())
        {
            return true;
        }
        std::cout << "Stack is not Empty." << std::endl;
        return false;
    }

        void print(int x){
        int SizeTopValue = size;
        Node<T>* temp = top;
         int y = 10;
        while(SizeTopValue > 0){
            gotoxy(x,y);
            std::cout<< top->element;
            top = top->next;
            SizeTopValue--;
            y = y + 2;
        }
        std::cout<<std::endl;
        top = temp;
        }

         void print(int x, int y)
    {
        Gotoxy go;
        if(!isEmpty())
        {
            go.gotoxy(x, y);
            std::cout<<" ";
        }

        while(!isEmpty())
        {
            go.gotoxy(x, y);
            std::cout<<pop();
            y = y+2;
        }
    }

    void print2(int x, int y, int ocultas, int columnaSize)
{
    Gotoxy go;
    if(!isEmpty())
    {
        go.gotoxy(x, y);
        std::cout<<" ";
    }
    int invisible = ocultas;
    if(ocultas == columnaSize)
    {
        invisible--;
    }
    while(!isEmpty())
    {
        go.gotoxy(x, y);
        if(invisible != 0)//mayor a 0 en caso de que nos pasen por parametro un -1.
        {
            std::cout<<"XXX";
            y = y+2;
            invisible--;
            pop();
        }else{
            std::cout<<pop();
            y = y+2;
        }
    }
}

   void printTopValues(int x) {};

};



#endif // LINKEDSTACK_H

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include "Stack.h"
#include<stdexcept>
#include"Gotoxy.h"

    void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
    }

using std::runtime_error;

template <typename T>

class ArrayStack:   public Stack<T>
{
private:
    int maxSize;
    int top;
    T * elements;

public:
    ArrayStack(int maxSize = 6)
    {
    this->maxSize = maxSize;
    this->elements = new T[maxSize];
    this->top = 0;
    }

    ~ArrayStack(){
    delete [] elements;
    }

    void push(T element){
    if(top == maxSize) {
        T* temp = new T[maxSize];
        temp = elements;
        top = 0;
        elements = new T[maxSize*2];
        for(int i =0; i < maxSize; i++){
            elements[i] = temp[i];
            top++;
        }
         maxSize = maxSize * 2;
    }
    elements[top] = element;
    top++;
    }

    T pop(){
    if(top==0){throw runtime_error("Stack underflow");}
    top--;
    return elements[top];
    }

    T topValue(){
    if (top==0) {throw runtime_error("Stack is empty");}
    return elements[top -1];
    }

    void clear(){
    top = 0;
    }

    bool isEmpty(){
    return top == 0;
    }

    int getSize(){
    return top;
    }

    void print(){
        int y = 10;
        int size = top-1;
        while(size >= 0){
            std::cout<<elements[size]<<std::endl;
            size--;
            y = y + 2;
        }
        std::cout<<std::endl;
    }

     void printTopValues(int x){
        int y = 7;
        int size = top-1;
        while(size >= 0){
           gotoxy(x,y);
           if(size == 0){
           // std::cout<<elements[top-1]<<std::endl;
           }
           else{
            std::cout<<"x"<<std::endl;
           }
            size--;
            y = y + 2;
        }
     }

    void print(int x){
     int y = 10;
        int size = top-1;
        int start = 0;
        while(size >= 0){
           gotoxy(x,y);
            std::cout<<elements[start]<<std::endl;
            start++;
            size--;
            y = y + 2;
        }
        std::cout<<std::endl;
    }


};


#endif // ARRAYSTACK_H

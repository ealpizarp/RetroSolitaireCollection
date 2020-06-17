#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#define MAX_SIZE 1024
#include"List.h"
#include<stdexcept>

using std::runtime_error;
template<typename T>

class ArrayList : public List<T>
{
    private:

    T* elements;
    int max;
    int pos;
    int size;

    public:

    ArrayList(int max = MAX_SIZE){
    if(max<=0){ throw runtime_error("Invalid max size");}
    elements = new T[max];
    this->max=max;
    pos=0;
    size=0;
    }

    void insert(T element){
    if(size==max){
    throw runtime_error("List is full");
    }
    for(int i=size; i>= pos; i--){
    elements[i]=elements[i-1];
    }
    elements[pos]=element;
    size++;
    }

    void append(T element){
    if(size==max){
    throw runtime_error("List is full");
    }
    elements[size]=element;
    size++;
    }

    T remove(){
    if(size==0){
        throw runtime_error("List is empty");
    }
    if(pos==size){
        throw runtime_error("No current element");
    }
    T res=elements[pos];
    for(int i=pos; i<size - 1; i++){
        elements[i]=elements[i+1];
    }
    size--;
    return res;
    }

    void clear(){
    size=pos;
    delete[] elements;
    elements = new T[max];
    }

    T getElement(){
    if(size==0){
        throw runtime_error("List is empty");
    }
    if(pos==size){
        throw runtime_error("No current element");
    }
    return elements[pos];
    }

    void goToStart(){
    pos=0;
    }

    void goToEnd(){
    pos=size;
    }

    void goToPos(int pos){
    if(pos<0 || pos>size){
    throw runtime_error("Index out of bounds");
    }
    this->pos=pos;
    }

    void next(){
    if(pos<size){
        pos++;
    }
    }

    void previous(){
    if(pos>0){
        pos--;
    }
    }

    bool atEnd(){
    return pos==size;
    }

    bool atStart(){
    return pos==0;
    }

    int getPos(){
    return pos;
    }

    int getSize(){
    return size;
    }

    bool contains(T element){
    for(int i=0; i<size; i++){
        if(elements[i]==element){
            return true;
        }
    }
    return false;
    }

    int indexOf(T element){                                                     //Preguntar si hay bronca que la posicion cambie al terminar el metodo
    if(!contains(element)){
        std::cout<<"Index out of range"<<std::endl;
        return -1;
    }
    goToStart();
    for(int i=0; i<size; i++){
        if(elements[i]==element){
            return pos;
        }
        pos++;
    }
    }

    void extend(ArrayList<T> * L){
    if(L->getSize() > max-size){
    throw runtime_error("Not enough space to add list");
    }
    for(int i=0; i< L->getSize(); i++){
    L->goToPos(i);
    elements[size]=L->getElement();
    size++;
    }
    }

    void Print(){
    for(int i=0; i<size; i++){
       std::cout<<elements[i]<<" ";
    }
    std::cout<<std::endl;
    }

    void print(int x){}

    void goToLastElement(){}




    ~ArrayList(){

    delete[] elements;

    }

};

#endif // ARRAYLIST_H

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "DNode.h"
#include <stdexcept>

using std::runtime_error;

template <typename T>

class DLinkedList : public List<T>
{
private:

    DNode<T> *head;
    DNode<T> *current;
    DNode<T> *tail;
    int size;

public:

    DLinkedList(){
    current = head = new DNode<T>();
    tail = head->next = new DNode<T>(nullptr,head);
    size=0;
    }

    void insert(T element){
    current->next=current->next->previous=new DNode<T>(element, current->next, current);
    size++;
    }

    void append(T element){
    tail->previous = tail->previous->next = new DNode<T>(element, tail, tail->previous);
    size++;
    }


    T remove(){
    if(size==0) {throw runtime_error("List is empty");}
    if (current->next==tail){ throw runtime_error("No current element");}

    T result = current->next->element;
    current->next=current->next->next;
    delete current->next->previous;
    current->next->previous=current;
    size--;
    return result;
    }

    void clear(){
    while(head->next != tail){
        current=head->next;
        head->next=current->next;
        delete current;
    }
    tail->previous=current=head;
    size=0;
    }

    T getElement(){

    if(size==0){throw runtime_error("List is empty");}
    if(current->next == tail){throw runtime_error("No current element");}
    return current->next->element;
    }

    void goToStart(){
    current=head;
    }

    void goToEnd(){
    current=tail->previous;
    }

    void goToLastElement(){
    current = tail->previous->previous;
    }

    void goToPos(int pos){
    if(pos<0 || pos>size){throw runtime_error("Index out of range");}
    current=head;
    for(int i=0; i<pos; i++){
        current=current->next;
    }
    }

    void next(){
    if(current->next != tail){
        current=current->next;
    }
    }

    void previous(){
    if(current != head){
        current=current->previous;
    }
    }

    bool atStart(){
    return current==head;
    }

    bool atEnd(){
    return current == tail->previous;
    }

    int getPos(){
    int pos=0;
    DNode<T>* temp=head;
    while(temp!=current){
        pos++;
        temp=temp->next;
    }
    return pos;
    }

    int getSize(){
    return size;
    }



    void sort(){

    if(size <= 1){
        std::cout<<"La lista ya esta ordenada!"<<std::endl;
    }
    else{


    DLinkedList<T> temp;
    DLinkedList<T> temp2;

    goToStart();
    T pivote = remove();
    goToStart();
    while(!atEnd()){

        if(getElement() < pivote){
            temp.append(remove());
        }
        else {
            temp2.append(remove());
        }
    }

    temp.sort();
    temp2.sort();

    clear();
    temp.goToStart();
    for(int i=0 ; i < temp.getSize(); i++){
    append(temp.getElement());
    temp.next();
    }
    append(pivote);
    temp2.goToStart();
    for(int i=0 ; i<temp2.getSize(); i++){
    append(temp2.getElement());
    temp2.next();
    }
    }
    }

        void print(int x){
        goToStart();
        int y = 19;
        while(current->next != tail){
            gotoxy(x,y);
            std::cout<<current->next->element;
            y = y+2;
            current=current->next;
        }
        }

};

#endif // DLINKEDLIST_H

#include "TextBuffer.h"

// ----------------- DoublyLinkedList -----------------
template <typename T>
element<T>::element(T data) {
    value = data;
    next = nullptr;
    prev = nullptr;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    element<T>* current = head;
    while(current){
        element<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
    element<T>* newEle = new element<T>(data);
    if(!head && !tail){
        head = newEle;
        tail = newEle;
        return;
    }
    newEle->prev = nullptr;
    newEle->next = head;
    head->prev = newEle;
    this->head = newEle;
    listSize++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data) {
    element<T>* newEle = new element<T>(data);
    if(!head && !tail){
        head = newEle;
        tail = newEle;
        return;
    }
    newEle->prev = tail;
    newEle->next = nullptr;
    tail->next = newEle;
    this->tail = newEle;
    listSize++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {
    if(index < 0 || index > listSize - 1){
        cout<<"out of range\n";
        return;
    }
    element<T>* newEle = new element<T>(data);
    if(index == 0) insertAtHead(data);
    else {
        element<T>* post = head;
        element<T>* previous = nullptr;
        for(int i = 0; i < index; i++)
            post = post->next;
        previous = post->prev;
        
        previous->next = newEle;
        newEle->prev = previous;
        post->prev = newEle;
        newEle->next = post;
        listSize++;
    }
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index) {
    if(index < 0 || index > listSize - 1){
        cout<<"out of range\n";
        return;
    }
    element<T>* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }

    element<T>* post = current->next;
    element<T>* previous = current->prev;
    if(previous)
        previous->next = post;
    else
        head = current;

    if(post)
        post->prev = previous;
    else
        tail = current;

    listSize--;
    delete current;
}
template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
    if(index < 0 || index > listSize - 1){
        cout<<"out of range\n";
        //return nullptr;
    }
    element<T>* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return (current->value);
};


// TODO: implement other methods of DoublyLinkedList

// ----------------- TextBuffer -----------------
TextBuffer::TextBuffer() {
    // TODO
}

TextBuffer::~TextBuffer() {
    // TODO
}

// TODO: implement other methods of TextBuffer

// ----------------- HistoryManager -----------------
TextBuffer::HistoryManager::HistoryManager() {
    // TODO
}

TextBuffer::HistoryManager::~HistoryManager() {
    // TODO
}

//TODO: implement other methods of HistoryManager

int main(){
    DoublyLinkedList<char> theList;
    //for(int i = 65; i <= 90; i++)
    theList.insertAtHead('s');
    theList.insertAtTail('a');
    theList.insertAtTail('a');
    theList.insertAtTail('a');
    theList.insertAt(0,'@');
    theList.insertAt(3,'2');
    theList.insertAt(5,'3');
    cout<<theList.get(0)<<" "<<theList.get(3)<<" "<<theList.get(4)<<" "<<theList.get(5)<<endl;
    theList.deleteAt(6);
    cout<<theList.get(5);
}
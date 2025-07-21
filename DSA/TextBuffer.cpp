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
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data) {

}

template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
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
    theList.insertAtHead('3');
    theList.insertAtTail('a');
    cout<<theList.get(1);
}
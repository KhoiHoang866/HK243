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
        listSize++;
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
        listSize++;
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
        throw out_of_range("Index is invalid!");
    }
    element<T>* newEle = new element<T>(data);
    if(!head && !tail){
        head = newEle;
        tail = newEle;
        listSize++;
        return;
    }
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
        throw out_of_range("Index is invalid!");
    }
    element<T>* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }

    element<T>* post = current->next;
    element<T>* previous = current->prev;
    if(previous)
        previous->next = post;
    else{
        head = post;
    }

    if(post)
        post->prev = previous;
    else
        tail = previous;

    listSize--;
    delete current;
}
template <typename T>
T& DoublyLinkedList<T>::get(int index) const {
    if(index < 0 || index > listSize - 1){
        throw out_of_range("Index is invalid!");
    }
    element<T>* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return (current->value);
};

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const {
    element<T>* current = head;
    int index = 0;
    while(current){
        if(current->value == item)
            return index; 
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const {
    return (indexOf(item) != -1);
}

template <typename T>
int DoublyLinkedList<T>::size() const {
    return this->listSize;
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
    element<T>* current = head;
    element<T>* hold = current->next;
    swap(head,tail);
    while(hold){
        hold = current->next;
        swap(current->next,current->prev);
        current = hold;
    }
}

string intToString(int value) {
    return to_string(value);
}
string intToString(double value) {
    return to_string(value);
}
string charToString(char& value) {
    return string(1,value);
}


template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T&)) const {
    stringstream s;
    s << "[";

    element<T>* current = head;
    while(current) {
        if(convert2str)
            s << convert2str(current->value);
        else 
            s << current->value;

        s << ((current->next != nullptr) ? ", " : "]");

        current = current->next;
    }

    return s.str();
}
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
    theList.insertAtHead('a');
    theList.insertAtTail('b');
    theList.insertAtTail('c');
    theList.insertAtTail('d');
    theList.insertAt(0,'1');
    theList.insertAt(3,'2');
    theList.insertAt(5,'3');
    for(int i = 0; i < 7; i++){
        cout<<theList.get(i)<<endl;
    }
    theList.deleteAt(4);
    cout<<"after del"<<endl;
    for(int i = 0; i < 6; i++){
        cout<<theList.get(i)<<endl;
    }
    theList.reverse();
    cout<<"after rev"<<endl;
    for(int i = 0; i < 6; i++){
        cout<<theList.get(i)<<endl;
    }
    cout<<theList.toString(charToString);

}
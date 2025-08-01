#include "TextBuffer.h"

// ----------------- DoublyLinkedList -----------------
template <typename T>
element<T>::element(T data) {
    value = data;
    next = nullptr;
    prev = nullptr;
};

// template <typename T>
// bool element<T>::operator<(const element<T>* other) const {
//     return this->value < other->value;
// }

// template <typename T>
// bool element<T>::operator>(const element<T>* other) const {
//     return this->value > other->value;
// }

// template <typename T>
// bool element<T>::operator==(const element<T>* other) const {
//     return this->value == other->value;
// }

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
    if(index < 0 || index > listSize){
        throw out_of_range("Index is invalid (ins) !");
    }
    element<T>* newEle = new element<T>(data);
    if(!head && !tail){
        head = newEle;
        tail = newEle;
        listSize++;
        return;
    }
    if(index == 0) insertAtHead(data);
    else if(index == listSize) insertAtTail(data);
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
        throw out_of_range("Index is invalid (del) !");
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
        throw out_of_range("Index is invalid (get) !");
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

        s << ((current->next != nullptr) ? ", " : "]\n");

        current = current->next;
    }

    return s.str();
}
// TODO: implement other methods of DoublyLinkedList

// ----------------- TextBuffer -----------------
TextBuffer::TextBuffer() {
    cursorPos = 0;
}

TextBuffer::~TextBuffer() {
    // TODO
}

void TextBuffer::insert(char c) {
    buffer.insertAt(cursorPos,c);
    moveCursorRight();
}

void TextBuffer::deleteChar() {
    buffer.deleteAt(cursorPos - 1);
    moveCursorLeft();
}

void TextBuffer::moveCursorLeft() {
    if(cursorPos == 0)
        throw cursor_error();
    else 
        cursorPos--;
}

void TextBuffer::moveCursorRight() {
    if(cursorPos == buffer.size())
        throw cursor_error();
    else 
        cursorPos++;
}

void TextBuffer::moveCursorTo(int index) {
    if(index < 0 || index > buffer.size())
        throw out_of_range("Index is invalid!");
    else
        cursorPos = index;
}

// Định dạng theo toString được không
string TextBuffer::getContent() const {
    return buffer.toString();
}

int TextBuffer::getCursorPos() const {
    return cursorPos;
}

int TextBuffer::findFirstOccurrence(char c) const {
    return buffer.indexOf(c);
}

int* TextBuffer::findAllOccurrences(char c, int &count) const {
    count = 0;
    int tempArr[buffer.size()];
    for(int i = 0; i < buffer.size(); i++){
        if(buffer.get(i) == c){
            tempArr[count++] = i;
        }
    }
    
    int* result = (count ? new int[count] : nullptr);
    for(int i = 0; i < count; i++){
        result[i] = tempArr[i];
    }
    return result;
}

void TextBuffer::deleteAllOccurrences(char c) {
    for(int i = 0; i < buffer.size(); i++){
        if(buffer.get(i) == c){
            buffer.deleteAt(i--);
        }
    }
}

// void merge(element<char>* begin, element<char>* mid, element<char>* end) {
//     int l_idx = begin;
//     int r_idx = mid + 1;
// }

// void mergeSort(int size, element<char>* begin, element<char>* end) {
//     if(begin >= end) return;
//     int mid = (begin + end) / 2;
//     mergeSort(head, begin, mid);
//     mergeSort(head, mid + 1, end);
//     merge(head, begin, mid, end);
// }

element<char>* partition__ (element<char>* start, element<char>* end){
    element<char>* pivot = end;
    element<char>* current = start;
    element<char>* mid = start->prev;

    while(current != end) {
        cout<<current->value<<endl;
        if(current->value <= pivot->value) {
            mid = (mid ? mid->next : start);
            swap(mid->value,current->value);
        }
        current = current->next;
    }
    mid = (mid ? mid->next : start);
    swap(mid->value,end->value);
    return mid;
}

void quickSort__ (element<char>* start, element<char>* end){
    if(start != end && start != end->next){
        element<char>* mid = partition__(start,end);
        quickSort__(start,mid);
        quickSort__(mid->next,end);
    }
}

bool smallOrEqual (char a, char b){
    if(isalpha(a) && isalpha(b)){
        return tolower(a) < tolower(b) || tolower(a) == tolower(b) && a <= b;
    }
    return a <= b;
}

int partition(DoublyLinkedList<char>* list, int begin, int end) {
    int pivot = list->get(end);
    int mid = begin - 1;
    for(int i = begin; i < end; i++){
        if(smallOrEqual(list->get(i), list->get(end))){
            swap(list->get(i), list->get(++mid));
        }
    }
    swap(list->get(end), list->get(++mid));
    return mid;
}

void quickSort(DoublyLinkedList<char>* list, int begin, int end) {
    if(begin < end){
        int mid = partition(list,begin,end);
        quickSort(list,begin,mid-1);
        quickSort(list,mid+1,end);
    }
}

void TextBuffer::sortAscending() {
    quickSort(&buffer,0,buffer.size()-1);
    cursorPos = 0;
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
    // DoublyLinkedList<char> theList;
    // //for(int i = 65; i <= 90; i++)
    // theList.insertAtHead('a');
    // theList.insertAtTail('2');
    // theList.insertAtTail('c');
    // theList.insertAtTail('d');
    // theList.insertAt(0,'1');
    // theList.insertAt(3,'2');
    // theList.insertAt(5,'3');
    // for(int i = 0; i < 7; i++){
    //     cout<<theList.get(i)<<endl;
    // }
    // theList.deleteAt(4);
    // cout<<"after del"<<endl;
    // for(int i = 0; i < 6; i++){
    //     cout<<theList.get(i)<<endl;
    // }
    // theList.reverse();
    // cout<<"after rev"<<endl;
    // for(int i = 0; i < 6; i++){
    //     cout<<theList.get(i)<<endl;
    // }
    // cout<<theList.toString(charToString);

    // for(int i = 0; i < 256; i++){
    //     cout<<(char)i<<endl;
    // }
    // return 0;


    TextBuffer note;
    note.insert('a');
    note.insert('c');
    note.insert('b');
    note.insert('d');
    note.insert('C');
    note.insert('A');
    note.insert('[');
    note.sortAscending();
    cout<<note.getContent();
    note.deleteAllOccurrences('c');
    cout<<note.getContent();
}
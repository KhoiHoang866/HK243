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
    undoTime = 0;
}

TextBuffer::~TextBuffer() {
    // TODO
}

void TextBuffer::insert(char c) {
    history.addAction("insert",cursorPos,c);
    buffer.insertAt(cursorPos,c);
    cursorPos++;
}

void TextBuffer::deleteChar() {
    history.addAction("delete",cursorPos,buffer.get(cursorPos - 1));
    buffer.deleteAt(cursorPos - 1);
    cursorPos--;
}

void TextBuffer::moveCursorLeft() {
    if(cursorPos == 0)
        throw cursor_error();
    else 
        history.addAction("move",cursorPos,'L');
        cursorPos--;
}

void TextBuffer::moveCursorRight() {
    if(cursorPos == buffer.size())
        throw cursor_error();
    else 
        history.addAction("move",cursorPos,'R');
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
    stringstream s;

    element<char>* current = this->buffer.head;
    int index = 0;
    bool cursorAdded = 0;
    while(current) {
        if(index == cursorPos) {
            s << "|";
            cursorAdded = 1; 
        }
        index++;
        s << current->value;
        current = current->next;
    }
    if(!cursorAdded) s << "|\n";
    else s<<'\n';

    return s.str();
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

bool smallOrEqual (char a, char b){
    if(isalpha(a) && isalpha(b)){
        return tolower(a) < tolower(b) || tolower(a) == tolower(b) && a <= b;
    }
    return a <= b;
}

void merge(DoublyLinkedList<char>* list, int begin, int mid, int end) {
    int l_idx = begin;
    int r_idx = mid + 1;
    int count = 0;
    char temp[end - begin + 1];
    while(l_idx <= mid && r_idx <= end){
        if (smallOrEqual(list->get(l_idx), list->get(r_idx))) {
            temp[count++] = list->get(l_idx);
            l_idx++;
        } else {
            temp[count++] = list->get(r_idx);
            r_idx++;
        }
    }
    while(l_idx <= mid) {
        temp[count++] = list->get(l_idx);
        l_idx++;
    }
    while(r_idx <= end) {
        temp[count++] = list->get(r_idx);
        r_idx++;
    }
    for(int i = 0; i < count; i++) {
        list->get(begin + i) = temp[i];
    }
}

void mergeSort(DoublyLinkedList<char>* list, int begin, int end) {
    if(begin >= end) return;
    int mid = (begin + end) / 2;
    mergeSort(list, begin, mid);
    mergeSort(list, mid + 1, end);
    merge(list, begin, mid, end);
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
    //quickSort(&buffer,0,buffer.size()-1);
    mergeSort(&buffer,0,buffer.size()-1);
    cursorPos = 0;
}

void strSeperator(string value, string& actName, int& cursor, char& character){
    actName = value.substr(1,value.find(',') - 1);
    cursor = stoi(value.substr(value.find(',') + 1,value.rfind(',') - value.find(',') - 1));
    character = value.substr(value.rfind(',') + 1, value.find(')') - value.rfind(',') - 1).at(0);
}
void TextBuffer::undo() {
    string data = history.actList.get(history.size()-1-undoTime);
    string actionName;
    int cursorPos;
    char character;
    strSeperator(data,actionName,cursorPos,character);
    
    if(actionName == "insert"){
        this->buffer.deleteAt(cursorPos);
        this->cursorPos--;
    }
    else if(actionName == "delete"){
        this->buffer.insertAt(cursorPos-1,character);
        this->cursorPos++;
    }
    else if(actionName == "move"){
        if(character == 'R')
            this->cursorPos--;
        else if (character == 'L')
            this->cursorPos++;
        else 
            cout<<"INVALID !"<<endl;
    } else
        cout<<"INVALID !"<<endl;

    undoTime++;
}
void TextBuffer::redo() {
    
}

// TODO: implement other methods of TextBuffer

// ----------------- HistoryManager -----------------
TextBuffer::HistoryManager::HistoryManager() {
    historySize = 0;
    historyPos = 0;
    cout<<"history list created"<<endl;
}

TextBuffer::HistoryManager::~HistoryManager() {
    cout<<"history list deleted"<<endl;
}

int TextBuffer::HistoryManager::size() const {
    return historySize;
}

void TextBuffer::HistoryManager::addAction(const string& actionName, int cursorPos, char c) {
    string s = "(" + actionName + "," + to_string(cursorPos) + "," + string(1,c) + ")";
    //xóa những action sau trước khi thêm action mới
    /////////
    //To do//
    /////////
    actList.insertAtTail(s);
    historySize++;
    historyPos++;

}

void TextBuffer::HistoryManager::printHistory() const {
    cout<<this->actList.toString();
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


    // TextBuffer note;
    // string chars = "gTrZaKGpBLmQbNwkXAeYcVoC";
    // for (char c : chars) {
    //     note.insert(c);
    // }
    // note.sortAscending();
    // cout<<note.getContent();
    // note.deleteAllOccurrences('c');
    // cout<<note.getContent();

    TextBuffer theList;
    cout<<theList.getContent();
    theList.insert('a');
    cout<<theList.getContent();
    theList.insert('b');
    cout<<theList.getContent();
    theList.insert('c');
    cout<<theList.getContent();
    theList.insert('d');
    cout<<theList.getContent();
    theList.insert('e');
    cout<<theList.getContent();
    theList.deleteChar();
    cout<<theList.getContent();
    theList.deleteChar();
    cout<<theList.getContent();
    theList.moveCursorLeft();
    cout<<theList.getContent();
    theList.deleteChar();
    cout<<theList.getContent();
    theList.undo();
    cout<<theList.getContent();
    theList.undo();
    cout<<theList.getContent();
    theList.undo();
    cout<<theList.getContent();


    theList.history.printHistory();



}
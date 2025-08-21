#ifndef __TEXT_BUFFER_H__
#define __TEXT_BUFFER_H__

#include "main.h"

template <typename T>
struct element {
    T value;
    element<T>* next;
    element<T>* prev;
    element(T data);
    // bool operator < (const element<T>* other) const ;
    // bool operator > (const element<T>* other) const ;
    // bool operator== (const element<T>* other) const ;
};

template <typename T>
class DoublyLinkedList {
public:
    element<T>* head;
    element<T>* tail;
    int listSize;
    // TODO: may provide some attributes

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAtHead(T data);
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    T& get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const;
    void reverse();
    string toString(string (*convert2str)(T&) = 0) const;
};

struct Action {
    string actionName;
    int cursorPos;
    char c;
    Action(string name, int pos, char ch){
        actionName = name;
        pos = cursorPos;
        c = ch;
    }
};

class TextBuffer {
private:
    DoublyLinkedList<char> buffer;
    int cursorPos;

    // TODO: may provide some attributes
    int undoTime;
public:
    TextBuffer();
    ~TextBuffer();

    void insert(char c);
    void deleteChar();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorTo(int index);
    string getContent() const;
    int getCursorPos() const;
    int findFirstOccurrence(char c) const;
    int* findAllOccurrences(char c, int &count) const;
    void sortAscending();
    void deleteAllOccurrences(char c);
    void undo();
    void redo();

public:
    class HistoryManager {
        int historySize;
        DoublyLinkedList<string>actList;
        int historyPos;
        // TODO: may provide some attributes

    public:
        friend class TextBuffer;

        HistoryManager();
        ~HistoryManager();

        void addAction(const string &actionName, int cursorPos, char c);
        void printHistory() const;
        int size() const;
        
        void strSeperator(string value, string& actName, int& cursor, char& character);
        void newHistory();
    };
    friend class TextBuffer::HistoryManager;
    HistoryManager history;
};

#endif // __TEXT_BUFFER_H__
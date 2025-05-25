// Файл MyStack.h
// Шаблонный класс MyStack на основе односвязного списка.
#ifndef MyStack_h           // защита от повторной компиляции
#define MyStack_h           // модуль подключен
#include<iostream>

// Шаблонный класс ListNode (узел односвязного списка)
template<class INF, class FRIEND>
class ListNode              // узел списка
{
private:
    INF d;                  // информационная часть узла
    ListNode *next;         // указатель на следующий узел списка
    ListNode(void) { next = nullptr; } //конструктор
    ListNode(INF d, ListNode* next) : d(d), next(next) {}
    friend FRIEND;
};

// Шаблонный класс MyStack на основе односвязного списка.
template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node *top;
public:
    MyStack(void);           // конструктор
    ~MyStack(void);          // освободить динамическую память
    MyStack(const MyStack&); // конструктор копирования
    MyStack& operator = (const MyStack&);   //operator =
    bool empty(void);        // стек пустой?
    bool push(INF n);        // добавить узел в вершину стека
    bool pop(void);          // удалить узел из вершины стека
    INF top_inf(void);       // считать информацию из вершины стека
    void free();             // освобождение стека
};

template<class INF>
MyStack<INF>::MyStack(): top(nullptr){
}

template<class INF>
MyStack<INF>::~MyStack(){
    free();
}

template<class INF>
MyStack<INF>::MyStack(const MyStack &obj): top(nullptr){
    MyStack<int> newStack;
    Node* tmp_node = obj.top;
    while (tmp_node) {
      //  n=obj;
        newStack.push(tmp_node->d);
        tmp_node = tmp_node ->next;
      //  ++obj;
    }
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator= (const MyStack &obj){
    free();
    MyStack<int> newStack;
    Node* tmp_node = obj.top;
    while (tmp_node) {
        newStack.push(tmp_node->d);
        tmp_node = tmp_node ->next;
    }
    return *this;
}

template<class INF>
bool MyStack<INF>::empty(void) {
    if (top == nullptr)
        return true;
    else
        return false;
}

template<typename INF>
bool MyStack<INF>::push(INF n) {
    Node* newTop = new Node(n, top);
    top = newTop;
    if (top==newTop)
        return true;
    else
        return false;
}

template<typename INF>
bool MyStack<INF>::pop() {
    if (top) {
        Node* temp = top;
        top = top->next;
        delete temp;
        return true;
    } else {
        return false;
    }
}

template<typename INF>
INF MyStack<INF>::top_inf() {
    if (top) {
        return top->d;
    }
    std::cout << "Попытка получения значения из пустого стека\n";
    throw 1;
}

template<typename INF>
void MyStack<INF>::free() {
    while (top) {
        pop();
    }
}

#endif

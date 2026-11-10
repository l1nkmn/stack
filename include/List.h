#ifndef __LIST_H__
#define __LIST_H__
template <class T>
struct Node {
    T val;
    Node<T>* prev;
    Node<T>* next;

    Node() : val(T()), prev(nullptr), next(nullptr) {}
    Node(T val) : val(val), prev(nullptr), next(nullptr) {}
};

template <class T>
class List {
public:
    Node<T>* head;
    Node<T>* tail;
    List(T val) : head(new Node<T>(val)), tail(head) {}
    void addNode(T val) {
        if (tail == nullptr) {
            head = new Node<T>(val);
            tail = head;
            return;
        }
        Node<T>* tmp = new Node<T>(val);
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
    void addNodeFront(const T& val) {
        if (head == nullptr) {
            head = new Node<T>(val);
            tail = head;
            return;
        }
        Node<T>* tmp = new Node<T>(val);
        tmp->next = head;
        head->prev = tmp;
        head = tmp;
    }

    void removeNode() {
        if (tail == nullptr) return;
        Node<T>* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
    }

    void removeNodeFront() {
        if (head == nullptr) return;
        Node<T>* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
    }

    ~List() {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            Node<T>* n = tmp->next;
            delete tmp;
            tmp = n;
        }
    }
};
#endif

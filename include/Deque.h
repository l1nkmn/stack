#include "List.h"

template <class T>
class Deque {
private:
    size_t size = 0;
    List<T>* deque = nullptr;
public:
    void push_back(const T& v) {
        if (deque == nullptr) {
            deque = new List<T>(v);
            size++;
            return;
        }
        deque->addNode(v);
        size++;
    }

    void push_front(const T& val) {
        if (deque == nullptr) {
            deque = new List<T>(val);
            size++;
            return;
        }
            deque->addNodeFront(val);
            size++;
        }

    T pop_back() {
        if (isEmpty())
            throw 1;
        T val = deque->tail->val;
        deque->removeNode();
        size--;
        return val;
    }

    T pop_front() {
        if (isEmpty())
            throw 1;
        T val = deque->head->val;
        deque->removeNodeFront();
        size--;
        return val;
    }

    bool isEmpty() {
        return size == 0;
    }
};

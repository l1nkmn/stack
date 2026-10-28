#include "List.h"

template <class T>
class Stack {
private:
    size_t size = 0;
    List<T>* stack = nullptr;
public:
    void push(T& v) {
        if (stack == nullptr) {
            stack = new List<T>(v);
            size++;
            return;
        }
        stack->addNode(v);
        size++;
    }
    T pop() {
        T val = stack->tail->val;
        stack->removeNode();
        size--;
        return val;
    }

    bool isEmpty() {
        return size == 0;
    }
};

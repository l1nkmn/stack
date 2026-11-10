#include "List.h"

template <class T>
class Queue {
private:
    size_t size = 0;
    List<T>* queue = nullptr;
public:
    void push(const T& v) {
        if (queue == nullptr) {
            queue = new List<T>(v);
            size++;
            return;
        }
        queue->addNode(v);
        size++;
    }

    T pop() {
        if (isEmpty())
            throw 1;
        T val = queue->head->val;
        queue->removeNodeFront();
        size--;
        return val;
    }

    bool isEmpty() {
        return size == 0;
    }
};

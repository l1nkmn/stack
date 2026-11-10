#include "List.h"

template <class T>
class Queue {
private:
    size_t size = 0;
    List<T>* queue = nullptr;
public:
    void push_back(const T& v) {
        if (queue == nullptr) {
            queue = new List<T>(v);
            size++;
            return;
        }
        queue->addNode(v);
        size++;
    }

    void push_front(const T& val) {
        if (queue == nullptr) {
            queue = new List<T>(val);
            size++;
            return;
        }
            queue->addNodeFront(val);
            size++;
        }

    T pop_back() {
        T val = queue->tail->val;
        queue->removeNode();
        size--;
        return val;
    }

    T pop_front() {
        T val = queue->head->val;
        queue->removeNodeFront();
        size--;
        return val;
    }

    bool isEmpty() {
        return size == 0;
    }
};

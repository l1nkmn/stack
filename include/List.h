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

    void removeNode() {
        if (tail == nullptr) return;
        Node<T>* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
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

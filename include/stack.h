template <class T, size_t sz>
class Stack {
private:
    T data[sz];
    size_t size = sz;
    int ind = 0;
public:
    void push(T& v) {
        if (ind == size)
            throw 2;
        data[ind++] = v;
    }
    T& pop() {
        if (ind < 0)
            throw 1;
        return data[ind--];
    }
}
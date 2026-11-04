#include <iostream>
#include "Stack.h"

int main() {
    Stack<int> st;
    for (int i = 0; i < 10; ++i)
        st.push(i);

    while (!st.isEmpty()) {
        std::cout << st.pop() << std::endl;
    }
}

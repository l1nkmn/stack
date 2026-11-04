#include <string>
#include <map>
#include <cctype>
#include "Stack.h"

class TArithmeticExpression {
private:
    std::string infix;                 // инфиксная запись
    std::string postfix;               // постфиксная запись

    int priority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    bool isOp(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isVar(char c) {
        return isalpha((unsigned char)c);
    }

    // перевод инфиксной записи в постфиксную
    // 0 - успех, иначе код ошибки
    int toPostfix() {
        postfix = "";
        Stack<char> st;
        char tmp;

        for (size_t i = 0; i < infix.size(); i++) {
            char c = infix[i];

            if (c == ' ') continue;

            if (isVar(c)) {
                postfix += c;
                postfix += ' ';
            }
            else if (c == '(') {
                tmp = c;
                st.push(tmp);
            }
            else if (c == ')') {
                while (!st.isEmpty()) {
                    tmp = st.pop();
                    if (tmp == '(') break;
                    postfix += tmp;
                    postfix += ' ';
                }
                if (tmp != '(')
                    return 1;   // скобки не сбалансированы
            }
            else if (isOp(c)) {
                while (!st.isEmpty()) {
                    tmp = st.pop();
                    if (tmp == '(') {
                        st.push(tmp);
                        break;
                    }
                    if (priority(tmp) >= priority(c)) {
                        postfix += tmp;
                        postfix += ' ';
                    }
                    else {
                        st.push(tmp);
                        break;
                    }
                }
                tmp = c;
                st.push(tmp);
            }
            else {
                return 2;   // непонятный символ
            }
        }

        while (!st.isEmpty()) {
            tmp = st.pop();
            if (tmp == '(')
                return 1;   // скобки не сбалансированы
            postfix += tmp;
            postfix += ' ';
        }

        if (!postfix.empty())
            postfix.pop_back();

        return 0;
    }

public:
    TArithmeticExpression() {}

    TArithmeticExpression(const std::string& s) {
        infix = s;
        toPostfix();
    }

    // 0 - успех, 1 - скобки, 2 - непонятный символ
    int setInfix(const std::string& s) {
        infix = s;
        return toPostfix();
    }

    std::string getInfix() {
        return infix;
    }

    std::string getPostfix() {
        return postfix;
    }

    // вычисление по постфиксной записи
    // vars - значения переменных, res - результат
    // 0 - успех, иначе код ошибки
    int calc(const std::map<char, double>& vars, double& res) {
        Stack<double> st;
        size_t i = 0;
        double a, b, val;
        char c;

        while (i < postfix.size()) {
            c = postfix[i];

            if (c == ' ') { i++; continue; }

            if (isVar(c)) {
                bool found = false;
                double value = 0;

                // проходим по map обычным for по диапазону
                for (const auto& p : vars) {
                    if (p.first == c) {
                        found = true;
                        value = p.second;
                        break;
                    }
                }

                if (!found)
                    return 3;   // переменная не задана

                val = value;
                st.push(val);
                i++;
            }
            else if (isOp(c)) {
                if (st.isEmpty())
                    return 4;
                b = st.pop();

                if (st.isEmpty())
                    return 4;
                a = st.pop();

                if (c == '+') val = a + b;
                else if (c == '-') val = a - b;
                else if (c == '*') val = a * b;
                else {
                    if (b == 0)
                        return 5;
                    val = a / b;
                }
                st.push(val);
                i++;
            }
            else {
                return 6;
            }
        }

        if (st.isEmpty())
            return 7;
        res = st.pop();
        if (!st.isEmpty())
            return 7;
        return 0;
    }
};

#include <iostream>
#include <cmath>
#include <stack>
#include <cctype>
using namespace std;
template <class T>
class OperatorADT {
public:
    T oper(char symb, T op1, T op2) {
        switch (symb) {
            case '+': return op1 + op2;
            case '-': return op1 - op2;
            case '*': return op1 * op2;
            case '/': return op1 / op2;
            case '^': return pow(op1, op2);
            default:
                cout << "Illegal operation\n";
                exit(1);
        }
    }
};
template <class T>
class PostfixADT {
    OperatorADT<T> op;  

public:
    T eval(char expr[]) {
        stack<T> st;
        char c;
        T op1, op2, value;

        for (int i = 0; (c = expr[i]) != '\0'; i++) {
            if (isdigit(c)) {
                st.push((T)(c - '0'));
            } else {
                op2 = st.top(); st.pop();
                op1 = st.top(); st.pop();

                value = op.oper(c, op1, op2);

                st.push(value);
            }
        }

        return st.top();
    }
};

int main() {
    char expr[100];
    cout << "Enter a postfix expression: ";
    cin >> expr;

    PostfixADT<double> evaluator;
    double result = evaluator.eval(expr);

    cout << "Result = " << result << endl;
    return 0;
}


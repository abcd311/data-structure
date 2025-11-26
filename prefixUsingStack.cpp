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
class PrefixADT {
    OperatorADT<T> op;

public:
    T eval(char expr[]) {
        stack<T> st;
        int len = 0;
        while (expr[len] != '\0') len++;

        char c;
        T op1, op2, value;
        for (int i = len - 1; i >= 0; i--) {
            c = expr[i];

            if (isdigit(c)) {
                st.push((T)(c - '0'));
            } else {  // operator
                op1 = st.top(); st.pop();
                op2 = st.top(); st.pop();
                value = op.oper(c, op1, op2);
                st.push(value);
            }
        }

        return st.top();
    }
};

// ******** MAIN ********
int main() {
    char expr[100];
    cout << "Enter a prefix expression: ";
    cin >> expr;

    PrefixADT<double> evaluator;
    double result = evaluator.eval(expr);

    cout << "Result = " << result << endl;
    return 0;
}

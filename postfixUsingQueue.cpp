#include <iostream>
#include <queue>
#include <cmath>
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
class PostfixQueueADT {
    OperatorADT<T> op;

public:
    T eval(char expr[]) {
        queue<T> q;
        char c;
        T op1, op2, value;

        for (int i = 0; (c = expr[i]) != '\0'; i++) {
            if (isdigit(c)) {
                q.push((T)(c - '0'));
            } else {
                if (q.size() < 2) {
                    cout << "Invalid Expression\n";
                    exit(1);
                }
                op1 = q.front(); q.pop();
                op2 = q.front(); q.pop();

                value = op.oper(c, op1, op2);

                q.push(value); 
            }
        }

        if (q.size() != 1) {
            cout << "Invalid Expression\n";
            exit(1);
        }

        return q.front();
    }
};

// ******** MAIN ********
int main() {
    char expr[100];
    cout << "Enter a postfix expression: ";
    cin >> expr;

    PostfixQueueADT<double> evaluator;
    double result = evaluator.eval(expr);

    cout << "Result = " << result << endl;

    return 0;
}

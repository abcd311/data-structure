#include <iostream>
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
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <class T>
class PrefixLLADT {
    OperatorADT<T> op;
    Node<T>* top;  // top of stack

public:
    PrefixLLADT() : top(nullptr) {}

    void push(T val) {
        Node<T>* n = new Node<T>(val);
        n->next = top;
        top = n;
    }

    T pop() {
        if (!top) {
            cout << "Stack Underflow\n";
            exit(1);
        }
        T val = top->data;
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    T eval(char expr[]) {
        // Find length of expression
        int len = 0;
        while (expr[len] != '\0') len++;

        T op1, op2, value;

        // Traverse from right to left
        for (int i = len - 1; i >= 0; i--) {
            char c = expr[i];

            if (isdigit(c)) {
                push((T)(c - '0'));
            } else {
                op1 = pop();
                op2 = pop();
                value = op.oper(c, op1, op2);
                push(value);
            }
        }

        return pop();
    }
};

// ******** MAIN ********
int main() {
    char expr[100];
    cout << "Enter a prefix expression: ";
    cin >> expr;

    PrefixLLADT<double> evaluator;
    double result = evaluator.eval(expr);

    cout << "Result = " << result << endl;
    return 0;
}

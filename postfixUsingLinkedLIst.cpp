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
class PostfixLLADT {
    OperatorADT<T> op;
    Node<T>* top;  // top of stack (head of linked list)

public:
    PostfixLLADT() : top(nullptr) {}

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
        char c;
        T op1, op2, value;

        for (int i = 0; (c = expr[i]) != '\0'; i++) {
            if (isdigit(c)) {
                push((T)(c - '0'));
            } else {
                op2 = pop();
                op1 = pop();
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
    cout << "Enter a postfix expression: ";
    cin >> expr;

    PostfixLLADT<double> evaluator;
    double result = evaluator.eval(expr);

    cout << "Result = " << result << endl;
    return 0;
}

#include <iostream>
#include <cmath>    // for pow()
#include <stack>    // for stack operations
#include <cctype>   // for isdigit()

using namespace std;

// Function to perform operation based on operator
double oper(char symb, double op1, double op2) {
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

// Function to evaluate postfix expression
double eval(char expr[]) {
    stack<double> opndstk;
    char c;
    double opnd1, opnd2, value;

    for (int position = 0; (c = expr[position]) != '\0'; position++) {
        if (isdigit(c)) {
            // Convert character to double and push it onto stack
            opndstk.push((double)(c - '0'));
        } else {
            // Operator case: pop two operands
            opnd2 = opndstk.top(); opndstk.pop();
            opnd1 = opndstk.top(); opndstk.pop();

            value = oper(c, opnd1, opnd2);

            // Push result back onto stack
            opndstk.push(value);
        }
    }

    // Final result
    return opndstk.top();
}

// Main function
int main() {
    char expr[100];
    cout << "Enter a postfix expression: ";
    cin >> expr;

    double result = eval(expr);
    cout << "Result = " << result << endl;

    return 0;
}

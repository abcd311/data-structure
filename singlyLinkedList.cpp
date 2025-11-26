#include<iostream>
using namespace std;
template <class T>
class Node {
public:
    T data;
    Node* next;

    Node(T el) {
        data = el;
        next = NULL;
    }
};

template <class T>
class SLL_ADT {
    Node<T>* head;

public:
    SLL_ADT() { head = NULL; }

    Node<T>* search(T x) {
        Node<T>* temp = head;
        while (temp != NULL) {
            if (temp->data == x)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void addtohead(T x);
    bool isempty();
    T removefromhead();
    void addtotail(T x);
    void addatposition(T el, int i);
    void removeAtPosition(int pos);
    void display();
};

template <class T>
void SLL_ADT<T>::addtohead(T x) {
    Node<T>* N = new Node<T>(x);
    if (isempty()) {
        head = N;
    } else {
        N->next = head;
        head = N;
    }
}

template <class T>
bool SLL_ADT<T>::isempty() {
    return head == NULL;
}

template <class T>
T SLL_ADT<T>::removefromhead() {
    if (!isempty()) {
        Node<T>* top = head;
        T val = top->data;
        head = head->next;
        delete top;
        return val;
    }
    cout << "List is empty, cannot remove!" << endl;
    return -1;
}

template <class T>
void SLL_ADT<T>::addtotail(T x) {
    Node<T>* N = new Node<T>(x);
    if (isempty()) {
        head = N;
    } else {
        Node<T>* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = N;
    }
}

template <class T>
void SLL_ADT<T>::addatposition(T el, int i) {
    if (i <= 1 || isempty()) {
        addtohead(el);
        return;
    }

    Node<T>* N = new Node<T>(el);
    Node<T>* temp = head;
    int cnt = 1;

    while (cnt < i - 1 && temp->next != NULL) {
        temp = temp->next;
        cnt++;
    }

    N->next = temp->next;
    temp->next = N;
}

template <class T>
void SLL_ADT<T>::removeAtPosition(int pos) {
    if (head == NULL) {
        cout << "List is empty!" << endl;
        return;
    }

    if (pos == 1) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<T>* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        cout << "Position out of range!" << endl;
        return;
    }

    Node<T>* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
}

template <class T>
void SLL_ADT<T>::display() {
    if (isempty()) {
        cout << "List is empty!" << endl;
        return;
    }

    Node<T>* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    SLL_ADT<int> list;   // now using template
    int choice, value;

    do {
        cout << "\n...Singly LinkedList Menu...\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at Position\n";
        cout << "3. Delete from Beginning\n";
        cout << "4. Delete from Position\n";
        cout << "5. Search Element\n";
        cout << "6. Display List\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the value to insert: ";
            cin >> value;
            list.addtohead(value);
            break;

        case 2: {
            cout << "Enter the value to insert: ";
            cin >> value;
            cout << "Enter the position to insert: ";
            int pos;
            cin >> pos;
            list.addatposition(value, pos);
            break;
        }

        case 3: {
            int removed = list.removefromhead();
            if (removed != -1)
                cout << "Removed element: " << removed << endl;
            break;
        }

        case 4: {
            cout << "Enter the position to remove: ";
            int rpos;
            cin >> rpos;
            list.removeAtPosition(rpos);
            break;
        }

        case 5: {
            cout << "Enter the element to search: ";
            int svalue;
            cin >> svalue;
            Node<int>* result = list.search(svalue);
            if (result != NULL) {
                cout << "Element " << svalue << " found at node address: " << result << endl;
            } else {
                cout << "Element " << svalue << " not found in the list." << endl;
            }
            break;
        }

        case 6:
            list.display();
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}

#include <iostream>
using namespace std;
template <class T>
class Node {
public:    
    T data;
    Node<T>* next;

    Node(T x) {
        data = x;
        next = nullptr;
    }
};

template <class T>
class CircularLinkedListADT {
private:
    Node<T>* cursor; 

public:
    CircularLinkedListADT() {
        cursor = nullptr;
    }

    bool isEmpty() {
        return cursor == nullptr;
    }

    void add(T x) {
        Node<T>* N = new Node<T>(x);

        if (isEmpty()) {
            cursor = N;
            N->next = cursor;
        } else {
            N->next = cursor->next;
            cursor->next = N;
            cursor = N;
        }
        cout << "Inserted: " << x << endl;
    }

    void remove(T x) {
        if (isEmpty()) {
            cout << "List is empty. Nothing to remove." << endl;
            return;
        }

        Node<T>* prev = cursor;
        Node<T>* curr = cursor->next;
        bool found = false;

        do {
            if (curr->data == x) {
                found = true;

                if (curr == cursor && curr == cursor->next) {
                    cursor = nullptr;
                } else {
                    prev->next = curr->next;
                    if (curr == cursor)
                        cursor = prev;
                }

                delete curr;
                cout << "Removed: " << x << endl;
                break;
            }

            prev = curr;
            curr = curr->next;

        } while (curr != cursor->next);

        if (!found)
            cout << "Element " << x << " not found in the list." << endl;
    }

    Node<T>* search(T x) {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return nullptr;
        }

        Node<T>* curr = cursor->next;
        do {
            if (curr->data == x)
                return curr;

            curr = curr->next;
        } while (curr != cursor->next);

        return nullptr;
    }

    void display() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* curr = cursor->next;
        cout << "Circular Linked List: ";
        do {
            cout << curr->data << " ";
            curr = curr->next;
        } while (curr != cursor->next);

        cout << endl;
    }
};

int main() {
    CircularLinkedListADT<int> list;
    int choice, x;

    do {
        cout << "\n--- Circular Linked List Menu ---\n";
        cout << "1. Insert Element\n";
        cout << "2. Remove Element\n";
        cout << "3. Search Element\n";
        cout << "4. Display List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to insert: ";
                cin >> x;
                list.add(x);
                break;

            case 2:
                cout << "Enter element to remove: ";
                cin >> x;
                list.remove(x);
                break;

            case 3:
                cout << "Enter element to search: ";
                cin >> x;
                {
                    Node<int>* found = list.search(x);
                    if (found)
                        cout << "Element " << x << " found at address: " << found << endl;
                    else
                        cout << "Element not found." << endl;
                }
                break;

            case 4:
                list.display();
                break;

            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

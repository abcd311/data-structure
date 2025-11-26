#include <iostream>
using namespace std;
template <class T>
class QueueADT {
    int front, rear, n;
    T* arr;

public:
    QueueADT(int size) {
        n = size;
        arr = new T[n];
        front = rear = -1;
    }

    ~QueueADT() { delete[] arr; }

    void enqueue(T x) {
        if ((rear + 1) % n == front) {
            cout << "Queue Overflow\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % n;
        arr[rear] = x;
    }

    T dequeue() {
        if (front == -1) {
            cout << "Queue Underflow\n";
            return -1;
        }
        T val = arr[front];
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % n;
        return val;
    }

    void display() {
        if (front == -1) {
            cout << "Queue is empty\n";
            return;
        }
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % n;
        }
        cout << "\n";
    }
};

int main() {
    int size;
    cout << "Enter queue size: ";
    cin >> size;

    // ---------- TEMPLATE USED WITH int ----------
    QueueADT<int> q(size);

    int choice, val;
    while (true) {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                q.enqueue(val);
                break;
            case 2:
                val = q.dequeue();
                if (val != -1)
                    cout << "Dequeued: " << val << endl;
                break;
            case 3:
                q.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}

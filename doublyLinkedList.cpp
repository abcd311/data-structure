#include<iostream>
using namespace std;
template <class T>
class Node{
public:
    T data;
    Node *next, *prev;

    Node(T el, Node *p, Node *n){
        data = el;
        next = n;
        prev = p;
    }
};

template <class T>
class DLL_ADT{
    Node<T>* head, *tail;

public:
    DLL_ADT(){
        head = NULL;
        tail = NULL;
    }

    void addtohead(T x);
    bool isempty();
    T removefromhead();
    void addtotail(T x);
    void removefromtail();
    void display();
};


template <class T>
void DLL_ADT<T>::addtohead(T x){
    Node<T>* N = new Node<T>(x, NULL, NULL);
    if(isempty()){
        head = tail = N;
    }
    else{
        head->prev = N;
        N->next = head;
        head = N;
    }
}

template <class T>
bool DLL_ADT<T>::isempty(){
    return (head == NULL && tail == NULL);
}

template <class T>
T DLL_ADT<T>::removefromhead(){
    if(!isempty()){
        Node<T>* temp = head;
        T val = temp->data;

        if(head->next != NULL){
            head->next->prev = NULL;
        } else {
            tail = NULL;
        }
        head = head->next;
        delete temp;
        return val;
    }
    else{
        cout<<"Underflow Error";
        return -1;
    }
}

template <class T>
void DLL_ADT<T>::addtotail(T x){
    Node<T>* N = new Node<T>(x, NULL, NULL);
    if(!isempty()){
        tail->next = N;
        N->prev = tail;
        tail = N;
    }
    else{
        head = tail = N;
    }
}

template <class T>
void DLL_ADT<T>::removefromtail(){
    if(!isempty()){
        Node<T>* temp = tail;

        if(tail->prev != NULL){
            tail->prev->next = NULL;
        } else {
            head = NULL;
        }

        tail = tail->prev;
        delete temp;
    }
    else{
        cout<<"Underflow Error";
    }
}

template <class T>
void DLL_ADT<T>::display(){
    if(!isempty()){
        Node<T>* temp = head;
        while(temp != NULL){
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << "NULL";
    }
}


int main(){
    DLL_ADT<int> list; 
    int choice, value;

    do{
        cout<<"\n...Doubly LinkedList Menu...\n";
        cout<<"1. Insert at Beginning\n";
        cout<<"2. Insert at Last\n";
        cout<<"3. Remove from beginning\n";
        cout<<"4. Remove from Last\n";
        cout<<"5. Display List\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the value to insert: ";
                cin>>value;
                list.addtohead(value);
                break;

            case 2:
                cout<<"Enter the value to insert: ";
                cin>>value;
                list.addtotail(value);
                break;

            case 3:
                list.removefromhead();
                break;

            case 4:
                list.removefromtail();
                break;

            case 5:
                list.display();
                break;

            case 6:
                cout<<"Exiting...\n";
                break;

            default:
                cout<<"Invalid Choice! Try again.\n";
        }
    } while(choice != 6);

    return 0;
}


#include <iostream>
using namespace std;
template <class T>
struct Node {
    T data;
    Node *left, *right;
};
template <class T>
Node<T>* newNode(T value) {
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}
template <class T>
class BST_ADT {
public:
    Node<T>* insert(Node<T>* root, T value);
    bool search(Node<T>* root, T key);
    Node<T>* deleteNode(Node<T>* root, T key);
    void inorder(Node<T>* root);
    void preorder(Node<T>* root);
    void postorder(Node<T>* root);
};

template <class T>
Node<T>* BST_ADT<T>::insert(Node<T>* root, T value) {
    Node<T>* node = newNode(value);

    if (root == NULL)
        return node;

    Node<T>* parent = NULL;
    Node<T>* temp = root;

    while (temp != NULL) {
        parent = temp;
        if (value < temp->data)
            temp = temp->left;
        else if (value > temp->data)
            temp = temp->right;
        else {
            cout << "Duplicate not allowed!\n";
            delete node;
            return root;
        }
    }

    if (value < parent->data)
        parent->left = node;
    else
        parent->right = node;

    return root;
}

template <class T>
bool BST_ADT<T>::search(Node<T>* root, T key) {
    while (root != NULL) {
        if (key == root->data)
            return true;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return false;
}

template <class T>
Node<T>* BST_ADT<T>::deleteNode(Node<T>* root, T key) {
    Node<T> *parent = NULL, *temp = root;

    while (temp != NULL && temp->data != key) {
        parent = temp;
        if (key < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (temp == NULL) {
        cout << "Element not found!\n";
        return root;
    }

    delete temp;
    return root;
}

template <class T>
void BST_ADT<T>::inorder(Node<T>* root) {
    Node<T>* pre;
    while (root != NULL) {
        if (root->left == NULL) {
            cout << root->data << " ";
            root = root->right;
        } else {
            pre = root->left;
            while (pre->right != NULL && pre->right != root)
                pre = pre->right;

            if (pre->right == NULL) {
                pre->right = root;
                root = root->left;
            } else {
                pre->right = NULL;
                cout << root->data << " ";
                root = root->right;
            }
        }
    }
}
template <class T>
void BST_ADT<T>::preorder(Node<T>* root) {
    Node<T>* pre;
    while (root != NULL) {
        if (root->left == NULL) {
            cout << root->data << " ";
            root = root->right;
        } else {
            pre = root->left;
            while (pre->right != NULL && pre->right != root)
                pre = pre->right;

            if (pre->right == NULL) {
                cout << root->data << " ";
                pre->right = root;
                root = root->left;
            } else {
                pre->right = NULL;
                root = root->right;
            }
        }
    }
}

template <class T>
void reversePrint(Node<T>* from, Node<T>* to) {
    if (from == to) {
        cout << from->data << " ";
        return;
    }
    reversePrint(from->right, to);
    cout << from->data << " ";
}

template <class T>
void BST_ADT<T>::postorder(Node<T>* root) {
    if (root == NULL) return;

    Node<T>* dummy = new Node<T>;
    dummy->left = root;
    dummy->right = NULL;

    Node<T>* pre = NULL;
    root = dummy;

    while (root != NULL) {
        if (root->left == NULL)
            root = root->right;
        else {
            pre = root->left;
            while (pre->right != NULL && pre->right != root)
                pre = pre->right;

            if (pre->right == NULL) {
                pre->right = root;
                root = root->left;
            } else {
                reversePrint(root->left, pre);
                pre->right = NULL;
                root = root->right;
            }
        }
    }

    delete dummy;
}

int main() {
    BST_ADT<int> bst;      
    Node<int>* root = NULL;
    int choice, value;

    do {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display Traversals\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = bst.insert(root, value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = bst.deleteNode(root, value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (bst.search(root, value))
                    cout << "Element found.\n";
                else
                    cout << "Element not found.\n";
                break;

            case 4:
                cout << "Inorder: ";
                bst.inorder(root);
                cout << "\nPreorder: ";
                bst.preorder(root);
                cout << "\nPostorder: ";
                bst.postorder(root);
                cout << endl;
                break;
        }

    } while (choice != 5);

    return 0;
}

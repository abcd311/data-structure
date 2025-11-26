#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
class AVLTreeADT {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int ht; // height of node

        Node(const T& val) : data(val), left(nullptr), right(nullptr), ht(1) {}
    };

    Node* root;

    // Helper functions
    int height(const Node* v) const { return v ? v->ht : 0; }

    void setHeight(Node* v) {
        if (v) {
            v->ht = 1 + max(height(v->left), height(v->right));
        }
    }

    bool isBalanced(const Node* v) const {
        if (!v) return true;
        int bal = height(v->left) - height(v->right);
        return (-1 <= bal && bal <= 1);
    }

    Node* tallChild(Node* z) const {
        if (height(z->left) >= height(z->right)) return z->left;
        else return z->right;
    }

    Node* tallGrandchild(Node* z) const {
        Node* y = tallChild(z);
        return tallChild(y);
    }

    Node* restructure(Node* x, Node* y, Node* z) {
        // Left-Left
        if (z->left == y && y->left == x) {
            z->left = y->right;
            y->right = z;
            setHeight(z);
            setHeight(y);
            return y;
        }
        // Right-Right
        if (z->right == y && y->right == x) {
            z->right = y->left;
            y->left = z;
            setHeight(z);
            setHeight(y);
            return y;
        }
        // Left-Right
        if (z->left == y && y->right == x) {
            y->right = x->left;
            z->left = x->right;
            x->left = y;
            x->right = z;
            setHeight(y);
            setHeight(z);
            setHeight(x);
            return x;
        }
        // Right-Left
        y->left = x->right;
        z->right = x->left;
        x->right = y;
        x->left = z;
        setHeight(y);
        setHeight(z);
        setHeight(x);
        return x;
    }

    Node* insert(Node* node, const T& val) {
        if (!node) return new Node(val);

        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        else return node; // duplicate not handled

        setHeight(node);

        if (!isBalanced(node)) {
            Node* y = tallChild(node);
            Node* x = tallChild(y);
            node = restructure(x, y, node);
        }

        return node;
    }

    bool search(const Node* node, const T& val) const {
        if (!node) return false;
        if (val == node->data) return true;
        else if (val < node->data) return search(node->left, val);
        else return search(node->right, val);
    }

    void inorder(const Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTreeADT() : root(nullptr) {}

    // Public ADT functions
    void insert(const T& k) { root = insert(root, k); }
    bool search(const T& k) const { return search(root, k); }
    void display() const {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }
};

// ************ MAIN ************
int main() {
    AVLTreeADT<int> avl;
    int choice, value;

    do {
        cout << "\n======AVL Tree Operations=======\n";
        cout << "1. Insert\n2. Search\n3. Display (Inorder)\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                avl.insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (avl.search(value)) cout << value << " found in the AVL tree.\n";
                else cout << value << " not found in the AVL tree.\n";
                break;
            case 3:
                avl.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

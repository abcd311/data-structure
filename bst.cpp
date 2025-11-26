#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

// Function to create a new node
Node* newNode(int value) {
    Node* temp = new Node;
    temp->data = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert an element (iterative, using only root)
Node* insert(Node* root, int value) {
    Node* node = newNode(value);

    if (root == NULL)
        return node;

    Node* parent = NULL;
    Node* temp = root;

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

// Search for an element (iterative)
bool search(Node* root, int key) {
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

// Find minimum value node
Node* findMin(Node* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete an element (iterative)
Node* deleteNode(Node* root, int key) {
    Node *parent = NULL, *temp = root;

    // Find the node to delete
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

// Inorder traversal 
void inorder(Node* root) {
    Node* pre;
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

// Preorder traversal (Morris-style, no recursion, no stack)
void preorder(Node* root) {
    Node* pre;
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

// Postorder traversal (simplified approach using Morris trick)
void postorder(Node* root) {
    if (root == NULL) return;

    Node* dummy = new Node;
    dummy->left = root;
    dummy->right = NULL;

    Node* pre = NULL;
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
                // Reverse print from root->left to pre
                Node* first = root->left;
                Node* second = pre;

                // Reverse path
                Node* x = first;
                Node* y = NULL;
                Node* z;
                while (x != second) {
                    z = x->right;
                    x->right = y;
                    y = x;
                    x = z;
                }

                z = x->right;
                x->right = y;

                // Print reversed
                Node* temp = x;
                while (temp != NULL) {
                    cout << temp->data << " ";
                    temp = temp->right;
                }

                // Restore path
                y = NULL;
                while (x != NULL) {
                    z = x->right;
                    x->right = y;
                    y = x;
                    x = z;
                }

                pre->right = NULL;
                root = root->right;
            }
        }
    }

    delete dummy;
}

// Main menu
int main() {
    Node* root = NULL;
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
                root = insert(root, value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Element found.\n";
                else
                    cout << "Element not found.\n";
                break;

            case 4:
                cout << "Inorder: ";
                inorder(root);
                cout << "\nPreorder: ";
                preorder(root);
                cout << "\nPostorder: ";
                postorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}

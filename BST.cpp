#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node *parent;

};

class BinarySearchTree {

public:
    Node *root = nullptr;

    Node* search(int data) const {
        Node *current = root;
        while (current != nullptr && current->data != data) {
            if (data > current->data) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
        return current;
    }

    void insert(const int data) {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->parent = nullptr;

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node *current = root;
        Node *parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            }
            else if (data > current->data) {
                current = current->right;
            }
            else {
                delete newNode;
                return;
            }

        }
        if (data > parent->data) {
            parent->right = newNode;
        }
        else {
            parent->left = newNode;
        }
        newNode->parent = parent;
    }

    void remove(const int data) {
        Node *found = search(data);

        if (found == nullptr) {
            return;
        }

        if (found->left == nullptr && found->right == nullptr) {
            if (found == root) {
                root = nullptr;
            }
            else {
                if (found == found->parent->left) {
                    found->parent->left = nullptr;
                }
                else {
                    found->parent->right = nullptr;
                }
            }
            delete found;
        }

        else if (found->left == nullptr ^ found->right == nullptr) {

            Node* subTree = (found->left != nullptr) ? found->left : found->right;

            if (found == root) {
                root = subTree;
            }
            else {
                if (found->parent->left == found) {
                    found->parent->left = subTree;
                }

                else {
                    found->parent->right = subTree;
                }

            subTree->parent = found->parent;
            delete found;

            }
        }

        else if (found->left != nullptr && found->right != nullptr) {
            Node* subTreeLeft = found->left;
            Node* subTreeRight = found->right;
            Node* successor = found->right;

            while (successor->left != nullptr) {
                successor = successor->left;
            }

            if (successor == subTreeRight) {
                subTreeLeft->parent = successor;
                if (found != root) {
                    if (found == found->parent->left) {
                        found->parent->left = successor;
                    }
                    else {
                        found->parent->right = successor;
                    }
                    successor->parent = found->parent;
                }
                else {
                    successor->parent = nullptr;
                }
                successor->left = subTreeLeft;
                return;
            }

            if (successor->right != nullptr) {
                successor->parent->left = successor->right;
                successor->right->parent = successor->parent;
            }
            else {
                successor->parent->left = nullptr;
            }

            if (found != root) {
                found->parent = successor->parent;
            }
            else {
                successor->parent = nullptr;
                root = successor;

            if (found->parent->left == found) {
                found->parent->left = successor;
            }
            else {
                found->parent->right = successor;
            }
            successor->left = subTreeLeft;
            successor->right = subTreeRight;

            }

            delete found;
        }

    }
};


int main() {
    Node *n1 = new Node();
    Node *n2 = new Node();
    Node *n3 = new Node();
    Node *n4 = new Node();
    Node *n5 = new Node();
    Node *n6 = new Node();
    Node *n7 = new Node();
    Node *n8 = new Node();
    Node *n9 = new Node();

    n1->data = 10;
    n2->data = 5;
    n3->data = 6;
    n4->data = 15;
    n5->data = 20;
    n6->data = 13;
    n7->data = 12;
    n8->data = 11;
    n9->data = 14;

    n1->left = n2;
    n1->right = n4;
    n2->right = n3;
    n4->right = n5;
    n4->left = n6;
    n6->left = n7;
    n6->right = n9;
    n7->left = n8;

    n2->parent = n1;
    n4->parent = n1;
    n3->parent = n2;
    n5->parent = n4;
    n6->parent = n4;
    n7->parent = n6;
    n8->parent = n7;
    n9->parent = n6;


    BinarySearchTree bst{};
    bst.root = n1;

    bst.remove(15);
    cout << bst.root->right->left->right->data << endl;



    return 0;
}



#include <iostream>
using namespace std;

struct Node {
    int cost;
    Node* left;
    Node* right;
};

class Stack {
public:
    int arr[100];
    int top;

    Stack() {
        top = -1;
    }

    void push(int x) {
        arr[++top] = x;
    }

    void pop() {
        if (top >= 0)
            top--;
    }
};

Stack s;

// Create new node
Node* createNode(int x) {

    Node* temp = new Node;

    temp->cost = x;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

// Check all paths starting from current node
void findPaths(Node* root, int target) {

    if (root == NULL)
        return;

    s.push(root->cost);

    int sum = 0;

    // Check all suffix paths ending at current node
    for (int i = s.top; i >= 0; i--) {

        sum = sum + s.arr[i];

        if (sum == target) {

            cout << "Path: ";

            for (int j = i; j <= s.top; j++) {
                cout << s.arr[j] << " ";
            }

            cout << endl;
        }
    }

    // Explore left and right children
    findPaths(root->left, target);
    findPaths(root->right, target);

    // Backtrack
    s.pop();
}

// Start a new path from every node
void checkEveryNode(Node* root, int target) {

    if (root == NULL)
        return;

    findPaths(root, target);

    checkEveryNode(root->left, target);
    checkEveryNode(root->right, target);
}

int main() {

    Node* root = createNode(10);

    root->left = createNode(5);
    root->right = createNode(3);

    root->left->left = createNode(2);
    root->left->right = createNode(3);

    root->right->right = createNode(7);

    int target = 15;

    cout << "Paths with sum " << target << ":\n";

    checkEveryNode(root, target);

    return 0;
}

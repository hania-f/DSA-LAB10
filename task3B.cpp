
#include <iostream>
using namespace std;

struct Node {
    int cost;
    Node* left;
    Node* right;
};

int arr[100];
int n = 0;

int subset[100];
int top = -1;

// Create node
Node* createNode(int x) {

    Node* temp = new Node;

    temp->cost = x;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

// Insert into BST
Node* insert(Node* root, int x) {

    if (root == NULL)
        return createNode(x);

    if (x < root->cost)
        root->left = insert(root->left, x);

    else
        root->right = insert(root->right, x);

    return root;
}

// Store BST values in sorted array
void inorder(Node* root) {

    if (root == NULL)
        return;

    inorder(root->left);

    arr[n] = root->cost;
    n++;

    inorder(root->right);
}

// Print current subset
void printSubset() {

    cout << "{ ";

    for (int i = 0; i <= top; i++) {
        cout << subset[i] << " ";
    }

    cout << "}" << endl;
}

// Backtracking
void findSubsets(int start, int sum, int target) {

    if (sum == target) {
        printSubset();
        return;
    }

    for (int i = start; i < n; i++) {

        // Pruning
        if (sum + arr[i] > target)
            return;

        // Choose
        top++;
        subset[top] = arr[i];

        // Explore
        findSubsets(i + 1, sum + arr[i], target);

        // Undo
        top--;
    }
}

int main() {

    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 18);

    inorder(root);

    int B = 22;

    cout << "Subsets with sum " << B << ":\n";

    findSubsets(0, 0, B);

    return 0;
}

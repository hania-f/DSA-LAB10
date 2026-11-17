
#include <iostream>
using namespace std;

struct Container {
    int id;
    int weight;
    Container* next;
};

struct Truck {
    int capacity;
    int index;
    Truck* next;
};

// Linked list of containers
Container* head = NULL;

// Queue of trucks
Truck* front = NULL;
Truck* rear = NULL;

// Store assigned container IDs
int assigned[50][50];
int containerCount[50] = {0};
int truckCount = 0;

// Insert container
void insertContainer(int id, int weight) {

    Container* temp = new Container;

    temp->id = id;
    temp->weight = weight;
    temp->next = NULL;

    if (head == NULL) {
        head = temp;
    }
    else {
        Container* p = head;

        while (p->next != NULL) {
            p = p->next;
        }

        p->next = temp;
    }
}

// Enqueue truck
void enqueue(int capacity) {

    Truck* temp = new Truck;

    temp->capacity = capacity;
    temp->index = truckCount;
    temp->next = NULL;

    if (front == NULL) {
        front = rear = temp;
    }
    else {
        rear->next = temp;
        rear = temp;
    }

    truckCount++;
}

// Calculate remaining container weight
int remainingWeight(Container* p) {

    if (p == NULL) {
        return 0;
    }

    return p->weight + remainingWeight(p->next);
}

// Calculate remaining truck capacity
int remainingCapacity(Truck* t, int load) {

    if (t == NULL) {
        return 0;
    }

    return (t->capacity - load) +
           remainingCapacity(t->next, 0);
}

// Backtracking function
bool solve(Container* c, Truck* t, int load) {

    // All containers assigned
    if (c == NULL) {
        return true;
    }

    // No trucks left
    if (t == NULL) {
        return false;
    }

    // Pruning
    if (remainingWeight(c) >
        remainingCapacity(t, load)) {
        return false;
    }

    // OPTION 1: Put container in current truck
    if (load + c->weight <= t->capacity) {

        assigned[t->index][containerCount[t->index]] = c->id;

        containerCount[t->index]++;

        if (solve(c->next, t, load + c->weight)) {
            return true;
        }

        // Undo assignment
        containerCount[t->index]--;
    }

    // OPTION 2: Move to next truck
    if (solve(c, t->next, 0)) {
        return true;
    }

    return false;
}

int main() {

    // Insert containers
    insertContainer(101, 4);
    insertContainer(102, 3);
    insertContainer(103, 5);
    insertContainer(104, 2);

    // Insert trucks
    enqueue(7);
    enqueue(8);
    enqueue(5);

    // Start backtracking
    if (solve(head, front, 0)) {

        cout << "Containers assigned successfully:\n";

        for (int i = 0; i < truckCount; i++) {

            cout << "Truck " << i + 1 << ": ";

            for (int j = 0; j < containerCount[i]; j++) {

                cout << assigned[i][j] << " ";
            }

            cout << endl;
        }
    }
    else {

        cout << "Insufficient truck capacity.";
    }

    return 0;
}

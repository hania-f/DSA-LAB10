
#include <iostream>
using namespace std;

class Stack {
public:
    char operations[20][5];
    int top;

    Stack() {
        top = -1;
    }

    void push(char op[]) {
        top++;

        int i = 0;

        while (op[i] != '\0') {
            operations[top][i] = op[i];
            i++;
        }

        operations[top][i] = '\0';
    }

    void pop() {
        if (top >= 0)
            top--;
    }

    void display() {
        for (int i = 0; i <= top; i++) {
            cout << operations[i] << " ";
        }

        cout << endl;
    }
};

Stack s;

int target;
int maxOperations;
int overflowLimit;

bool found = false;

void solve(int current, int steps) {

    // Target reached
    if (current == target) {
        s.display();
        found = true;
        return;
    }

    // Maximum operations reached
    if (steps == maxOperations)
        return;

    int result;

    // Operation 1: +3
    result = current + 3;

    if (result >= 0 && result <= overflowLimit) {

        s.push("+3");
        solve(result, steps + 1);
        s.pop();
    }

    // Operation 2: *2
    result = current * 2;

    if (result >= 0 && result <= overflowLimit) {

        s.push("*2");
        solve(result, steps + 1);
        s.pop();
    }

    // Operation 3: -5
    result = current - 5;

    if (result >= 0 && result <= overflowLimit) {

        s.push("-5");
        solve(result, steps + 1);
        s.pop();
    }

    // Operation 4: /2
    if (current % 2 == 0) {

        result = current / 2;

        if (result >= 0 && result <= overflowLimit) {

            s.push("/2");
            solve(result, steps + 1);
            s.pop();
        }
    }
}

int main() {

    int initial;

    cout << "Enter initial value: ";
    cin >> initial;

    cout << "Enter target value: ";
    cin >> target;

    cout << "Enter maximum operations: ";
    cin >> maxOperations;

    cout << "Enter overflow limit: ";
    cin >> overflowLimit;

    cout << "\nValid sequences:\n";

    solve(initial, 0);

    if (!found)
        cout << "No valid sequence found.";

    return 0;
}

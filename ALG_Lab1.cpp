#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <conio.h>

using namespace std;

class Stack {
private:
    string value;
    Stack* prev{};
    Stack* next{};
    Stack* head = nullptr;
    Stack* tail = nullptr;

    Stack* creationStack(int length) {
        Stack* curr = nullptr, * afterCurr = nullptr;
        for (int i = 0; i < length; ++i) {
            curr = new Stack;
            curr->next = afterCurr;
            if (afterCurr != nullptr) {
                afterCurr->prev = curr;
            }
            afterCurr = curr;
        }
        curr->prev = nullptr;
        return curr;
    }

public:
    Stack() = default;

    void inputStack(int length) {
        head = creationStack(length);
        Stack* curr = head;
        for (int i = 0; i < length; ++i) {
            cin >> curr->value;
            tail = curr;
            curr = curr->next;
        }
    }

    void inputStack(const string& data) {
        head = creationStack(int(data.size()));
        Stack* curr = head;
        for (char element : data) {
            curr->value = element;
            tail = curr;
            curr = curr->next;
        }
    }

    int sizeStack() {
        int length = 0;
        Stack* curr = head;
        while (curr) {
            length += 1;
            curr = curr->next;
        }
        return length;
    }

    string getTopStack() {
        return tail->value;
    }

    void printStack() {
        Stack* curr = tail;
        int length = sizeStack();
        for (int i = 0; i < length; ++i) {
            cout << curr->value << " ";
            curr = curr->prev;
        }
        cout << "\n";
    }

    void deleteStack() {
        Stack* afterHead;
        while (head) {
            afterHead = head->next;
            delete head;
            head = afterHead;
        }
    }

    void appendElement(const string& data) {
        if (head != nullptr) {
            Stack* curr = tail;
            curr->next = new Stack;
            Stack* temp = curr;
            curr = curr->next;
            curr->prev = temp;
            curr->next = nullptr;
            curr->value = data;
            tail = curr;
        }
        else {
            inputStack(data);
        }
    }

    void deleteElement() {
        if (sizeStack() >= 2) {
            Stack* curr = tail;
            Stack* temp = curr->prev;
            temp->next = nullptr;
            curr->prev = nullptr;
            delete curr;
            tail = temp;
        }
        else {
            deleteStack();
        }
    }

    ~Stack() = default;
};

class Node {
private:
    int value;
    Node* prev;
    Node* next;
    Node* head = nullptr;
    Node* creationList(int length) {
        Node* curr = nullptr, * afterCurr = nullptr;
        for (int i = 0; i < length; ++i) {
            curr = new Node;
            curr->next = afterCurr;
            if (afterCurr != nullptr) {
                afterCurr->prev = curr;
            }
            afterCurr = curr;
        }
        curr->prev = nullptr;
        return curr;
    }
    int sizeList() {
        int length = 0;
        Node* curr = head;
        while (curr) {
            length += 1;
            curr = curr->next;
        }
        return length;
    }
public:
    Node() = default;
    void inputList(int length) {
        head = creationList(length);
        Node* curr = head;
        for (int i = 0; i < length; ++i) {
            cin >> curr->value;
            curr = curr->next;
        }
    }

    void printList() {
        Node* curr = head;
        int length = sizeList();
        for (int i = 0; i < length; ++i) {
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << "\n";
    }

    void deleteList() {
        Node* afterHead;
        while (head) {
            afterHead = head->next;
            delete head;
            head = afterHead;
        }
    }
    ~Node() = default;
};

class Array {
private:
    int length = 0;
    int* head = nullptr;
    int* creationArray() {
        int* array = new int[length];
        return array;
    }
public:
    Array() = default;
    void inputArray(int lengthArray) {
        length = lengthArray;
        head = creationArray();
        for (int i = 0; i < length; ++i) {
            cin >> head[i];
        }
    }

    void printArray() {
        for (int i = 0; i < length; ++i) {
            cout << head[i] << " ";
        }
        cout << "\n";
    }

    void deleteArray() {
        delete[] head;
    }
    ~Array() = default;
};

class Notation {
private:
    vector<string> infixNotation;
    string reversePolishNotation;
    map<string, int> dictOperators = { {"+", 1},
                                                 {"-", 1},
                                                 {"*", 2},
                                                 {"/", 2},
                                                 {"^", 3},
                                                 {"s", 3}, // sin
                                                 {"c", 3} }; // cos
public:
    Notation() = default;

    void inputString(string data) {
        data += " ";
        string localString;
        for (char element : data) {
            if (element != ' ' && element != '(' && element != ')') {
                localString.push_back(element);
            }
            else if (element == '(') {
                localString.push_back(element);
                infixNotation.push_back(localString);
                localString.clear();
            }
            else if (element == ')') {
                infixNotation.push_back(localString);
                localString.clear();
                localString.push_back(element);
                infixNotation.push_back(localString);
                localString.clear();
            }
            else if (!localString.empty()) {
                infixNotation.push_back(localString);
                localString.clear();
            }
        }
    }

    void infixToRPNotation() {
        Stack stack;

        for (const string& token : infixNotation) {
            if (isdigit(token[0])) {
                reversePolishNotation += token + " ";
            }
            else if (dictOperators.find(token) != dictOperators.end()) {
                while (stack.sizeStack() != 0 && stack.getTopStack() != "(" &&
                    dictOperators.at(stack.getTopStack()) >= dictOperators.at(token)) {
                    reversePolishNotation += stack.getTopStack() + " ";
                    stack.deleteElement();
                }
                stack.appendElement(token);
            }

            else if (token == "(") {
                stack.appendElement(token);
            }

            else if (token == ")") {
                while (stack.sizeStack() != 0 && stack.getTopStack() != "(") {
                    reversePolishNotation += stack.getTopStack() + " ";
                    stack.deleteElement();
                }

                if (stack.sizeStack() != 0 && stack.getTopStack() == "(") {
                    stack.deleteElement();
                }
            }
        }

        while (stack.sizeStack() != 0) {
            reversePolishNotation += stack.getTopStack() + " ";
            stack.deleteElement();
        }
    }

    void printNotation() {
        infixToRPNotation();
        cout << reversePolishNotation << "\n";
        deleteNotation();
    }

    void deleteNotation() {
        infixNotation.clear();
        reversePolishNotation.clear();
    }

    ~Notation() = default;
};

int main() {
    int lengthList;
    int lengthArray;
    int lengthStack;
    string directNotation;

    int condition;

    Node node;
    Array array;
    Stack stack;
    Notation notation;

    while (true) {
        cout << "Commands: \n"
            "-- 0) Exit \n"
            "-- 1) Create linked-list \n"
            "-- 2) Create dynamic-array \n"
            "-- 3) Create stack \n"
            "-- 4) Reverse-Polish notation \n";

        cin >> condition;
        switch (condition) {
        case 0:
            node.deleteList();
            array.deleteArray();
            stack.deleteStack();
            notation.deleteNotation();
            exit(0);
        case 1:
            cout << "Input lenght: ";
            cin >> lengthList;
            cout << "Input elements: ";
            node.inputList(lengthList);
            cout << "Linked list: ";
            node.printList();
            _getch();
            system("cls");
            break;
        case 2:
            cout << "Input lenght: ";
            cin >> lengthArray;
            cout << "Input elements: ";
            array.inputArray(lengthArray);
            cout << "Dynamic array: ";
            array.printArray();
            _getch();
            system("cls");
            break;
        case 3:
            cout << "Input lenght: ";
            cin >> lengthStack;
            cout << "Input elements: ";
            stack.inputStack(lengthStack);
            cout << "Stack: ";
            stack.printStack();
            _getch();
            system("cls");
            break;
        case 4:
            cout << "Input infix notation: ";
            cin.ignore();
            getline(cin, directNotation);
            notation.inputString(directNotation);
            cout << "Postfix notation: ";
            notation.printNotation();
            cout << endl;
            break;
        default:
            continue;
        }
    }
}
// 5 + 4 * (32 - 5 * 6 - 1) + 15 + 4 * 3 / 2 - (21 + 5 * 2 - 3) + s (32 - 1) + c (2)
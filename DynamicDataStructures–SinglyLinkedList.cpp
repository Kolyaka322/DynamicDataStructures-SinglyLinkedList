#include <iostream>
#include <stdexcept>

struct StackNode {
    int data;
    StackNode* next;

    explicit StackNode(int val, StackNode* nxt = nullptr)
        : data(val), next(nxt) {
    }
};

class LinkedStack {
private:
    StackNode* topNode;
    size_t currentSize;
    size_t maxCapacity;

    void growCapacity() {
        maxCapacity = (maxCapacity == 0) ? 2 : maxCapacity * 2;
    }

public:
    explicit LinkedStack(size_t initialCapacity = 4)
        : topNode(nullptr), currentSize(0), maxCapacity(initialCapacity) {
    }

    ~LinkedStack() {
        clear();
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        return currentSize;
    }

    size_t capacity() const {
        return maxCapacity;
    }

    void push(int value) {
        if (currentSize >= maxCapacity) {
            growCapacity();
        }
        topNode = new StackNode(value, topNode);
        ++currentSize;
    }

    int pop() {
        if (isEmpty()) {
            throw std::underflow_error("Стек порожній: неможливо виконати pop");
        }
        StackNode* temp = topNode;
        int value = temp->data;
        topNode = topNode->next;
        delete temp;
        --currentSize;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Стек порожній: неможливо виконати peek");
        }
        return topNode->data;
    }

    void clear() {
        while (topNode != nullptr) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        currentSize = 0;
    }

    void print() const {
        std::cout << "Стек (розмір: " << currentSize << ", місткість: " << maxCapacity << ") [вершина -> дно]: ";
        StackNode* curr = topNode;
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "\n";
    }
};

int main() {
    system("chcp 1251>null");
    LinkedStack stack(2);

    stack.push(10);
    stack.push(20);
    stack.print();

    stack.push(30);
    stack.push(40);
    stack.push(50);
    stack.print();

    std::cout << "Верхній елемент (peek): " << stack.peek() << "\n";
    std::cout << "Знято (pop): " << stack.pop() << "\n";
    std::cout << "Знято (pop): " << stack.pop() << "\n";
    stack.print();

    stack.clear();
    std::cout << "Після clear порожній? " << (stack.isEmpty() ? "Так" : "Ні") << "\n";

    return 0;
}

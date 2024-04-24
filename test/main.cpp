#include <iostream>

template<typename T>
struct ListNode {
    T value;
    ListNode* next;
    ListNode(T val) : value(val), next(nullptr) {}
};

template<typename T>
class List {
public:
    ListNode<T>* head;
    ListNode<T>* tail;

    List() : head(nullptr), tail(nullptr) {}

    void append(T val) {
        ListNode<T>* newNode = new ListNode<T>(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to reverse a part of the list from start to end
    void reverse(ListNode<T>*& start, ListNode<T>*& end) {
        ListNode<T>* prev = nullptr;
        ListNode<T>* curr = start;
        ListNode<T>* temp = nullptr;
        ListNode<T>* endNext = end->next;

        while (curr != endNext) {
            temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        // Correct the outer links if necessary
        if (start->next != endNext) {
            start->next = endNext;
        }
        if (endNext) {
            endNext->next = start;
        }

        // Swap start and end pointers to reflect the reversed section
        temp = start;
        start = end;
        end = temp;
    }

    void reverseNth(int n) {
        ListNode<T>* current = head;
        ListNode<T>* prevEnd = nullptr;

        while (current) {
            ListNode<T>* blockStart = current;
            ListNode<T>* blockEnd = current;

            int count = 1;
            while (count < n && blockEnd->next) {
                blockEnd = blockEnd->next;
                count++;
            }

            ListNode<T>* nextBlockStart = blockEnd->next;

            // Reverse the current block
            reverse(blockStart, blockEnd);

            // Connect previous block to current
            if (prevEnd) {
                prevEnd->next = blockStart;
            } else {
                head = blockStart;
            }

            // Prepare for next iteration
            prevEnd = blockEnd;
            current = nextBlockStart;

            // Update tail pointer on last block
            if (!nextBlockStart) {
                tail = blockEnd;
            }
        }
    }

    void print() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~List() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    List<int> myList;
    myList.append(1);
    myList.append(2);
    myList.append(3);
    myList.append(4);
    myList.append(5);
    myList.append(6);
    myList.append(7);
    myList.append(8);
    myList.append(9);

    std::cout << "Original List: ";
    myList.print();

     myList.reverse(myList.head, myList.tail);

    std::cout << "Reversed List: ";
    myList.print();
    
    // Test reverseNth function
    myList.reverseNth(3);

    std::cout << "List after reverseNth(3): ";
    myList.print();

    return 0;
}

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() : head_(nullptr), tail_(nullptr), length_(0) {
    // No need for body implementation here as initializer list does the job
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
    // This correctly returns an iterator to the first element
    return ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
    // This correctly returns an iterator to one past the last element (nullptr)
    // Since tail_->next is always nullptr for the last element, this is correct.
    // No changes needed here if your ListIterator can handle nullptr correctly.
    return ListIterator(nullptr);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
    ListNode* current = head_; // Start with the head of the list
    while (current != nullptr) { // Continue until there are no more nodes
        ListNode* next = current->next; // Save the next node
        delete current; // Delete the current node
        current = next; // Move to the next node
    }
    head_ = nullptr; // Reset head to nullptr
    tail_ = nullptr; // Reset tail to nullptr
    length_ = 0; // Reset the length of the list
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
    ListNode* newNode = new ListNode(ndata);
    newNode->next = head_; // Point newNode's next to the current head
    newNode->prev = nullptr; // newNode's prev is null since it will be the new head
    
    if (head_ != nullptr) {
        head_->prev = newNode; // Update the current head's prev to point to newNode
    }
    
    head_ = newNode; // Update head_ to point to the new node
    
    if (tail_ == nullptr) {
        tail_ = newNode; // If the list was empty, tail_ also points to newNode
    }
    
    length_++; // Increment the length of the list
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
    ListNode* newNode = new ListNode(ndata); // Create a new node with the given data
    newNode->next = nullptr; // Since it's going to be the last node, its next is null

    if (tail_ != nullptr) { // If the list is not empty
        tail_->next = newNode; // Set current tail's next to the new node
        newNode->prev = tail_; // Set new node's prev to the current tail
        tail_ = newNode; // Update the tail to be the new node
    } else { // If the list is empty
        head_ = newNode; // The new node is both the head
        tail_ = newNode; // and the tail of the list
        newNode->prev = nullptr; // Its prev is null since it's the only node
    }

    length_++; // Increment the length of the list
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    // Handle edge cases
    if (start == nullptr || splitPoint <= 0) {
        return nullptr; // No split to perform
    }

    ListNode* curr = start;
    for (int i = 1; i < splitPoint && curr->next != nullptr; i++) {
        curr = curr->next; // Move to the next node until reaching splitPoint or end of list
    }

    // If curr is the last node or beyond, no split occurs
    if (curr == nullptr || curr->next == nullptr) {
        return nullptr;
    }

    // Split the list
    ListNode* newHead = curr->next; // The head of the second part of the list
    newHead->prev = nullptr; // This is now the first node, so no previous node
    curr->next = nullptr; // Disconnect the first part of the list from the second

    return newHead; // Return the head of the second, newly created list
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
    // Early exit if the list has fewer than three elements.
    if (length_ < 3) {
        return;
    }

    ListNode* current = head_;
    ListNode* newHead = nullptr;
    ListNode* lastGroupTail = nullptr;

    while (current != nullptr && current->next != nullptr && current->next->next != nullptr) {
        // Identify the three nodes to rotate.
        ListNode* first = current;
        ListNode* second = current->next;
        ListNode* third = current->next->next;
        ListNode* nextGroupHead = third->next;

        // Perform the rotation: second becomes the first of the group.
        if (newHead == nullptr) {
            newHead = second;
        }
        second->prev = lastGroupTail;
        if (lastGroupTail != nullptr) {
            lastGroupTail->next = second;
        }

        // Adjusting pointers to complete the rotation.
        third->next = first;
        first->prev = third;
        first->next = nextGroupHead;
        if (nextGroupHead != nullptr) {
            nextGroupHead->prev = first;
        } else {
            tail_ = first; // Update the tail if this is the last group.
        }

        // Prepare for the next iteration/group.
        lastGroupTail = first;
        current = nextGroupHead;
    }

    // Update head_ if we made any changes.
    if (newHead != nullptr) {
        head_ = newHead;
    }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    // Validate input
    if (startPoint == nullptr || endPoint == nullptr || startPoint == endPoint) {
        return;
    }

    ListNode* beforeStart = startPoint->prev;
    ListNode* afterEnd = endPoint->next;
    ListNode* current = startPoint;
    ListNode* tempPrev = nullptr;

    while (current != afterEnd) {
        ListNode* nextNode = current->next;
        current->next = tempPrev;
        current->prev = nextNode;
        tempPrev = current;
        current = nextNode;
    }

    // Reconnect the reversed segment with the rest of the list
    if (beforeStart != nullptr) {
        beforeStart->next = endPoint;
    } else {
        head_ = endPoint; // If reversing from the start, update head_
    }

    if (afterEnd != nullptr) {
        afterEnd->prev = startPoint;
    } else {
        tail_ = startPoint; // If reversing till the end, update tail_
    }

    // Swap startPoint and endPoint
    startPoint->next = afterEnd;
    if (beforeStart != nullptr) {
        endPoint->prev = beforeStart;
    } else {
        endPoint->prev = nullptr; // endPoint is now the head
    }

    // Update the references to startPoint and endPoint to their new positions
    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
    if (n <= 1 || head_ == nullptr || head_->next == nullptr) {
        // If n is 1 or less, or the list has 0 or 1 element, no need to reverse.
        return;
    }

    ListNode* currentStart = head_;
    ListNode* blockEnd = nullptr;
    ListNode* prevBlockEnd = nullptr;

    while (currentStart != nullptr) {
        // Identify the end of the current block.
        blockEnd = currentStart;
        for (int i = 1; i < n && blockEnd->next != nullptr; i++) {
            blockEnd = blockEnd->next;
        }

        // Reverse the current block.
        ListNode* nextBlockStart = blockEnd->next;
        reverse(currentStart, blockEnd);

        // Reconnect the reversed block with the rest of the list.
        if (prevBlockEnd != nullptr) {
            prevBlockEnd->next = blockEnd;
            blockEnd->prev = prevBlockEnd;
        } else {
            head_ = blockEnd; // Update the head if we reversed the first block.
        }

        currentStart->next = nextBlockStart;
        if (nextBlockStart != nullptr) {
            nextBlockStart->prev = currentStart;
        } else {
            tail_ = currentStart; // Update the tail if we reversed the last block.
        }

        // Prepare for the next block.
        prevBlockEnd = currentStart;
        currentStart = nextBlockStart;
    }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
    if (!first) return second;
    if (!second) return first;

    // Corrected initialization to avoid most vexing parse
    ListNode dummyNode{ T() }; // Use curly braces for uniform initialization
    ListNode* current = &dummyNode;

    while (first && second) {
        if (first->data < second->data) {
            current->next = first;
            first->prev = current;
            first = first->next;
        } else {
            current->next = second;
            second->prev = current;
            second = second->next;
        }
        current = current->next;
    }

    // Attach any remaining nodes from 'first' or 'second'
    current->next = (first != nullptr) ? first : second;
    if (current->next) {
        current->next->prev = current;
    }

    ListNode* mergedHead = dummyNode.next;
    if (mergedHead) mergedHead->prev = nullptr; // Ensure the head's prev is null
    return mergedHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    if (chainLength <= 1) {
        return start; // Base case: a single element is always sorted.
    }

    // Find the midpoint of the list to split it into two halves
    int mid = chainLength / 2;
    ListNode* middle = start;
    for (int i = 0; i < mid - 1; i++) {
        middle = middle->next;
    }

    ListNode* secondHalfStart = middle->next;
    middle->next = nullptr; // Split the list into two halves

    // Recursively sort each half
    ListNode* left = mergesort(start, mid);
    ListNode* right = mergesort(secondHalfStart, chainLength - mid);

    // Merge the sorted halves
    return merge(left, right);
}


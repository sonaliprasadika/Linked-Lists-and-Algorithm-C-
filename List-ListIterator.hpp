
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        if (position_ != nullptr) { // Check to ensure we're not at the end
            position_ = position_->next; // Move to the next node
        }
        return *this; // Return a reference to this iterator after incrementing
    }

    // Post-Increment, iter++
    ListIterator operator++(int) {
        ListIterator temp(*this);  // Make a copy of the current iterator
        if (position_ != nullptr) {  // Check to ensure we're not at the end
            position_ = position_->next;  // Move to the next node
        }
        return temp;  // Return the copy made before the increment
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        if (position_ != nullptr) { // Ensure we're not at the beginning or in an invalid state
            position_ = position_->prev;
        }
        return *this; // Return a reference to this iterator after decrementing
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        ListIterator temp(*this);  // Make a copy of the current iterator
        if (position_ != nullptr) { // Ensure we're not at the beginning or in an invalid state
            position_ = position_->prev;  // Move to the previous node
        }
        return temp;  // Return the copy made before the decrement
    }

    bool operator!=(const ListIterator& rhs) const {
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};

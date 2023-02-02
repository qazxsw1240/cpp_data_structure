#include "stack.h"

template<class T>
array_stack<T>::array_stack(
        const std::size_t capacity
): _capacity(capacity),
   _elements(new T[this->_capacity]),
   _top(0) {}

template<class T>
array_stack<T>::~array_stack() {
    delete[] this->_elements;
}

template<class T>
bool array_stack<T>::is_empty() const {
    return this->_top == 0;
}

template<class T>
bool array_stack<T>::is_full() const {
    return this->_top == this->_capacity;
}

template<class T>
std::size_t array_stack<T>::size() const {
    return this->_top;
}

template<class T>
bool array_stack<T>::push(T item) {
    if (this->is_full())
        return false;
    this->_elements[this->_top] = item;
    ++this->_top;
    return true;
}

template<class T>
bool array_stack<T>::peek(T &item) const {
    if (this->is_empty())
        return false;
    item = this->_elements[this->_top - 1];
    return true;
}

template<class T>
bool array_stack<T>::pop(T &item) {
    if (this->is_empty())
        return false;
    --this->_top;
    item = this->_elements[this->_top];
    return true;
}

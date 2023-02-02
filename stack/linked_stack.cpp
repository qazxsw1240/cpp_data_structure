#include <cstdint>
#include "stack.h"

template<class T>
linked_stack<T>::frame::frame(
        T value,
        frame *prev
): m_value(value),
   m_prev(prev) {}

template<class T>
linked_stack<T>::linked_stack(): _size(0),
                                 _top(nullptr) {}

template<class T>
linked_stack<T>::~linked_stack() {
    while (this->_top != nullptr) {
        frame *f = this->_top;
        this->_top = f->m_prev;
        f->m_prev = nullptr;
        delete f;
    }
}

template<class T>
bool linked_stack<T>::is_empty() const {
    return this->_top == nullptr;
}

template<class T>
bool linked_stack<T>::is_full() const {
    return this->_size == SIZE_MAX;
}

template<class T>
size_t linked_stack<T>::size() const {
    return this->_size;
}

template<class T>
bool linked_stack<T>::push(T item) {
    if (this->is_full())
        return false;
    frame *f = new frame(item, this->_top);
    this->_top = f;
    ++this->_size;
    return true;
}

template<class T>
bool linked_stack<T>::peek(T &item) const {
    if (this->is_empty())
        return false;
    item = this->_top->m_value;
    return true;
}

template<class T>
bool linked_stack<T>::pop(T &item) {
    if (this->is_empty())
        return false;
    frame *f = this->_top;
    item = f->m_value;
    this->_top = f->m_prev;
    delete f;
    --this->_size;
    return true;
}

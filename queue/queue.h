#ifndef CPP_DATA_STRUCTURE_QUEUE_H
#define CPP_DATA_STRUCTURE_QUEUE_H


#include <cstddef>

template<class T>
class queue {
public:
    virtual bool is_empty() const = 0;

    virtual bool is_full() const = 0;

    virtual std::size_t size() const = 0;

    virtual bool enqueue(T item) = 0;

    virtual bool peek(T &item) const = 0;

    virtual bool dequeue(T &item) = 0;
};


#endif //CPP_DATA_STRUCTURE_QUEUE_H

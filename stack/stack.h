#ifndef CPP_DATA_STRUCTURE_STACK_H
#define CPP_DATA_STRUCTURE_STACK_H

#include <cstddef>

template<class T>
class stack {
public:
    virtual ~stack() = default;

    virtual bool is_empty() const = 0;

    virtual bool is_full() const = 0;

    virtual std::size_t size() const = 0;

    virtual bool push(T item) = 0;

    virtual bool peek(T &item) const = 0;

    virtual bool pop(T &item) = 0;
};

template<class T>
class array_stack final : stack<T> {
    std::size_t _capacity;
    T *_elements;
    std::size_t _top;

public:
    explicit array_stack(std::size_t capacity);

    ~array_stack() override;

    bool is_empty() const override;

    bool is_full() const override;

    std::size_t size() const override;

    bool push(T item) override;

    bool peek(T &item) const override;

    bool pop(T &item) override;
};

template<class T>
class linked_stack final : stack<T> {
    class frame {
    public:
        T m_value;
        frame *m_prev;

        frame(T value, frame *prev);
    };

    std::size_t _size;
    frame *_top;

public:
    explicit linked_stack();
    
    ~linked_stack() override;

    bool is_empty() const override;

    bool is_full() const override;

    std::size_t size() const override;

    bool push(T item) override;

    bool peek(T &item) const override;

    bool pop(T &item) override;
};


#endif //CPP_DATA_STRUCTURE_STACK_H

#ifndef CPP_DATA_STRUCTURE_STACK_H
#define CPP_DATA_STRUCTURE_STACK_H

#include <cstddef>

template<class T>
class stack {
public:
    virtual ~stack() = default;

    /**
     * 스택이 비었는지 확인합니다.
     */
    virtual bool is_empty() const = 0;

    /**
     * 스택이 가득 찼는지 확인합니다.
     */
    virtual bool is_full() const = 0;

    /**
     * 스택이 가지고 있는 요소의 개수를 반환합니다.
     */
    virtual std::size_t size() const = 0;

    /**
     * 스택에 요소를 추가합니다.
     * @param item 스택에 추가할 요소
     * @returns 성공적으로 추가되어 스택에 변화가 생기면 true, 아니면 false
     */
    virtual bool push(T item) = 0;

    /**
     * 스택에서 제거하지 않으면서 가장 마지막에 추가된 요소를 참조매개변수에 할당합니다.
     * 스택에 요소가 비어있으면 false가 반환되면서 참조매개변수에 값이 할당되지 않습니다.
     * @param item 값이 할당될 변수
     * @returns 스택이 비어있으면 false, 아니면 true
     */
    virtual bool peek(T &item) const = 0;

    /**
     * 스택에서 가장 마지막에 추가된 요소를 제거하면서 참조매개변수에 제거된 요소를 할당합니다.
     * 스택에 요소가 비어있으면 false가 반환되면서 참조매개변수에 값이 할당되지 않습니다.
     * @param item 값이 할당될 변수
     * @returns 스택이 비어있으면 false, 아니면 true
     */
    virtual bool pop(T &item) = 0;
};

template<class T>
class array_stack final : stack<T> {
    /**
     * 스택의 허용량
     */
    std::size_t _capacity;
    /**
     * 요소가 저장될 배열
     */
    T *_elements;

    /**
     * 현재의 인덱스 위치
     */
    std::size_t _top;

public:
    /**
     * 스택을 생성자로 초기화합니다.
     * @param capacity 스택의 허용량
     */
    explicit array_stack(std::size_t capacity);

    /**
     * 메모리에서 소멸될 때 스택을 해체합니다.
     */
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
    /**
     * 스택을 초기화합니다.
     */
    explicit linked_stack();

    /**
     * 메모리에서 소멸될 때 스택을 해체합니다.
     */
    ~linked_stack() override;

    bool is_empty() const override;

    bool is_full() const override;

    std::size_t size() const override;

    bool push(T item) override;

    bool peek(T &item) const override;

    bool pop(T &item) override;
};


#endif //CPP_DATA_STRUCTURE_STACK_H

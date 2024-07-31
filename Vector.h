#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

// This would do for now.
//
// Later on, we add feature like reversing,
// reserving, pushback, pop, shift and unshift,
// capacity, etc.
// Ensure test cases for those as well!

template<class T>
class Vector {
public:
    Vector();
    explicit Vector(int size);
    // allows for Vector _ {...}
    Vector(std::initializer_list<T> list);

    // Deconstructor
    ~Vector();

    // copy constructor
    Vector(const Vector& other);
    // move constructor
    Vector(Vector&& other) noexcept;

    [[nodiscard]] size_t size() const;
    [[nodiscard]] T* begin() const;
    [[nodiscard]] T* end() const;
    [[nodiscard]] T front() const;
    [[nodiscard]] T back() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] int capacity() const;

    T at(int index) const;

    void reserve(int newalloc);
    void resize(int new_size);
    void push_back(T new_item);
    void pop_back();
    void clear();
    void erase();
    void shrink_to_fit();

    // Provide (mutable) support for Vector[]
    T& operator[](int index);
    // `const` support - provide immutable reference
    const T& operator[](int index) const;
    // copy assignment (copy and swap idiom)
    Vector& operator=(const Vector& other);
    // move assignment
    Vector& operator=(Vector&& other) noexcept;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
private:
    const int INCREASE_FACTOR = 2; // Idk, honestly...
    int _sz{};
    std::unique_ptr<T[]> data{};
    int _space{};
};


#endif //VECTOR_H

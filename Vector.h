#ifndef VECTOR_H
#define VECTOR_H

#include <memory>


template<class T>
class Vector {
public:
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
    int sz{};
    std::unique_ptr<T[]> data{};
};


#endif //VECTOR_H

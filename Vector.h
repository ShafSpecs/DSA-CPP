#ifndef VECTOR_H
#define VECTOR_H

#include <memory>


class Vector {
public:
    explicit Vector(int size);
    // allows for Vector _ {...}
    Vector(std::initializer_list<int> list);

    // Deconstructor
    ~Vector();

    // copy constructor
    Vector(const Vector& other);
    // move constructor
    Vector(Vector&& other) noexcept;

    [[nodiscard]] int size() const;
    [[nodiscard]] int* begin() const;
    [[nodiscard]] int* end() const;

    // Provide (mutable) support for Vector[]
    int& operator[](int index);
    // `const` support - provide immutable reference
    const int& operator[](int index) const;
    // copy assignment (copy and swap idiom)
    Vector& operator=(const Vector& other);
    // move assignment
    Vector& operator=(Vector&& other) noexcept;
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
private:
    int sz{};
    std::unique_ptr<int[]> data{};
};


#endif //VECTOR_H

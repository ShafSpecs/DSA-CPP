#include <gtest/gtest.h>
#include <string>
#include <typeinfo>

// Apparently, when using template classes, importing
// just header files don't work for some reason.
//
// Weird, but you need the implementation as well. Anyway,
// my convention splits the class into two; the source also
// imports the header.
#include "Vector.cpp"

namespace {
    TEST(Vector, VectorInstantiation) {
        Vector a {1, 2, 3};

        ASSERT_EQ(a.size(), 3) << "Vector a is instantiated with the right size";
        ASSERT_EQ(a[0], 1) << "Vector a is created with the correct order of items";

        auto b = Vector<int>(5);

        ASSERT_EQ(b.size(), 5) << "Vector can be created with a fixed size of default items";
        ASSERT_EQ(b[0], 0) << "Ensure that vector is created correctly with default values";

        const Vector c = {0, 512};

        ASSERT_EQ(c.size(), 2) << "Vector can also be created this way!";

        const auto d = Vector<int>();

        ASSERT_EQ(d.size(), 0) << "Vector also has an empty constructor that creates an"
                                  "empty vector.";
    }

    TEST(Vector, VectorSize) {
        const Vector<int> a {1, 2, 3};
        const auto b = Vector<int>(200);
        const Vector<int> c = {0};

        ASSERT_EQ(a.size(), 3);
        ASSERT_EQ(b.size(), 200);
        ASSERT_EQ(c.size(), 1);
    }

    TEST(Vector, VectorEdges) {
        const Vector test {1, 5, 9};

        const int* begin = test.begin();

        ASSERT_EQ(*begin, 1);

        // Hmm, an interesting case-study
        //
        // Learning new ways to think as I come up with
        // case-studies
        auto it = test.begin();
        for (size_t i = 0; i < test.size(); ++i) {
            ASSERT_NE(it, test.end()) << "Iterator should not be at end yet";
            ++it;
        }

        ASSERT_EQ(it, test.end()) << "Iterator should now be at end (one past last element)";
    }

    TEST(Vector, VectorOperators) {
        const Vector a = {0, 2, 4};
        Vector b = {0, 2, 5};
        const auto c = Vector<int>(4);

        ASSERT_NE(a, b) << "Basic non-equals assetion. Checks for != operator";

        b[2] = 4;

        ASSERT_EQ(a, b) << "Tests both the [] operator (+ mutability) and the == operator";
    }

    TEST(Vector, VectorCopy) {
        Vector a = {1, 2};
        auto b = Vector<int>(2);

        b.reserve(3);

        b = a;

        ASSERT_EQ(a, b);

        ASSERT_EQ(b[0], 1);
        ASSERT_EQ(b[1], 2);

        ASSERT_EQ(a.capacity(), 2);
        ASSERT_EQ(b.capacity(), 3) << "A shallow copy doesn't mutate reserved space";

        ASSERT_NE(&b, &a) << "Best way I could think of to make sure a and b are two, distinct objects";
    }

    TEST(Vector, VectorMove) {
        Vector a {0, 1, 2};
        Vector b {3, 4, 5, 6};

        a.reserve(5);
        const size_t a_size_before = a.size();
        const int a_capacity_before = a.capacity();

        const int* a_data_ptr = &a[0];

        b = std::move(a);

        ASSERT_EQ(a_size_before, 3);
        ASSERT_NE(a.size(), 3);

        ASSERT_EQ(b.size(), a_size_before);
        ASSERT_NE(b.capacity(), a_capacity_before) << "Moving/capacity discards reserved, unused space";
        ASSERT_EQ(&b[0], a_data_ptr);
    }

    TEST(Vector, VectorGenerics) {
        const auto _int = Vector<int>(3);
        const auto _double = Vector<double>(2);
        const auto _str = Vector<std::string>(5);

        ASSERT_EQ(_int[0], 0);
        ASSERT_EQ(_double[0], 0.0);
        ASSERT_EQ(_str[0], "") << "This test case asserts that `Vector` is dynamic";
    }

    TEST(Vector, VectorEnds) {
        const Vector vector = {2, 3, 4, 5};

        ASSERT_EQ(vector.front(), 2) << "Ascertain the `front` method returns the first element";
        ASSERT_EQ(vector.back(), 5) << "The `back` method must return the last element (not pointer)";
    }

    TEST(Vector, VectorEmpty) {
        const auto v1 = Vector<int>();
        const Vector v2 = {1, 2};
        const auto v3 = Vector<int>(0);

        ASSERT_TRUE(v1.empty()) << "Vector empty constructor initialises an empty vector successfully";
        ASSERT_FALSE(v2.empty());
        ASSERT_TRUE(v3.empty());
    }

    TEST(Vector, VectorAt) {
        const Vector v = {1.0, 2.1, 2.34, 5.6};

        ASSERT_EQ(v.at(1), 2.1) << "A less sophisticated `[]` method";
        ASSERT_EQ(v.at(3), 5.6);

        ASSERT_THROW(v.at(5), std::out_of_range) << "`at` throws when you attempt to access an element "
                                                    "out of bounds";
    }

    TEST(Vector, VectorReserve) {
        Vector v = {1, 2, 3};

        ASSERT_EQ(v.capacity(), 3) << "The vector total space (capacity) is the same as the initialised"
                                      "value";
        v.reserve(2);

        ASSERT_EQ(v.capacity(), 3) << "Reserving a smaller capacity does nothing";

        v.reserve(10);

        ASSERT_EQ(v.capacity(), 10) << "The vector is now capable of holding 10 elements";
        ASSERT_EQ(v.size(), 3) << "The vector still has a size of 3 elements - the other 7 spaces remain"
                                  "uninitialised and are just empty memory (not necessarily null)";
    }

    TEST(Vector, VectorResize) {
        Vector v = {2, 3, 4, 5, 0};

        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v.capacity(), 5) << "Capacity and size are the same at initialisation";

        v.resize(6);

        ASSERT_EQ(v.size(), 6);
        ASSERT_EQ(v.capacity(), 6) << "Resizing increases the capacity, if space is less than new size";

        ASSERT_EQ(v[5], 0) << "Resizing initializes the unassigned spaces to default value of type";

        v.reserve(10);

        ASSERT_EQ(v.capacity(), 10) << "Vector now has a capacity of ten";
        ASSERT_EQ(v.size(), 6) << "The size is still 6";

        v.resize(8);

        ASSERT_EQ(v.capacity(), 10) << "Capacity is greater than new size so it doesn't change";
        ASSERT_EQ(v.size(), 8) << "The new size is 8";
    }

    TEST(Vector, VectorPushBack) {
        Vector v = {1, 2};

        ASSERT_EQ(v.capacity(), 2);

        v.push_back(3);

        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v.capacity(), 4);
        ASSERT_EQ(v.size(), 3);

        v.push_back(999);

        ASSERT_EQ(v.capacity(), 4);
        ASSERT_EQ(v.size(), 4);
    }
} // namespace

#include <gtest/gtest.h>

#include "Vector.h"

namespace {
    TEST(Vector, VectorInstantiation) {
        Vector a {1, 2, 3};

        ASSERT_EQ(a.size(), 3) << "Vector a is instantiated with the right size";
        ASSERT_EQ(a[0], 1) << "Vector a is created with the correct order of items";

        auto b = Vector(5);

        ASSERT_EQ(b.size(), 5) << "Vector can be created with a fixed size of default items";
        ASSERT_EQ(b[0], 0) << "Ensure that vector is created correctly with default values";

        const Vector c = {0, 512};

        ASSERT_EQ(c.size(), 2) << "Vector can also be created this way!";
    }

    TEST(Vector, VectorSize) {
        const Vector a {1, 2, 3};
        const auto b = Vector(200);
        const Vector c = {0};

        ASSERT_EQ(a.size(), 3);
        ASSERT_EQ(b.size(), 200);
        ASSERT_EQ(c.size(), 1);
    }

    TEST(Vector, VectorEnds) {
        const Vector test {1, 5, 9};

        const int* begin = test.begin();
        const int* end = test.end();

        ASSERT_EQ(*begin, 1);
        ASSERT_EQ(*end, 9);
    }

    TEST(Vector, VectorOperators) {
        const Vector a = {0, 2, 4};
        Vector b = {0, 2, 5};
        const auto c = Vector(4);

        ASSERT_NE(a, b) << "Basic non-equals assetion. Checks for != operator";

        b[2] = 4;

        ASSERT_EQ(a, b) << "Tests both the [] operator (+ mutability) and the == operator";
    }

    TEST(Vector, VectorCopy) {
        Vector a = {1, 2};
        auto b = Vector(2);

        b = a;

        ASSERT_EQ(a, b);

        ASSERT_EQ(b[0], 1);
        ASSERT_EQ(b[1], 2);

        ASSERT_NE(&b, &a) << "Best way I could think of to make sure a and b are two, distinct objects";
    }

    TEST(Vector, VectorMove) {
        Vector a {0, 1, 2};
        Vector b {3, 4, 5, 6};

        const size_t a_size_before = a.size();

        const int* a_data_ptr = &a[0];

        b = std::move(a);

        ASSERT_EQ(a_size_before, 3);
        ASSERT_NE(a.size(), 3);

        ASSERT_EQ(b.size(), a_size_before);
        ASSERT_EQ(&b[0], a_data_ptr);
    }
} // namespace

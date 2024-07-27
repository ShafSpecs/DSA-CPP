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
        Vector<int> a {1, 2, 3};

        ASSERT_EQ(a.size(), 3) << "Vector a is instantiated with the right size";
        ASSERT_EQ(a[0], 1) << "Vector a is created with the correct order of items";

        auto b = Vector<int>(5);

        ASSERT_EQ(b.size(), 5) << "Vector can be created with a fixed size of default items";
        ASSERT_EQ(b[0], 0) << "Ensure that vector is created correctly with default values";

        const Vector<int> c = {0, 512};

        ASSERT_EQ(c.size(), 2) << "Vector can also be created this way!";
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
        const Vector<int> test {1, 5, 9};

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
        const Vector<int> a = {0, 2, 4};
        Vector<int> b = {0, 2, 5};
        const auto c = Vector<int>(4);

        ASSERT_NE(a, b) << "Basic non-equals assetion. Checks for != operator";

        b[2] = 4;

        ASSERT_EQ(a, b) << "Tests both the [] operator (+ mutability) and the == operator";
    }

    TEST(Vector, VectorCopy) {
        Vector<int> a = {1, 2};
        auto b = Vector<int>(2);

        b = a;

        ASSERT_EQ(a, b);

        ASSERT_EQ(b[0], 1);
        ASSERT_EQ(b[1], 2);

        ASSERT_NE(&b, &a) << "Best way I could think of to make sure a and b are two, distinct objects";
    }

    TEST(Vector, VectorMove) {
        Vector<int> a {0, 1, 2};
        Vector<int> b {3, 4, 5, 6};

        const size_t a_size_before = a.size();

        const int* a_data_ptr = &a[0];

        b = std::move(a);

        ASSERT_EQ(a_size_before, 3);
        ASSERT_NE(a.size(), 3);

        ASSERT_EQ(b.size(), a_size_before);
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
} // namespace

#include <gtest/gtest.h>

#include "HashTable.cpp"
#include "Pair.cpp"
#include "Vector.cpp"

namespace {
    TEST(HashTable, TableInstantiation) {
        const auto t1 = HashTable<int, int>();
        const auto t2 = HashTable<int, char>(40);

        ASSERT_EQ(t1.capacity(), 16) << "Hash table instantiates with a default capacity of 16";
        ASSERT_EQ(t2.capacity(), 40) << "Hash table can also customise table size - to conserve "
                                    "memory/expand capacity";

        // gtest ASSERT_DEATH is broken, for some reason, generics
        // aren't valid.
        //
        // ASSERT_DEATH({
        //     const auto t3 = HashTable<Vector<int>,int>();
        // }, "Key type must be a string, int, char, or long");
    }

    TEST(HashTable, TableOperations) {
        auto table = HashTable<char, int>();

        table.insert('a', 5);
        table.insert('b', 8);

        ASSERT_EQ(table.get('a'), 5);
        ASSERT_EQ(table.get('b'), 8);

        ASSERT_EQ(table.get('v'), std::nullopt) << "Undefined keys return a `nullopt` (not an error)";

        table.remove('b');

        ASSERT_EQ(table.get('b'), std::nullopt);
    }

    TEST(HashTable, ValueChecker) {
        auto table = HashTable<int, std::string>();

        table.insert(0, "John Doe");
        table.insert(1, "Kree Jones");

        ASSERT_TRUE(table.is_value(0, "John Doe"));
        ASSERT_FALSE(table.is_value(1, "ShafSpecs"));
        ASSERT_FALSE(table.is_value(1001, "")) << "Undefined keys also work - always returns false tho";
    }
} // namespace

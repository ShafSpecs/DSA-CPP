#include <gtest/gtest.h>
#include "Map.cpp"

namespace {
    TEST(Map, MapInstantiation) {
        const auto raw_map = Map<int, double>();
        const Map<int, char> map = {{1, 's'}, {2, 'e'}};

        ASSERT_EQ(map.size(), 2) << "Map is instantiated correctly";
        ASSERT_EQ(raw_map.size(), 0) << "An empty map can be initialised successfully";
    }

    TEST(Map, MapSize) {
        const Map<int, double> a = {{0, 1.0}, {1, 2.0}, {2, 3.0}, {3, 4.0}};
        const auto b = Map<int, char>();
        // apparently, using new returns a pointer?! so:
        // `new Map<...>` is actually Map* and not Map.
        //
        // in-efficiences whilst copying and dynamic alloc.
        // are the main reason imo for this behaviour 🖋️
        const Map<char, long> c = {{'a', 2465982}};

        ASSERT_EQ(a.size(), 4);
        ASSERT_EQ(b.size(), 0);
        ASSERT_EQ(c.size(), 1);
    }

    TEST(Map, ClearingMap) {
        Map<int, char> map = {{1, 's'}, {2, 'x'}, {7, 'p'}};

        ASSERT_FALSE(map.empty());

        map.clear();

        ASSERT_TRUE(map.empty());
        ASSERT_EQ(map.size(), 0);
    }

    TEST(Map, MapInsertion) {
        Map<int, char> map = {{1, 's'}, {2, 'x'}, {7, 'p'}};

        map.insert(9, 'd');
        map.insert(std::pair<int, char>({2, 'h'}));

        ASSERT_EQ(map.size(), 5);
        ASSERT_FALSE(map.empty());
    }

    TEST(Map, MapRemoval) {
        Map<int, char> map = {{1, 's'}, {2, 'x'}, {7, 'p'}};

        map.erase(5);

        ASSERT_EQ(map.size(), 3) << "Attempting to erase a non-existent key does nothing";

        map.erase(2);

        ASSERT_EQ(map.size(), 2) << "Successful erasure removes the associated key-value pair";
    }

    TEST(Map, MapOperators) {
        Map<int, char> a = {{1, 's'}, {2, 'x'}, {7, 'p'}};
        const Map<int, char> b = {{1, 's'}, {2, 'x'}, {7, 'p'}};
        Map<int, char> c = {};

        ASSERT_EQ(a, b);
        ASSERT_NE(b, c);

        ASSERT_EQ(a[1], 's');
        ASSERT_EQ(b[2], 'x') << "[] operator works well on immutable Map as well";

        ASSERT_EQ(c[5], char()) << "Should return a mutable default value of value type when "
                                   "key is not found";

        c[5] = 'a';
        ASSERT_EQ(c[5], 'a');
        ASSERT_GT(c.size(), 0);
    }
} // namespace
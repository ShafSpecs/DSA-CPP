#include <gtest/gtest.h>
#include "Map.cpp"

namespace {
    TEST(Map, MapInstantiation) {
        const Map<int, char> map = {{1, 's'}, {2, 'e'}};

        ASSERT_EQ(map.size(), 2);
    }
} // namespace
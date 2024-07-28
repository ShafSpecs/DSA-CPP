#include <gtest/gtest.h>
#include <string>

#include "Pair.cpp"

namespace {
    TEST(Pair, PairInstantiation) {
        const auto pair = Pair<int, int>({1, 3});

        ASSERT_EQ(pair.first, 1);
        ASSERT_EQ(pair.second, 3) << "Ensuring that Pair got instantiated correctly";
    }

    TEST(Pair, PairSwapping) {
        auto pair = Pair<int, int>({3, 8});

        ASSERT_EQ(pair.first, 3);
        ASSERT_EQ(pair.second, 8);

        pair.swap();

        ASSERT_EQ(pair.first, 8);
        ASSERT_EQ(pair.second, 3);

        auto diff_pair = Pair<std::string, int>({"value", 5});

        ASSERT_EQ(diff_pair.first, "value");

        const auto new_pair = diff_pair.swap();

        ASSERT_EQ(new_pair.first, 5);
        ASSERT_EQ(diff_pair.second, 5) << "Swap occured successfully";
    }
} // namespace
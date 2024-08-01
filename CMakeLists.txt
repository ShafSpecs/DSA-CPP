cmake_minimum_required(VERSION 3.28)
project(DSA)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(DSA main.cpp
        Vector.cpp
        Vector.h
        Map.cpp
        Map.h
        BinaryTree.cpp
        Pair.cpp
        Pair.h
        HashTable.cpp
        HashTable.h)

enable_testing()

add_executable(
        dsa_test
        # test files
        binary_tree_test.cpp
        hash_table_test.cpp
        map_test.cpp
        pair_test.cpp
        vector_test.cpp
        # source files
        BinaryTree.cpp
        HashTable.cpp
        HashTable.h
        Vector.cpp
        Vector.h
        Map.cpp
        Map.h
        Pair.h
        Pair.cpp
)
target_link_libraries(
        dsa_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dsa_test)

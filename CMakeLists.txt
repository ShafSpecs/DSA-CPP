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
        Vector.h)

enable_testing()

add_executable(
        vector_test
        vector_test.cpp
        Vector.cpp
        Vector.h
)
target_link_libraries(
        vector_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_test)

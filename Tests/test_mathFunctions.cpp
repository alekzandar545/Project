#if !TEST_IN_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#else
#define DOCTEST_CONFIG_DISABLE
#endif
#include "doctest.h"
#include "../src/Utils/mathFunctions.h"

// MathFunctions Tests
TEST_CASE("MathFunctions::Fib") {
    CHECK(MathFunctions::Fib(0, 1, 0) == 0);
    CHECK(MathFunctions::Fib(0, 1, 1) == 1);
    CHECK(MathFunctions::Fib(0, 1, 5) == 5);
    CHECK(MathFunctions::Fib(1, 1, 5) == 8);
}

TEST_CASE("MathFunctions::Swap") {
    unsigned a = 5, b = 10;
    MathFunctions::Swap(a, b);
    CHECK(a == 10);
    CHECK(b == 5);
}

TEST_CASE("MathFunctions::Shuffle") {
    std::vector<unsigned> vec = {1, 2, 3, 4, 5};
    std::vector<unsigned> originalVec = vec;
    MathFunctions::Shuffle(vec);
    // Check that the shuffled vector has the same elements
    CHECK(vec.size() == originalVec.size());
    std::sort(vec.begin(), vec.end());
    CHECK(vec == originalVec);
}

TEST_CASE("MathFunctions::Min") {
    CHECK(MathFunctions::Min(10, 20) == 10);
    CHECK(MathFunctions::Min(20, 10) == 10);
    CHECK(MathFunctions::Min(15, 15) == 15);
}

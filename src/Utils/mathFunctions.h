#pragma once
#include <vector>

class MathFunctions {
public:
    // Calculates the nth Fibonacci number starting from a and b.
    static unsigned Fib(unsigned a, unsigned b, unsigned n);

    // Swaps the values of two unsigned integers.
    static void Swap(unsigned& a, unsigned& b);

    // Shuffles the elements of a vector of unsigned integers.
    static void Shuffle(std::vector<unsigned>& a);

    // Returns the minimum of two unsigned integers.
    static unsigned Min(const unsigned a, const unsigned b);
};
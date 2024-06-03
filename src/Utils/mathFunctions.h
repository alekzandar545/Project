#pragma once
#include <vector>

/**
 * @class MathFunctions
 * @brief Contains various mathematical functions.
 */
class MathFunctions {
public:
    /**
     * @brief Calculates the nth Fibonacci number starting from a and b.
     * @param a The first number in the Fibonacci sequence.
     * @param b The second number in the Fibonacci sequence.
     * @param n The position of the desired Fibonacci number.
     * @return The nth Fibonacci number.
     */
    static unsigned Fib(unsigned a, unsigned b, unsigned n);

    /**
     * @brief Swaps the values of two unsigned integers.
     * @param a The first integer.
     * @param b The second integer.
     */
    static void Swap(unsigned& a, unsigned& b);

    /**
     * @brief Shuffles the elements of a vector of unsigned integers.
     * @param a The vector to be shuffled.
     */
    static void Shuffle(std::vector<unsigned>& a);

    /**
     * @brief Returns the minimum of two unsigned integers.
     * @param a The first integer.
     * @param b The second integer.
     * @return The minimum of a and b.
     */
    static unsigned Min(const unsigned a, const unsigned b);
};
#include "mathFunctions.h"
#include <vector>
#include <cstdlib>


unsigned MathFunctions::Fib(unsigned a, unsigned b, unsigned n) {
    if (n == 0) return a;
    if (n == 1) return b;
    unsigned prev = a;
    unsigned curr = b;
    unsigned next;
    for (size_t i = 2; i <= n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return next;
}

void MathFunctions::Swap(unsigned& a, unsigned& b) {
    unsigned c = a;
    a = b;
    b = c;
}

void MathFunctions::Shuffle(std::vector<unsigned>& a) {
    for (int i = 0; i < a.size(); ++i) {
        Swap(a[i], a[rand() % a.size()]);
    }
}

unsigned MathFunctions::Min(const unsigned a, const unsigned b) {
    return (a < b) ? a : b;
}
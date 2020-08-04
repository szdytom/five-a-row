/**
 * random.cpp
 * 
 * Define of functions and classes in random.h
 * 
 */

#include "../../include/tools/random.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <cstdlib>

#ifdef RAND_USE_MAX
#undef RAND_USE_MAX
#endif

#ifdef RAND_USE_MAX_LOG
#undef RAND_USE_MAX_LOG
#endif

#define RAND_USE_MAX 256
#define RAND_USE_MAX_LOG 8

int ltzero::tools::randint(int x, int y) {
    if (x >= y)
        throw std::runtime_error("[ltzero::tools::randint] range length must be at least 1.");

    return x + randint(y - x);
}

int ltzero::tools::randint(int x) {
    int res = 0;
    while (res < x)
        res = (res << RAND_USE_MAX_LOG) + (std::rand() % RAND_USE_MAX);

    return res % x;
}

template <typename __T>
__T rand_choice(std::vector<__T> v) {
    return v[randint(v.size())];
}

#undef RAND_USE_MAX
#undef RAND_USE_MAX_LOG
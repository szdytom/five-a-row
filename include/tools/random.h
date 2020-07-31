/**
 * random.h
 * 
 * A simple tool about generating random numbers.
 * 
 * functions:
 *   - int randint(int)
 *   - int randint(int, int)
 *   - __T rand_choice(std::vector<__T>)
 * 
 */

#ifndef TOOLS_RANDOM_H
#define TOOLS_RANDOM_H

#include <vector>

namespace ltzero::tools {

/**
 * @breif get a random number in [x, y)
 * @param x  
 * @param y
 * @return int the random number
 * @throw std::invalid_argument in witch case x is larger of equal than y
 * 
 * This function generates random numbers using rand() inside stdlib,
 * so you need to call srand() first.
 *
 */
int randint(int x, int y);

/**
 * @breif get a random number in [0, x)
 * @param x
 * @return int the random number
 * 
 * This function generates random numbers using rand() inside stdlib,
 * so you need to call srand() first.
 *
 */
int randint(int x);

/**
 * @breif get a random value in a std::vector
 * @param v the vector
 * @return __T the value of random choice
 * 
 * This function choice a random index in the vector,
 * than return the value of the index in vector.
 *
 * like this:
 * return v[random_index];
 * 
 */
template<typename __T> 
__T rand_choice(std::vector<__T> v);

} // namespace ltzero::tools

#endif// TOOLS_RANDOM_H
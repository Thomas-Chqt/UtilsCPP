/*
 * ---------------------------------------------------
 * random.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 12:42:06
 * ---------------------------------------------------
 */

#ifndef RANDOM_HPP
# define RANDOM_HPP

#include <string>
#include <vector>
#include <random>

#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/UniquePtr.hpp"

namespace utils_tests
{

template<typename T>
T random()
{
    static std::mt19937 gen((std::random_device())());
    static std::uniform_int_distribution<T> dis;
    return dis(gen);
}

template<typename T>
T random(T min, T max)
{
    static std::mt19937 gen((std::random_device())());
    std::uniform_int_distribution<T> dis(min, max);
    return dis(gen);
}

template<>
char random<char>();

template<>
unsigned char random<unsigned char>();

template<>
std::string random<std::string>();

template<>
std::vector<int> random<std::vector<int>>();

template<>
float random<float>();

template<>
double random<double>();

}

#endif // RANDOM_HPP
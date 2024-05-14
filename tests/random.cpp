/*
 * ---------------------------------------------------
 * random.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 12:44:01
 * ---------------------------------------------------
 */

#include "./random.hpp"

namespace utils_tests
{

template<>
char random<char>()
{
    return (char)random<int>(CHAR_MIN, CHAR_MAX);
}

template<>
unsigned char random<unsigned char>()
{
    return (unsigned char)random<int>(0, UCHAR_MAX);
}

template<>
std::string random<std::string>()
{
    static const std::string strs[] = {
        "azerty",      "qwerty",
        "hello",       "world",
        "foo",         "bar",
        "example",     "test",
        "programming", "github",
        "copilot",     "more",
        "strings",     "to",
        "add",         "in",
        "this",        "array",
        "for",         "testing",
        "purposes",    "lolo",
        "",            "ezljrhfzeirufhzeiurnfzeiruhgzieuhgiuzenrizuehtgiuoerhflzieurhfzeuirhfzeliurhfilezrhglijrnfuzeilrfhzleirjhgizeuthglzeiurfnizelurhfzeiruhgzelirufhjizerufhjezliruhgizelrunfzeliruncfzelirughzeilruhgzeliurfhzeriunfczieruhf"
    };

    return strs[random<unsigned int>(0, sizeof(strs) / sizeof(strs[0]) - 1)];
}

template<>
std::vector<int> random<std::vector<int>>()
{
    std::vector<int> vector;
    std::vector<int>::size_type len = random<std::vector<int>::size_type>(0, 10);
    vector.reserve(len);
    vector.resize(len);
    vector.shrink_to_fit();

    for (int i = 0; i < len; i++)
        vector[i] = random<int>();

    return vector;
}

template<>
float random<float>()
{
    static std::mt19937 gen((std::random_device())());
    static std::uniform_real_distribution<float> dis;
    return dis(gen);
}

template<>
double random<double>()
{
    static std::mt19937 gen((std::random_device())());
    static std::uniform_real_distribution<double> dis;
    return dis(gen);
}

}
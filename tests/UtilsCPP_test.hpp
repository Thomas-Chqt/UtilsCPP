/*
 * ---------------------------------------------------
 * UtilsCPP_test.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/12 20:29:02
 * ---------------------------------------------------
 */

#ifndef UTILSCPP_TEST_HPP
#define UTILSCPP_TEST_HPP

#include <gtest/gtest.h>
#include <string>
#include <vector>

#define ASSERT_OR_EXPECT(ext, ...) \
    if constexpr (assert)          \
        ASSERT_##ext(__VA_ARGS__); \
    else                           \
        EXPECT_##ext(__VA_ARGS__);

namespace utl::test
{

struct std_string : public std::string
{
    using std::string::string;
};

struct std_vector_of_int : public std::vector<int>
{
    using std::vector<int>::vector;
};

struct std_vector_of_strings : public std::vector<std::string>
{
    using std::vector<std::string>::vector;
};

using TestedTypes = ::testing::Types<
    unsigned char, int, double, unsigned long long,
    std_string, std_vector_of_int, std_vector_of_strings
>;

template<typename T>
const T getTestData(unsigned int index);

template<typename T>
const std::vector<T>& getTestDataVector(unsigned int index)
{
    static std::vector<T> datas[] = {
        [index](){ std::vector<T> v; for (int i = 0; i <  0; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  1; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  2; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  3; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  4; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  5; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  6; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  7; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i <  8; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
        [index](){ std::vector<T> v; for (int i = 0; i < 30; i++) { v.push_back(getTestData<T>((index+i)%10)); } return v; }(),
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

}

#endif // UTILSCPP_TEST_HPP

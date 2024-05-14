/*
 * ---------------------------------------------------
 * SharedPtr_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/13 17:21:25
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>

#include "UtilsCPP/SharedPtr.hpp"

namespace utils_tests
{

using utils::SharedPtr;

template<typename T>
class SharedPtrTest : public testing::Test {};

using TestedTypes = ::testing::Types<
    unsigned char, int, double, unsigned long long,
    std::string, std::vector<int>
>;

TYPED_TEST_SUITE(SharedPtrTest, TestedTypes);

TYPED_TEST(SharedPtrTest, defaultConstructor)
{
    using SharedPtr = SharedPtr<TypeParam>;
    using Type      = typename SharedPtr::Type;

    SharedPtr ptr1;

    EXPECT_EQ(ptr1.m_pointer, nullptr);
    EXPECT_EQ(ptr1.m_refCount, nullptr);
}

}
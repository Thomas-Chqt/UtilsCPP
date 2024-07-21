/*
 * ---------------------------------------------------
 * Set_testCases.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2024/07/21 14:34:29
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include "UtilsCPP/Set.hpp"

namespace utils_tests
{

template<typename T>
class SetTest : public testing::Test {};

using TestedTypes = ::testing::Types<int, std::string>;

TYPED_TEST_SUITE(SetTest, TestedTypes);

TYPED_TEST(SetTest, constructor)
{
    utils::Set<TypeParam> set1;
    EXPECT_EQ(set1.size(), 0);

    utils::Set<TypeParam> set2(set1);
    EXPECT_EQ(set1.size(), 0);
}

TEST(SetTest, insert)
{
    utils::Set<int> set1;

    EXPECT_EQ(*set1.insert(1), 1);
    EXPECT_EQ(set1.size(), 1);

    EXPECT_EQ(*set1.insert(2), 2);
    EXPECT_EQ(set1.size(), 2);

    EXPECT_THROW({
        set1.insert(2);
    }, utils::Set<int>::DuplicateElementError);
}

TEST(SetTest, find)
{
    utils::Set<int> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);

    EXPECT_EQ(*set.find(1), 1);
    EXPECT_EQ(*set.find(3), 3);
    EXPECT_EQ(set.find(5), set.end());
}

}
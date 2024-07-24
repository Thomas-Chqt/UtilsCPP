/*
 * ---------------------------------------------------
 * Set_testCases.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2024/07/21 14:34:29
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include "UtilsCPP/Array.hpp"
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

    EXPECT_EQ(*set1.insert(2), 2);
    EXPECT_EQ(set1.size(), 1);

    EXPECT_EQ(*set1.insert(1), 1);
    EXPECT_EQ(set1.size(), 2);

    EXPECT_THROW({
        set1.insert(2);
    }, utils::Set<int>::DuplicateElementError);
}

TEST(SetTest, find)
{
    utils::Set<int> set;
    set.insert(1);
    set.insert(4);
    set.insert(3);
    set.insert(2);

    EXPECT_EQ(*set.find(1), 1);
    EXPECT_EQ(*set.find(3), 3);
    EXPECT_EQ(set.find(5), set.end());
}

TEST(SetTest, copy)
{
    utils::Set<int> set1;
    set1.insert(1);
    set1.insert(4);
    set1.insert(3);
    set1.insert(2);

    utils::Set<int> set2(set1);

    ASSERT_EQ(set1, set2);

    utils::Set<int> set3;
    set3 = set1;

    ASSERT_EQ(set1, set3);
}

TEST(SetTest, equal)
{
    utils::Set<int> set1;
    set1.insert(1);
    set1.insert(4);
    set1.insert(3);
    set1.insert(2);

    utils::Set<int> set2;
    set2.insert(4);
    set2.insert(1);
    set2.insert(2);
    set2.insert(3);

    utils::Set<int> set3;
    set3.insert(5);
    set3.insert(7);
    set3.insert(1);

    utils::Set<int> set4;
    set4.insert(1);
    set4.insert(3);
    set4.insert(2);

    EXPECT_TRUE(set1 == set2);
    EXPECT_FALSE(set1 == set3);
    EXPECT_FALSE(set1 == set4);
}

TEST(SetTest, iterator)
{
    utils::Array<int> arr  = {1, 2, 3, 4, 5, 6};
    utils::Set<int>   set1 = {1, 2, 3, 4, 5, 6};
    utils::Set<int>   set2 = {3, 6, 1, 5, 4, 2};

    utils::Array<int>::Iterator arrIt = arr.begin();
    utils::Set<int>::Iterator  set1It = set1.begin();
    utils::Set<int>::Iterator  set2It = set2.begin();

    for (; arrIt != arr.end(); ++arrIt, ++set1It, ++set2It)
    {
        ASSERT_EQ(*arrIt, *set1It);
        ASSERT_EQ(*arrIt, *set2It);
    }

    ASSERT_EQ(set1It, set1.end());
    ASSERT_EQ(set2It, set2.end());
}

}
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
#include "random.hpp"

namespace utils_tests
{

template<typename T>
class SetTest : public testing::Test {};

using TestedTypes = ::testing::Types<int, std::string>;

TYPED_TEST_SUITE(SetTest, TestedTypes);

TYPED_TEST(SetTest, defaultConstructor)
{
    {
        utils::Set<TypeParam> set;
        EXPECT_EQ(set.size(), 0);
    }
    {
        const utils::Set<TypeParam> set;
        EXPECT_EQ(set.size(), 0);
    }
}

TEST(SetTest, initializerListConstructor)
{
    {
        utils::Set<int> set = { 3, 6, 2 };
        EXPECT_EQ(set.size(), 3);
    }
    {
        const utils::Set<int> set = { 3, 6, 2 };
        EXPECT_EQ(set.size(), 3);
    }
}

TYPED_TEST(SetTest, insert)
{
    {
        utils::Set<TypeParam> set;
        set.insert(random<TypeParam>());
        EXPECT_EQ(set.size(), 1);
    }
    {
        utils::Set<TypeParam> set;
        TypeParam val = random<TypeParam>();
        EXPECT_EQ(*set.insert((const TypeParam&)val), val);
        EXPECT_EQ(set.size(), 1);
    }
    {
        utils::Set<TypeParam> set;
        TypeParam val = random<TypeParam>();
        EXPECT_EQ(*set.insert((const TypeParam&)val), val);
        EXPECT_THROW({ set.insert((const TypeParam&)val); }, typename utils::Set<TypeParam>::DuplicateElementError);
        EXPECT_EQ(set.size(), 1);
    }
}

TEST(SetTest, find)
{
    {
        utils::Set<int> set = {1, 4, 3, 2};

        EXPECT_EQ(*set.find(1), 1);
        EXPECT_EQ(*set.find(3), 3);
        EXPECT_EQ( set.find(5), set.end());
    }
    {
        const utils::Set<int> set = {1, 4, 3, 2};

        EXPECT_EQ(*set.find(1), 1);
        EXPECT_EQ(*set.find(3), 3);
        EXPECT_EQ( set.find(5), set.end());
    }
}

TEST(SetTest, copy)
{
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2(set1);
        ASSERT_EQ(set1, set2);
    }
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2; set2 = set1;
        ASSERT_EQ(set1, set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2(set1);
        ASSERT_EQ(set1, set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2; set2 = set1;
        ASSERT_EQ(set1, set2);
    }
}

TEST(SetTest, equal)
{
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2 = set1;
        EXPECT_TRUE(set1 == set2);
    }
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2 = {1, 4, 3, 2};
        EXPECT_TRUE(set1 == set2);
    }
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2 = {4, 1, 2, 3};
        EXPECT_TRUE(set1 == set2);
    }
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2;
        EXPECT_FALSE(set1 == set2);
    }
    {
        utils::Set<int> set1 = {1, 4, 3, 2};
        utils::Set<int> set2 = {1, 4};
        EXPECT_FALSE(set1 == set2);
    }
    // CONST
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2 = set1;
        EXPECT_TRUE(set1 == set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2 = {1, 4, 3, 2};
        EXPECT_TRUE(set1 == set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2 = {4, 1, 2, 3};
        EXPECT_TRUE(set1 == set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2;
        EXPECT_FALSE(set1 == set2);
    }
    {
        const utils::Set<int> set1 = {1, 4, 3, 2};
        const utils::Set<int> set2 = {1, 4};
        EXPECT_FALSE(set1 == set2);
    }
}

TEST(SetTest, iterator)
{
    utils::Array<int> arr  = {1, 2, 3, 4, 5, 6};
    utils::Set<int>   set1 = {1, 2, 3, 4, 5, 6};
    utils::Set<int>   set2 = {3, 6, 1, 5, 4, 2};
    const utils::Set<int>   set3 = {1, 2, 3, 4, 5, 6};
    const utils::Set<int>   set4 = {3, 6, 1, 5, 4, 2};

    utils::Array<int>::Iterator arrIt = arr.begin();
    utils::Set<int>::Iterator  set1It = set1.begin();
    utils::Set<int>::Iterator  set2It = set2.begin();
    utils::Set<int>::const_Iterator  set3It = set3.begin();
    utils::Set<int>::const_Iterator  set4It = set4.begin();

    for (; arrIt != arr.end(); ++arrIt, ++set1It, ++set2It, ++set3It, ++set4It)
    {
        ASSERT_EQ(*arrIt, *set1It);
        ASSERT_EQ(*arrIt, *set2It);
        ASSERT_EQ(*arrIt, *set3It);
        ASSERT_EQ(*arrIt, *set4It);
    }

    ASSERT_EQ(set1It, set1.end());
    ASSERT_EQ(set2It, set2.end());
    ASSERT_EQ(set3It, set3.end());
    ASSERT_EQ(set4It, set4.end());
}

TEST(SetTest, remove)
{
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35};
        set.remove(set.find(5));
        ASSERT_EQ(set.size(), 5);
        ASSERT_EQ(set.find(5), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 5);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35};
        set.remove(set.find(10));
        ASSERT_EQ(set.size(), 5);
        ASSERT_EQ(set.find(10), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 5);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35};
        set.remove(set.find(30));
        ASSERT_EQ(set.size(), 5);
        ASSERT_EQ(set.find(30), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 5);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35, 4, 6, 33, 36, 34};
        set.remove(set.find(5));
        ASSERT_EQ(set.size(), 10);
        ASSERT_EQ(set.find(5), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 10);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35, 4, 6, 33, 36, 34};
        set.remove(set.find(25));
        ASSERT_EQ(set.size(), 10);
        ASSERT_EQ(set.find(25), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 10);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35, 4, 6, 33, 36, 34};
        set.remove(set.find(30));
        ASSERT_EQ(set.size(), 10);
        ASSERT_EQ(set.find(30), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 10);
    }
    {
        utils::Set<int> set = {20, 10, 30, 5, 25, 35, 4, 6, 33, 36, 34};
        set.remove(set.find(35));
        ASSERT_EQ(set.size(), 10);
        ASSERT_EQ(set.find(35), set.end());

        utils::Set<int>::Iterator curr = set.begin();
        int prev = 0;
        int count = 0;
        for (; curr != set.end(); ++curr) {
            ASSERT_GT(*curr, prev);
            prev = *curr;
            count++;
        }
        ASSERT_EQ(count, 10);
    }
    {
        utils::Set<int> set;
        set.remove(set.begin());
        ASSERT_EQ(set.size(), 0);
        ASSERT_EQ(set.begin(), set.end());
    }
    {
        utils::Set<int> set = { 1 };
        set.remove(set.find(1));
        ASSERT_EQ(set.size(), 0);
        ASSERT_EQ(set.find(1), set.end());
        ASSERT_EQ(set.begin(), set.end());
    }
    {
        utils::Set<int> set = { 1 };
        set.remove(set.begin());
        ASSERT_EQ(set.size(), 0);
        ASSERT_EQ(set.find(1), set.end());
        ASSERT_EQ(set.begin(), set.end());
    }
}

}
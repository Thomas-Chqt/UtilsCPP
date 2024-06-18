/*
 * ---------------------------------------------------
 * Dictionary_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/21 15:17:09
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include <string>

#include "UtilsCPP/Dictionary.hpp"

namespace utils_tests
{

using utils::Dictionary;

class DictionaryTest : public testing::Test {};

TEST_F(DictionaryTest, insert)
{
    Dictionary<std::string, std::string> dic;

    dic.insert("1", "1");
    EXPECT_EQ(dic.size(), 1);
    EXPECT_TRUE(dic.contain("1"));
}

TEST_F(DictionaryTest, remove)
{
    Dictionary<std::string, std::string> dic;

    dic.insert("1", "1");
    dic.insert("2", "2");

    dic.remove("1");
 
    EXPECT_EQ(dic.size(), 1);
    EXPECT_FALSE(dic.contain("1"));
}

TEST_F(DictionaryTest, access)
{
    Dictionary<std::string, std::string> dic;

    dic.insert("1", "1");
    dic.insert("2", "2");

    EXPECT_EQ(dic["1"], "1");
    EXPECT_EQ(dic["2"], "2");

    EXPECT_ANY_THROW({ dic["33"]; });
}

TEST_F(DictionaryTest, get)
{
    Dictionary<int, std::string> dic;

    EXPECT_EQ(dic.get(1), "");
    EXPECT_EQ(dic.get(2, "val"), "val");
}

}
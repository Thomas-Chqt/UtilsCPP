/*
 * ---------------------------------------------------
 * Error_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/25 18:22:56
 * ---------------------------------------------------
 */

#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/Dictionary.hpp"
#include "UtilsCPP/String.hpp"
#include <gtest/gtest.h>

using namespace utils;

namespace utils_test
{

TEST(ErrorTest, arrayOOB)
{
    utils::Array<int> arr(5);

    for (auto i : {0, 1, 4, 5, 6})
    {
        if (i < 5)
        {
            EXPECT_NO_THROW({
                arr[i];
            });
        }
        else
        {
            EXPECT_THROW({
                arr[5];
            }, utils::Array<int>::OutOfBoundError);
        }
    }
}

TEST(ErrorTest, dictionaryErrors)
{
    Dictionary<String, String> dic;

    using DuplicateKeyError = Dictionary<String, String>::DuplicateKeyError;
    using KeyNoFoundError = Dictionary<String, String>::KeyNoFoundError;

    EXPECT_NO_THROW({
        dic.insert("a", "a");
        dic.insert("b", "b");
    });

    EXPECT_THROW({
        dic.insert("a", "a");
    }, DuplicateKeyError);

    EXPECT_THROW({
        dic["c"];
    }, KeyNoFoundError);
}

}
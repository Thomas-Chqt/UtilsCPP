/*
 * ---------------------------------------------------
 * SmartPointer_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/24 13:24:10
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include <vector>

#include "UtilsCPP/SharedPtr.hpp"
#include "UtilsCPP/UniquePtr.hpp"

namespace utils_tests
{

TEST(SmartPointerTest, SharedPtrBase)
{
    std::vector<utils::UniquePtr<utils::SharedPtrBase>> vector;

    utils::SharedPtr<int> ptr1(new int);
    vector.push_back(utils::UniquePtr<utils::SharedPtrBase>(new utils::SharedPtr<int>(ptr1)));

    {
        utils::SharedPtr<int> ptr2(new int);
        vector.push_back(utils::UniquePtr<utils::SharedPtrBase>(new utils::SharedPtr<int>(ptr2)));
    }
}

}
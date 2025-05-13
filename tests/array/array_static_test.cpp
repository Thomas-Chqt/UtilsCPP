/*
 * ---------------------------------------------------
 * array_static_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/11 10:24:27
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include "array_test.hpp"
#include <iterator>
#include "UtilsCPP/Array.hpp"

namespace utl::test
{

TYPED_TEST(ArrayTestStatic, static)
{
    static_assert(std::random_access_iterator<typename Array<TypeParam>::Iterator>);
    static_assert(std::random_access_iterator<typename Array<TypeParam>::const_Iterator>);
    SUCCEED();
}

}


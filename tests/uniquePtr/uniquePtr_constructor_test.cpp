/*
 * ---------------------------------------------------
 * uniquePtr_constructor_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/25 21:47:50
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <type_traits>
#include "uniquePtr_test.hpp"
#include "UtilsCPP/memory.hpp"

namespace utl::test
{

TYPED_TEST(uniquePtrTest, defaultConstructor)
{
    new (&this->utlUniquePtr) utl::unique_ptr<TypeParam>;
    new (&this->stdUniquePtr) std::unique_ptr<TypeParam>;

    this->identityTest();
}

}

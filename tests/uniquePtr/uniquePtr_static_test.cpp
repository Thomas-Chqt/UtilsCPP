/*
 * ---------------------------------------------------
 * uniquePtr_static_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/25 16:42:13
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include <type_traits>
#include "uniquePtr_test.hpp"
#include "UtilsCPP/memory.hpp"

namespace utl::test
{

TYPED_TEST(uniquePtrTestStatic, copyConstructor)
{
    static_assert(!std::is_copy_constructible_v<utl::unique_ptr<TypeParam>>, "unique_ptr connot be copy constructible");
}

TYPED_TEST(uniquePtrTestStatic, copyAssignment)
{
    static_assert(!std::is_copy_assignable_v<utl::unique_ptr<TypeParam>>, "unique_ptr connot be copy assignable");
}

}

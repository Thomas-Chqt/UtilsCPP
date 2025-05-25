/*
 * ---------------------------------------------------
 * uniquePtr_constructor_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/25 21:47:50
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include <algorithm>
#include <gtest/gtest.h>
#include "UtilsCPP_test.hpp"
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

TYPED_TEST(uniquePtrTest, pointerConstructor)
{
    auto* ptr = new TypeParam(getTestData<TypeParam>(1));

    new (&this->utlUniquePtr) utl::unique_ptr<TypeParam>(ptr);
    new (&this->stdUniquePtr) std::unique_ptr<TypeParam>(ptr);

    this->identityTest();
    this->stdUniquePtr.release(); // bad
}

TYPED_TEST(uniquePtrTest, moveConstrctor1)
{
    utl::unique_ptr<TypeParam> utl;
    std::unique_ptr<TypeParam> std;

    new (&this->utlUniquePtr) utl::unique_ptr(std::move(utl));
    new (&this->stdUniquePtr) std::unique_ptr(std::move(std));

    this->identityTest();
}

TYPED_TEST(uniquePtrTest, moveConstrctor2)
{
    auto* ptr = new TypeParam(getTestData<TypeParam>(1));

    auto utl = utl::unique_ptr<TypeParam>(ptr);
    auto std = std::unique_ptr<TypeParam>(ptr);

    new (&this->utlUniquePtr) utl::unique_ptr(std::move(utl));
    new (&this->stdUniquePtr) std::unique_ptr(std::move(std));

    this->identityTest();
    this->stdUniquePtr.release(); // bad
}

}

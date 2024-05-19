/*
 * ---------------------------------------------------
 * SharedPtr_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/13 17:21:25
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>

#include "UtilsCPP/SharedPtr.hpp"

namespace utils_tests
{

using utils::SharedPtr;

template<typename T>
class SharedPtrTest : public testing::Test {};

using TestedTypes = ::testing::Types<
    unsigned char, int, double, unsigned long long,
    std::string, std::vector<int>
>;

TYPED_TEST_SUITE(SharedPtrTest, TestedTypes);

TYPED_TEST(SharedPtrTest, defaultConstructor)
{
    using SharedPtr = SharedPtr<TypeParam>;
    using Type      = typename SharedPtr::Type;

    SharedPtr ptr1;

    EXPECT_EQ((TypeParam*)ptr1, nullptr);
    EXPECT_EQ(ptr1.refCount(), 0);
}

TYPED_TEST(SharedPtrTest, copyConstructor)
{
    using SharedPtr = SharedPtr<TypeParam>;
    using Type      = typename SharedPtr::Type;

    SharedPtr ptr1 = SharedPtr(new TypeParam);

    {
        SharedPtr ptr2(ptr1);
        EXPECT_EQ((TypeParam*)ptr2, (TypeParam*)ptr1);
        EXPECT_EQ(ptr2.refCount(), 2);
        EXPECT_EQ(ptr1.refCount(), 2);
    }

    EXPECT_EQ(ptr1.refCount(), 1);
}

TEST(SharedPtrTest, dynamicCastSuccess)
{
    using utils::SharedPtr;

    struct Base { int nbr = 3; virtual ~Base() = default; };
    struct Derived : public Base { int nbr = 3; ~Derived() override = default; };

    SharedPtr<Base>    basePtr    = SharedPtr<Base>(new Derived);
    SharedPtr<Derived> derivedPtr = basePtr.dynamicCast<Derived>();

    EXPECT_TRUE(basePtr == true);
    EXPECT_EQ(basePtr.refCount(), 2);

    EXPECT_TRUE(derivedPtr == true);
    EXPECT_EQ(derivedPtr.refCount(), 2);
}

TEST(SharedPtrTest, dynamicCastFail)
{
    using utils::SharedPtr;

    struct Base { int nbr = 3; virtual ~Base() = default; };
    struct Derived : public Base { int nbr = 3; ~Derived() override = default; };

    SharedPtr<Base>    basePtr    = SharedPtr<Base>(new Base);
    SharedPtr<Derived> derivedPtr = basePtr.dynamicCast<Derived>();

    EXPECT_TRUE(basePtr == true);
    EXPECT_EQ(basePtr.refCount(), 1);

    EXPECT_TRUE(derivedPtr == false);
}

}
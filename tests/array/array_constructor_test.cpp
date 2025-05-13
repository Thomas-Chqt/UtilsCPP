/*
 * ---------------------------------------------------
 * array_constructor_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/03/03 18:57:31
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "UtilsCPP_test.hpp"
#include "array_test.hpp"
#include "UtilsCPP/Array.hpp"
#include <vector>

namespace utl::test
{

TYPED_TEST(ArrayTest, defaultConstructor)
{
    new (&this->m_array) Array<TypeParam>;
    new (&this->m_identityVector) std::vector<TypeParam>;
    this->identityTest();
}

#define COPY_CONSTRUCTOR_TEST_BODY                                         \
    {                                                                      \
        Array<TypeParam> array = this->m_array;                            \
        std::vector<TypeParam> vector = this->m_identityVector;            \
        this->integrityTest(); /* this->m_array should not have changed */ \
        this->identityTest();                                              \
        EXPECT_EQ(array.size(), vector.size());                            \
        EXPECT_EQ(array.capacity(), vector.capacity());                    \
        for (int i = 0; auto& e : array)                                   \
            EXPECT_EQ(array[i], vector[i]);                                \
    }

TYPED_TEST(ArrayTestOnDefaultArray, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnDefaultConstArray, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData1, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData1, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData10, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData10, copyConstructor)
COPY_CONSTRUCTOR_TEST_BODY

#define MOVE_CONSTRUCTOR_TEST_BODY                                         \
    {                                                                      \
        Array<TypeParam> array = std::move(this->m_array);                 \
        std::vector<TypeParam> vector = std::move(this->m_identityVector); \
        this->identityTest();                                              \
        EXPECT_EQ(array.size(), vector.size());                            \
        EXPECT_EQ(array.capacity(), vector.capacity());                    \
        for (int i = 0; auto& e : array)                                   \
            EXPECT_EQ(array[i], vector[i]);                                \
    }

TYPED_TEST(ArrayTestOnDefaultArray, moveConstructor)
MOVE_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData1, moveConstructor)
MOVE_CONSTRUCTOR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData10, moveConstructor)
MOVE_CONSTRUCTOR_TEST_BODY

#define LENGTH_CONSTRUCTOR_DEFAULT_ELEMENT_TEST_BODY(n)          \
    {                                                            \
        new (&this->m_array) Array<TypeParam>(n);                \
        new (&this->m_identityVector) std::vector<TypeParam>(n); \
        this->identityTest();                                    \
    }

TYPED_TEST(ArrayTest, lengthConstructorDefaultElementEmpty)
LENGTH_CONSTRUCTOR_DEFAULT_ELEMENT_TEST_BODY(0)

TYPED_TEST(ArrayTest, lengthConstructorDefaultElementNotEmpty1)
LENGTH_CONSTRUCTOR_DEFAULT_ELEMENT_TEST_BODY(1)

TYPED_TEST(ArrayTest, lengthConstructorDefaultElementNotEmpty2)
LENGTH_CONSTRUCTOR_DEFAULT_ELEMENT_TEST_BODY(4)

TYPED_TEST(ArrayTest, lengthConstructorDefaultElementNotEmpty3)
LENGTH_CONSTRUCTOR_DEFAULT_ELEMENT_TEST_BODY(9)

#define LENGTH_CONSTRUCTOR_COPY_ELEMENT_TEST_BODY(n)                                        \
    {                                                                                       \
        new (&this->m_array) Array<TypeParam>(n, getTestData<TypeParam>(n));                \
        new (&this->m_identityVector) std::vector<TypeParam>(n, getTestData<TypeParam>(n)); \
        this->identityTest();                                                               \
    }

TYPED_TEST(ArrayTest, lengthConstructorCopyElementEmpty)
LENGTH_CONSTRUCTOR_COPY_ELEMENT_TEST_BODY(0)

TYPED_TEST(ArrayTest, lengthConstructorCopyElementNotEmpty1)
LENGTH_CONSTRUCTOR_COPY_ELEMENT_TEST_BODY(1)

TYPED_TEST(ArrayTest, lengthConstructorCopyElementNotEmpty2)
LENGTH_CONSTRUCTOR_COPY_ELEMENT_TEST_BODY(4)

TYPED_TEST(ArrayTest, lengthConstructorCopyElementNotEmpty3)
LENGTH_CONSTRUCTOR_COPY_ELEMENT_TEST_BODY(9)

#define ITERATOR_CONSTRUCTOR_TEST_BODY(n)                                                                                                     \
    {                                                                                                                                         \
        new (&this->m_array) Array<TypeParam>(getTestDataVector<TypeParam>(n).begin(), getTestDataVector<TypeParam>(n).end());                \
        new (&this->m_identityVector) std::vector<TypeParam>(getTestDataVector<TypeParam>(n).begin(), getTestDataVector<TypeParam>(n).end()); \
        this->identityTest();                                                                                                                 \
    }

TYPED_TEST(ArrayTest, iteratorConstructorEmpty)
ITERATOR_CONSTRUCTOR_TEST_BODY(0)

TYPED_TEST(ArrayTest, iteratorConstructorNotEmpty1)
ITERATOR_CONSTRUCTOR_TEST_BODY(1)

TYPED_TEST(ArrayTest, iteratorConstructorNotEmpty2)
ITERATOR_CONSTRUCTOR_TEST_BODY(4)

TYPED_TEST(ArrayTest, iteratorConstructorNotEmpty3)
ITERATOR_CONSTRUCTOR_TEST_BODY(9)

#define INIT_LIST_CONSTRUCTOR_TEST_BODY(...)                                 \
    {                                                                        \
        new (&this->m_array) Array<TypeParam>({__VA_ARGS__});                \
        new (&this->m_identityVector) std::vector<TypeParam>({__VA_ARGS__}); \
        this->identityTest();                                                \
    }

TYPED_TEST(ArrayTest, initListConstructorEmpty)
INIT_LIST_CONSTRUCTOR_TEST_BODY()

TYPED_TEST(ArrayTest, initListConstructorNotEmpty1)
INIT_LIST_CONSTRUCTOR_TEST_BODY(
    getTestData<TypeParam>(1),
    getTestData<TypeParam>(2),
    getTestData<TypeParam>(3),
    getTestData<TypeParam>(4))

TYPED_TEST(ArrayTest, initListConstructorNotEmpty2)
INIT_LIST_CONSTRUCTOR_TEST_BODY(
    getTestData<TypeParam>(5),
    getTestData<TypeParam>(6),
    getTestData<TypeParam>(7),
    getTestData<TypeParam>(8),
    getTestData<TypeParam>(9))

} // namespace utl::test

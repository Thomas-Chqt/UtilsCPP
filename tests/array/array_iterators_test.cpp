/*
 * ---------------------------------------------------
 * array_iterators_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/12 20:23:31
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "array_test.hpp"

namespace utl::test
{

#define ITERATOR_BEGIN_TEST_BODY                                             \
    {                                                                        \
        if (this->m_array.size() == 0 && this->m_identityVector.size() == 0) \
        {                                                                    \
            auto arrIt = this->m_array.begin();                              \
            auto vecIt = this->m_identityVector.begin();                     \
            EXPECT_EQ(arrIt, this->m_array.end());                           \
            EXPECT_EQ(vecIt, this->m_identityVector.end());                  \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            auto arrIt = this->m_array.begin();                              \
            auto vecIt = this->m_identityVector.begin();                     \
            EXPECT_EQ(*arrIt, *vecIt);                                       \
        }                                                                    \
        this->identityTest();                                                \
        this->integrityTest();                                               \
    }

TYPED_TEST(ArrayTestOnDefaultArray, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

TYPED_TEST(ArrayTestOnDefaultConstArray, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData1, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData1, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData11, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData11, iteratorBegin)
ITERATOR_BEGIN_TEST_BODY

#define ITERATOR_END_TEST_BODY                                                            \
    {                                                                                     \
        auto sz = this->m_array.size();                                                   \
        auto arrIt = this->m_array.end();                                                 \
        auto vecIt = this->m_identityVector.end();                                        \
        if (sz > 0)                                                                       \
            EXPECT_EQ(*(arrIt - 1), *(vecIt - 1));                                        \
        EXPECT_EQ(arrIt, this->m_array.begin() + this->m_array.size());                   \
        EXPECT_EQ(vecIt, this->m_identityVector.begin() + this->m_identityVector.size()); \
        this->identityTest();                                                             \
        this->integrityTest();                                                            \
    } // namespace utl::test

TYPED_TEST(ArrayTestOnDefaultArray, iteratorEnd)
ITERATOR_END_TEST_BODY

TYPED_TEST(ArrayTestOnDefaultConstArray, iteratorEnd)
ITERATOR_END_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData1, iteratorEnd)
ITERATOR_END_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData1, iteratorEnd)
ITERATOR_END_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData11, iteratorEnd)
ITERATOR_END_TEST_BODY

TYPED_TEST(ArrayTestOnConstArrayWithData11, iteratorEnd)
ITERATOR_END_TEST_BODY

} // namespace utl::test

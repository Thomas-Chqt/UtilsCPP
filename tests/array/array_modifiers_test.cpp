/*
 * ---------------------------------------------------
 * array_modifiers_test.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/10 07:42:24
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include <cassert>
#include <gtest/gtest.h>
#include <iterator>
#include "array_test.hpp"
#include "UtilsCPP_test.hpp"

namespace utl::test
{

#define APPEND_COPY_TEST_BODY(i)                       \
    {                                                  \
        TypeParam element = getTestData<TypeParam>(i); \
        this->m_array.append(element);                 \
        this->m_identityVector.push_back(element);     \
        this->identityTest();                          \
    }

TYPED_TEST(ArrayTestOnDefaultArray, pushBackCopy1)
APPEND_COPY_TEST_BODY(0)

TYPED_TEST(ArrayTestOnDefaultArray, pushBackCopy2)
APPEND_COPY_TEST_BODY(9)

TYPED_TEST(ArrayTestOnArrayWithData1, pushBackCopy1)
APPEND_COPY_TEST_BODY(0)

TYPED_TEST(ArrayTestOnArrayWithData1, pushBackCopy2)
APPEND_COPY_TEST_BODY(9)

TYPED_TEST(ArrayTestOnArrayWithData8, pushBackCopy1)
APPEND_COPY_TEST_BODY(0)

TYPED_TEST(ArrayTestOnArrayWithData8, pushBackCopy2)
APPEND_COPY_TEST_BODY(9)

#define APPEND_MOVE_TEST_BODY(i)                                  \
    {                                                             \
        {                                                         \
            TypeParam element = getTestData<TypeParam>(i);        \
            this->m_array.append(std::move(element));             \
        }                                                         \
        {                                                         \
            TypeParam element = getTestData<TypeParam>(i);        \
            this->m_identityVector.push_back(std::move(element)); \
        }                                                         \
        this->identityTest();                                     \
    }

TYPED_TEST(ArrayTestOnDefaultArray, appendMove1)
APPEND_MOVE_TEST_BODY(0)

TYPED_TEST(ArrayTestOnDefaultArray, appendMove2)
APPEND_MOVE_TEST_BODY(9)

TYPED_TEST(ArrayTestOnArrayWithData1, appendMove1)
APPEND_MOVE_TEST_BODY(0)

TYPED_TEST(ArrayTestOnArrayWithData1, appendMove2)
APPEND_MOVE_TEST_BODY(9)

TYPED_TEST(ArrayTestOnArrayWithData8, appendMove1)
APPEND_MOVE_TEST_BODY(0)

TYPED_TEST(ArrayTestOnArrayWithData8, appendMove2)
APPEND_MOVE_TEST_BODY(9)

#define ERASE_FRONT_TEST_BODY                                                          \
    {                                                                                  \
        if (this->m_array.size() == 1 && this->m_identityVector.size() == 1)           \
        {                                                                              \
            auto arrIt = this->m_array.erase(this->m_array.begin());                   \
            auto vecIt = this->m_identityVector.erase(this->m_identityVector.begin()); \
            EXPECT_EQ(arrIt, this->m_array.end());                                     \
            EXPECT_EQ(vecIt, this->m_identityVector.end());                            \
        }                                                                              \
        else                                                                           \
        {                                                                              \
            auto arrIt = this->m_array.erase(this->m_array.begin());                   \
            auto vecIt = this->m_identityVector.erase(this->m_identityVector.begin()); \
            EXPECT_EQ(*arrIt, *vecIt);                                                 \
        }                                                                              \
        this->identityTest();                                                          \
    }

TYPED_TEST(ArrayTestOnArrayWithData1, eraseFront)
ERASE_FRONT_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData3, eraseFront)
ERASE_FRONT_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData6, eraseFront)
ERASE_FRONT_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData10, eraseFront)
ERASE_FRONT_TEST_BODY

#define ERASE_MID_TEST_BODY(i)                                                                   \
    {                                                                                            \
        assert(this->m_array.size() > (i) + 1);                                                  \
        assert(this->m_identityVector.size() > (i) + 1);                                         \
                                                                                                 \
        auto arrIt = this->m_array.erase(std::next(this->m_array.begin(), i));                   \
        auto vecIt = this->m_identityVector.erase(std::next(this->m_identityVector.begin(), i)); \
        EXPECT_EQ(*arrIt, *vecIt);                                                               \
        this->identityTest();                                                                    \
    }

TYPED_TEST(ArrayTestOnArrayWithData3, eraseMid)
ERASE_MID_TEST_BODY(1)

TYPED_TEST(ArrayTestOnArrayWithData6, eraseMid)
ERASE_MID_TEST_BODY(3)

TYPED_TEST(ArrayTestOnArrayWithData10, eraseMid)
ERASE_MID_TEST_BODY(5)

#define ERASE_BACK_TEST_BODY                                                                \
    {                                                                                       \
        auto arrIt = this->m_array.erase(std::prev(this->m_array.end()));                   \
        auto vecIt = this->m_identityVector.erase(std::prev(this->m_identityVector.end())); \
        EXPECT_EQ(arrIt, this->m_array.end());                                              \
        EXPECT_EQ(vecIt, this->m_identityVector.end());                                     \
        this->identityTest();                                                               \
    }

TYPED_TEST(ArrayTestOnArrayWithData1, eraseBack)
ERASE_BACK_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData3, eraseBack)
ERASE_BACK_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData6, eraseBack)
ERASE_BACK_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData10, eraseBack)
ERASE_BACK_TEST_BODY

#define CLEAR_TEST_BODY                 \
    {                                   \
        this->m_array.clear();          \
        this->m_identityVector.clear(); \
        this->identityTest();           \
    }

TYPED_TEST(ArrayTestOnDefaultArray, clear)
CLEAR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData1, clear)
CLEAR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData3, clear)
CLEAR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData8, clear)
CLEAR_TEST_BODY

TYPED_TEST(ArrayTestOnArrayWithData10, clear)
CLEAR_TEST_BODY

} // namespace utl::test

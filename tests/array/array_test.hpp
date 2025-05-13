/*
 * ---------------------------------------------------
 * array_test.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/02/20 14:23:10
 * ---------------------------------------------------
 */

#ifndef ARRAYTEST_HPP
#define ARRAYTEST_HPP

#include <gtest/gtest.h>
#include "UtilsCPP_test.hpp"
#include "UtilsCPP/Array.hpp"
#include <vector>

#define ARRAY_TEST_FIXITURE_CONST_VERSION(className, baseClasseName) \
    template<typename T>                                             \
    class className : public baseClasseName<T>                       \
    {                                                                \
    protected:                                                       \
        className() : m_array(baseClasseName<T>::m_array) {}         \
        using baseClasseName<T>::SetUp;                              \
        ~className() override = default;                             \
        const Array<T>& m_array;                                     \
    };

#define ASSERT_OR_EXPECT(ext, ...) \
    if (assert)                    \
        ASSERT_##ext(__VA_ARGS__); \
    else                           \
        EXPECT_##ext(__VA_ARGS__); \


namespace utl::test
{

template<typename T>
class ArrayTestStatic : public testing::Test {};
TYPED_TEST_SUITE(ArrayTestStatic, TestedTypes);

template<typename T>
class ArrayTest : public testing::Test
{
protected:
    ArrayTest()
        : m_array(*reinterpret_cast<Array<T>*>(m_arrayBuff)),
          m_identityVector(*reinterpret_cast<std::vector<T>*>(m_identityVectorBuff))
    {
    }

    void SetUp() override
    {
    }


    void identityTest(bool assert = false) // test if m_array is identical to m_identityVector
    {
        ASSERT_OR_EXPECT(EQ, this->m_array.size(),     this->m_identityVector.size());
        ASSERT_OR_EXPECT(EQ, this->m_array.capacity(), this->m_identityVector.capacity());
        for (int i = 0; auto& e : m_array) {
            ASSERT_OR_EXPECT(EQ, this->m_array[i], this->m_identityVector[i]);
        }
    }

    ~ArrayTest() override
    {
        m_array.~Array();
        m_identityVector.~vector();
    }

    Array<T>& m_array;
    std::vector<T>& m_identityVector; // applied the same call, use to compare with std::vector

private:
    alignas(Array<T>) std::byte m_arrayBuff[sizeof(Array<T>)] = {};
    alignas(std::vector<T>) std::byte m_identityVectorBuff[sizeof(std::vector<T>)] = {};
};
TYPED_TEST_SUITE(ArrayTest, TestedTypes);

template<typename T>
class ArrayTestOnDefaultArray : public ArrayTest<T>
{
protected:
    ArrayTestOnDefaultArray()
        : m_integrityArray(*reinterpret_cast<Array<T>*>(m_intgrityArrayBuff))
    {
    }   

    void SetUp() override
    {
        ArrayTest<T>::SetUp();

        new (&this->m_array) Array<T>;
        new (&this->m_integrityArray) Array<T>;
        new (&this->m_identityVector) std::vector<T>;

        this->integrityTest(true);
        this->identityTest(true);
    }

    void integrityTest(bool assert = false) // test if m_array is identical to m_intgrityArray
    {
        ASSERT_OR_EXPECT(EQ, this->m_array.size(),     this->m_integrityArray.size());
        ASSERT_OR_EXPECT(EQ, this->m_array.capacity(), this->m_integrityArray.capacity());
        for (int i = 0; auto& e : this->m_array) {
            ASSERT_OR_EXPECT(EQ, this->m_array[i], this->m_integrityArray[i]);
        }
    }

    ~ArrayTestOnDefaultArray() override
    {
        m_integrityArray.~Array();
    }


    Array<T>& m_integrityArray; // use to check if nothings changed

private:
    alignas(Array<T>) std::byte m_intgrityArrayBuff[sizeof(Array<T>)] = {};
};
TYPED_TEST_SUITE(ArrayTestOnDefaultArray, TestedTypes);

ARRAY_TEST_FIXITURE_CONST_VERSION(ArrayTestOnDefaultConstArray, ArrayTestOnDefaultArray)
TYPED_TEST_SUITE(ArrayTestOnDefaultConstArray, TestedTypes);

template<typename T, std::size_t sz>
class ArrayTestOnArrayWithData : public ArrayTestOnDefaultArray<T>
{
protected:
    ArrayTestOnArrayWithData() = default;

    void SetUp() override
    {
        ArrayTestOnDefaultArray<T>::SetUp();

        for (int i = 0; i < sz; i++)
        {
            this->m_array.push_back(getTestData<T>(i % 10));
            this->m_integrityArray.push_back(getTestData<T>(i % 10));
            this->m_identityVector.push_back(getTestData<T>(i % 10));
        }

        this->integrityTest(true);
        this->identityTest(true);
    }

    ~ArrayTestOnArrayWithData() override = default;
};

#define ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(sz)                                                     \
    template<typename T>                                                                               \
    using ArrayTestOnArrayWithData##sz = ArrayTestOnArrayWithData<T, sz>;                              \
    TYPED_TEST_SUITE(ArrayTestOnArrayWithData##sz, TestedTypes);                                       \
    ARRAY_TEST_FIXITURE_CONST_VERSION(ArrayTestOnConstArrayWithData##sz, ArrayTestOnArrayWithData##sz) \
    TYPED_TEST_SUITE(ArrayTestOnConstArrayWithData##sz, TestedTypes);

ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(1)
ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(3)
ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(6)
ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(8)
ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(10)
ARRAY_TEST_ON_ARRAY_WITH_DATA_FIXITURE(11)

}

#endif // ARRAYTEST_HPP

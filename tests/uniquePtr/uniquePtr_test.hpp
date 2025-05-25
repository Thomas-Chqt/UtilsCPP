/*
 * ---------------------------------------------------
 * uniquePtr_test.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/25 16:40:30
 * ---------------------------------------------------
 */

#include "gtest/gtest.h"
#include <cassert>
#include <gtest/gtest.h>
#include "UtilsCPP/memory.hpp"
#include "UtilsCPP_test.hpp"

namespace utl::test
{

template<typename T>
class uniquePtrTest : public testing::Test
{
protected:
    uniquePtrTest()
        : utlUniquePtr(*reinterpret_cast<utl::unique_ptr<T>*>(m_utlUniquePtrBuff)),
          stdUniquePtr(*reinterpret_cast<std::unique_ptr<T>*>(m_stdUniquePtrBuff))
    {
    }

    void SetUp() override {}

    template<bool assert = false>
    void identityTest()
    {
        ASSERT_OR_EXPECT(EQ, utlUniquePtr.get(), stdUniquePtr.get())
    }

    ~uniquePtrTest() override
    {
        utlUniquePtr.~unique_ptr();
        stdUniquePtr.~unique_ptr();
    }

    utl::unique_ptr<T>& utlUniquePtr;
    std::unique_ptr<T>& stdUniquePtr;

private:
    alignas(utl::unique_ptr<T>) std::byte m_utlUniquePtrBuff[sizeof(utl::unique_ptr<T>)] = {};
    alignas(std::unique_ptr<T>) std::byte m_stdUniquePtrBuff[sizeof(std::unique_ptr<T>)] = {};
};
TYPED_TEST_SUITE(uniquePtrTest, TestedTypes);

template<typename T>
class uniquePtrTestStatic : public testing::Test {};
TYPED_TEST_SUITE(uniquePtrTestStatic, TestedTypes);

template<typename T>
class uniquePtrTestOnDefaultPtr : public uniquePtrTest<T>
{
protected:
    uniquePtrTestOnDefaultPtr()
        : integrityUniquePtr(*reinterpret_cast<utl::unique_ptr<T>>(m_integrityUniquePtrBuff))
    {
    }

    void SetUp() override
    {
        uniquePtrTest<T>::SetUp();

        new (&this->utlUniquePtr) utl::unique_ptr<T>;
        new (&this->stdUniquePtr) std::unique_ptr<T>;
        new (&this->integrityUniquePtr) utl::unique_ptr<T>;

        this->template integrityTest<true>();
        this->template identityTest<true>();
    }

    template<bool assert = false>
    void integrityTest()
    {
        ASSERT_OR_EXPECT(EQ, this->utlUniquePtr.get(), integrityUniquePtr.get())
    }

    ~uniquePtrTestOnDefaultPtr()
    {
        integrityUniquePtr.~unique_ptr();
    }

    utl::unique_ptr<T>& integrityUniquePtr;

private:
    alignas(utl::unique_ptr<T>) std::byte m_integrityUniquePtrBuff[sizeof(utl::unique_ptr<T>)] = {};
};
TYPED_TEST_SUITE(uniquePtrTestOnDefaultPtr, TestedTypes);

} // namespace utl::test

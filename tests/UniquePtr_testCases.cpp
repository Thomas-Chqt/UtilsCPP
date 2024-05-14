/*
 * ---------------------------------------------------
 * test_uniquePtr.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 17:18:48
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>

#include "UtilsCPP/UniquePtr.hpp"
#include "./random.hpp"

namespace utils_tests
{

template<typename T>
class UniquePtr : public testing::Test
{
public:
    UniquePtr() : pointer(*reinterpret_cast<utils::UniquePtr<T>*>(pointerBytes)),
                  nullPointer(*reinterpret_cast<utils::UniquePtr<T>*>(nullPointerBytes))
    {
        pointer.m_pointer = new T();
        nullPointer.m_pointer = nullptr;
    }

    ~UniquePtr()
    {
        delete pointer.m_pointer;
    }

private:
    unsigned char pointerBytes[sizeof(utils::UniquePtr<T>)] = {};
    unsigned char nullPointerBytes[sizeof(utils::UniquePtr<T>)] = {};

protected:
    utils::UniquePtr<T>& pointer;
    utils::UniquePtr<T>& nullPointer;
};

using TestedTypes = ::testing::Types<
    unsigned char, int, double, unsigned long long,
    std::string, std::vector<int>
>;

TYPED_TEST_SUITE(UniquePtr, TestedTypes);

TYPED_TEST(UniquePtr, defaultConstructor)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    unsigned char bytes[sizeof(UniquePtr)] = {};
    UniquePtr& pointer = *reinterpret_cast<UniquePtr*>(bytes);

    new (&pointer) UniquePtr();
    EXPECT_EQ(pointer.m_pointer, nullptr);
}

TYPED_TEST(UniquePtr, copyConstructor)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    static_assert(!std::is_copy_constructible<UniquePtr>::value, "UniquePtr should not be copy constructible");
}

TYPED_TEST(UniquePtr, moveConstructor)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    for (auto& ptr : std::vector<UniquePtr*>{ &this->pointer, &this->nullPointer })
    {
        unsigned char bytes[sizeof(UniquePtr)] = {};
        UniquePtr& pointer = *reinterpret_cast<UniquePtr*>(bytes);

        Type* rawPtr = (*ptr).m_pointer;
        new (&pointer) UniquePtr(std::move(*ptr));

        EXPECT_EQ(pointer.m_pointer, rawPtr);
        EXPECT_EQ((*ptr).m_pointer,  nullptr);

        delete pointer.m_pointer;
    }
}

TYPED_TEST(UniquePtr, makeUnique)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    EXPECT_NE(utils::makeUnique<TypeParam>().m_pointer, nullptr);

    for (auto& data : { random<TypeParam>(), random<TypeParam>(), random<TypeParam>() })
        EXPECT_EQ(*utils::makeUnique<TypeParam>(data).m_pointer, data);
}

TYPED_TEST(UniquePtr, clear)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    this->pointer.clear();
    EXPECT_EQ(this->pointer.m_pointer, nullptr);
    this->nullPointer.clear();
    EXPECT_EQ(this->nullPointer.m_pointer, nullptr);
}


TYPED_TEST(UniquePtr, copyAssignementOperator)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    static_assert(!std::is_copy_assignable<UniquePtr>::value, "UniquePtr should not be copy assignable");
}

TYPED_TEST(UniquePtr, moveAssignementOperator)
{
    using UniquePtr = utils::UniquePtr<TypeParam>;
    using Type      = typename UniquePtr::Type;

    for (auto& ptr : std::vector<UniquePtr*>{ &this->pointer, &this->nullPointer })
    {{
        unsigned char bytes[sizeof(UniquePtr)] = {};
        UniquePtr& pointer = *reinterpret_cast<UniquePtr*>(bytes);
        pointer.m_pointer = nullptr;

        Type* rawPtr = (*ptr).m_pointer;
        pointer = std::move(*ptr);

        EXPECT_EQ(pointer.m_pointer, rawPtr);
        EXPECT_EQ((*ptr).m_pointer,  nullptr);

        delete pointer.m_pointer;
    }{
        unsigned char bytes[sizeof(UniquePtr)] = {};
        UniquePtr& pointer = *reinterpret_cast<UniquePtr*>(bytes);
        pointer.m_pointer = new TypeParam(random<TypeParam>());

        Type* rawPtr = (*ptr).m_pointer;
        pointer = std::move(*ptr);

        EXPECT_EQ(pointer.m_pointer, rawPtr);
        EXPECT_EQ((*ptr).m_pointer,  nullptr);

        delete pointer.m_pointer;
    }}
}

}
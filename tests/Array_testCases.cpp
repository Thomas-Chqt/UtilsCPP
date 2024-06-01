/*
 * ---------------------------------------------------
 * Array_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/04/22 04:12:52
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>
#include <list>

#include "UtilsCPP/Array.hpp"
#include "./random.hpp"
#include "UtilsCPP/Types.hpp"

namespace utils_tests
{

using utils::Array;

template<typename T>
class ArrayTest : public testing::Test
{
public:
    using Element = typename Array<T>::Element;
    using Size    = typename Array<T>::Size;
    using Index   = typename Array<T>::Index;

public:
    ArrayTest() : m_array(*reinterpret_cast<Array<T>*>(m_arrayBytes)), m_constArray(*reinterpret_cast<const Array<T>*>(m_constArrayBytes))
    {
    }

    template<typename Y>
    void test(const Y& fn)
    {
        struct data { Size length; Size capacity; };
        for (data input : {(data){0, 1}, (data){1, 2}, (data){3, 4}, (data){128, 255}, (data){3152, 3152}})
        {
            m_array.m_length = input.length;
            m_array.m_capacity = input.capacity;
            m_array.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

            Array<T>& editableConstArray = *reinterpret_cast<Array<T>*>(m_constArrayBytes);

            editableConstArray.m_length = input.length;
            editableConstArray.m_capacity = input.capacity;
            editableConstArray.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

            m_vector.resize(m_array.m_length);
            m_vector.reserve(m_array.m_capacity);

            for (int i = 0; i < m_array.m_length; i++)
            {
                m_vector[i] = T(random<T>());
                new (m_array.m_buffer + i) T(m_vector[i]);
                new (editableConstArray.m_buffer + i) T(m_vector[i]);
            }

            fn();

            m_vector.clear();
            
            if (m_array.m_buffer != nullptr)
            {
                for (Size i = 0; i < m_array.m_length; ++i)
                    m_array.m_buffer[i].~Element();
                operator delete (m_array.m_buffer);
            }
            if (editableConstArray.m_buffer != nullptr)
            {
                for (Size i = 0; i < editableConstArray.m_length; ++i)
                    editableConstArray.m_buffer[i].~Element();
                operator delete (editableConstArray.m_buffer);
            }
        }
    }

private:
    unsigned char m_arrayBytes[sizeof(Array<T>)] = {};
    unsigned char m_constArrayBytes[sizeof(Array<T>)] = {};

public:
    Array<T>& m_array;
    const Array<T>& m_constArray;
    std::vector<T> m_vector;
};

using TestedTypes = ::testing::Types<
    unsigned char, int, double, unsigned long long,
    std::string, std::vector<int>
>;

TYPED_TEST_SUITE(ArrayTest, TestedTypes);

TYPED_TEST(ArrayTest, defaultConstructor)
{
    unsigned char bytes[sizeof(Array<TypeParam>)] = {};
    new (bytes) Array<TypeParam>;
    Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

    EXPECT_EQ(array.m_length,   0);
    EXPECT_EQ(array.m_capacity, 1);
    EXPECT_NE(array.m_buffer,   nullptr);

    operator delete (array.m_buffer);
}

TYPED_TEST(ArrayTest, copyConstructor) { this->test([this]() 
{
    {
        unsigned char bytes[sizeof(Array<TypeParam>)] = {};
        Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

        new (&array) Array<TypeParam>(this->m_array);

        ASSERT_NE(this->m_array.m_buffer, nullptr);
        ASSERT_NE(array.m_buffer,         nullptr);
        ASSERT_NE(array.m_buffer,         this->m_array.m_buffer);
        ASSERT_EQ(array.m_capacity,       this->m_array.m_capacity);
        ASSERT_EQ(array.m_length,         this->m_array.m_length);

        for (int i = 0; i < array.m_length; i++)
            ASSERT_EQ(array.m_buffer[i], this->m_array.m_buffer[i]);
        
        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
    {
        unsigned char bytes[sizeof(Array<TypeParam>)] = {};
        Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

        new (&array) Array<TypeParam>(this->m_constArray);

        ASSERT_NE(this->m_constArray.m_buffer, nullptr);
        ASSERT_NE(array.m_buffer,              nullptr);
        ASSERT_NE(array.m_buffer,              this->m_constArray.m_buffer);
        ASSERT_EQ(array.m_capacity,            this->m_constArray.m_capacity);
        ASSERT_EQ(array.m_length,              this->m_constArray.m_length);

        for (int i = 0; i < array.m_length; i++)
            ASSERT_EQ(array.m_buffer[i], this->m_constArray.m_buffer[i]);
        
        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
});}

TYPED_TEST(ArrayTest, moveConstructor) { this->test([this]()
{    
    unsigned char bytes[sizeof(Array<TypeParam>)] = {};
    Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

    new (&array) Array<TypeParam>(std::move(this->m_array));

    ASSERT_EQ(this->m_array.m_buffer, nullptr);
    ASSERT_NE(array.m_buffer,         nullptr);
    ASSERT_EQ(array.m_length,         this->m_vector.size());
    ASSERT_EQ(array.m_capacity,       this->m_vector.capacity());

    for (int i = 0; i < array.m_length; i++)
        ASSERT_EQ(array.m_buffer[i], this->m_vector[i]);
    
    for (int i = 0; i < array.m_length; i++)
        array.m_buffer[i].~TypeParam();
    ::operator delete(array.m_buffer);
});}

TYPED_TEST(ArrayTest, iteratorConstructor)
{
    {
        TypeParam c_array[100];

        for (int i = 0; i < 100;i++)
            c_array[i] = random<TypeParam>();
        
        unsigned char bytes[sizeof(Array<TypeParam>)] = {};
        Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

        new (&array) Array<TypeParam>(&c_array[0], &c_array[100]);

        for (int i = 0; i < 100; i++)
            EXPECT_EQ(array.m_buffer[i], c_array[i]);

        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
    {
        std::vector<TypeParam> vector;

        for (int i = 0; i < 100;i++)
            vector.push_back(random<TypeParam>());
        
        unsigned char bytes[sizeof(Array<TypeParam>)] = {};
        Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

        new (&array) Array<TypeParam>(vector.begin(), vector.end());

        for (int i = 0; i < 100; i++)
            EXPECT_EQ(array.m_buffer[i], vector[i]);

        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
    {
        std::list<TypeParam> list;

        for (int i = 0; i < 100;i++)
            list.push_back(random<TypeParam>());
        
        unsigned char bytes[sizeof(Array<TypeParam>)] = {};
        Array<TypeParam>& array = *reinterpret_cast<Array<TypeParam>*>(bytes);

        new (&array) Array<TypeParam>(list.begin(), list.end());
        
        int i = 0; 
        for (auto& el : list)
            EXPECT_EQ(array.m_buffer[i++], el);

        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
}

TYPED_TEST(ArrayTest, lengthConstructor)
{
    using Array = Array<TypeParam>;
    using Size = typename Array::Size;
    using Index = typename Array::Index;
    using Element = typename Array::Element;

    for (const Size& length : { 0, 1, 10 , 128 })
    {
        unsigned char bytes[sizeof(Array)] = {};
        Array& array = *reinterpret_cast<Array*>(bytes);

        new (&array) Array(length, Element());

        EXPECT_EQ(array.m_length, length);
        EXPECT_TRUE(array.m_capacity >= length);
        EXPECT_NE(array.m_buffer, nullptr);

        for (Index idx = 0; idx < length; idx++)
            ASSERT_EQ(array.m_buffer[idx], Element());

        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
}

TYPED_TEST(ArrayTest, findWhere) { this->test([this]()
{
    using Array = Array<TypeParam>;
    using Index = typename Array::Index;
    using Iterator = typename Array::Iterator;
    using const_Iterator = typename Array::const_Iterator;

    std::vector<Index> indices = { 0, this->m_array.m_length - 1, random<Index>(0, this->m_array.m_length - 1) };
    for (auto& index : indices)
    {
        if (this->m_array.m_length > 0)
        {
            Iterator it = this->m_array.findWhere([&](const typename Array::Element& e) {
                return e == this->m_vector[index];
            });
            ASSERT_NE(it, this->m_array.end());
            ASSERT_EQ(*it, this->m_vector[index]);
        }
        if (this->m_constArray.m_length > 0)
        {
            const_Iterator it = this->m_constArray.findWhere([&](const typename Array::Element& e) {
                return e == this->m_vector[index];
            });
            ASSERT_NE(it, this->m_constArray.end());
            ASSERT_EQ(*it, this->m_vector[index]);
        }
    }
});}

TYPED_TEST(ArrayTest, find) { this->test([this]()
{
    using Array = Array<TypeParam>;
    using Index = typename Array::Index;
    using Iterator = typename Array::Iterator;
    using const_Iterator = typename Array::const_Iterator;
    
    std::vector<Index> indices = { 0, this->m_array.m_length - 1, random<Index>(0, this->m_array.m_length - 1) };
    for (auto& index : indices)
    {
        if (this->m_array.m_length > 0)
        {
            Iterator it = this->m_array.find(this->m_vector[index]);
            ASSERT_NE(it, this->m_array.end());
            ASSERT_EQ(*it, this->m_vector[index]);
        }
        if (this->m_constArray.m_length > 0)
        {
            const_Iterator it = this->m_constArray.find(this->m_vector[index]);
            ASSERT_NE(it, this->m_constArray.end());
            ASSERT_EQ(*it, this->m_vector[index]);
        }
    }
});}

TYPED_TEST(ArrayTest, containWhere) { this->test([this]()
{
    using Array = Array<TypeParam>;
    using Index = typename Array::Index;
    
    std::vector<Index> indices = { 0, this->m_array.m_length - 1, random<Index>(0, this->m_array.m_length - 1) };
    for (auto& index : indices)
    {
        if (this->m_array.m_length > 0)
            ASSERT_TRUE(this->m_array.containWhere([&](const typename Array::Element& e) {return e == this->m_vector[index];}));
        if (this->m_constArray.m_length > 0)
            ASSERT_TRUE(this->m_constArray.containWhere([&](const typename Array::Element& e) {return e == this->m_vector[index];}));
    }
});}

TYPED_TEST(ArrayTest, contain) { this->test([this]()
{
    using Array = Array<TypeParam>;
    using Index = typename Array::Index;
    
    std::vector<Index> indices = { 0, this->m_array.m_length - 1, random<Index>(0, this->m_array.m_length - 1) };
    for (auto& index : indices)
    {
        if (this->m_array.m_length > 0)
            ASSERT_TRUE(this->m_array.contain(this->m_vector[index]));
        if (this->m_constArray.m_length > 0)
            ASSERT_TRUE(this->m_constArray.contain(this->m_vector[index]));
    }
});}

TYPED_TEST(ArrayTest, append) { this->test([this]()
{
    using Array = Array<TypeParam>;
    for (auto& i : { 1, 2, 3 })
    {
        typename Array::Size prevLength = this->m_array.m_length;
        TypeParam newItem = random<TypeParam>();
        this->m_array.append(newItem);
        ASSERT_EQ(this->m_array.m_length, prevLength + 1);
        ASSERT_TRUE(this->m_array.m_capacity >= this->m_array.m_length);
        ASSERT_EQ(this->m_array.m_buffer[this->m_array.m_length - 1], newItem);
    }
    for (auto& i : { 1, 2, 3 })
    {
        typename Array::Size prevLength = this->m_array.m_length;
        TypeParam newItem = random<TypeParam>();
        this->m_array.append(TypeParam(newItem));
        ASSERT_EQ(this->m_array.m_length, prevLength + 1);
        ASSERT_TRUE(this->m_array.m_capacity >= this->m_array.m_length);
        ASSERT_EQ(this->m_array.m_buffer[this->m_array.m_length - 1], newItem);
    }
});}

TYPED_TEST(ArrayTest, remove) { this->test([this]()
{
    using Array = Array<TypeParam>;
    using Vector = std::vector<TypeParam>;

    int i = -1;
    while (++i < 4 && this->m_vector.size() > 0)
    {
        utils::uint32 n = this->m_vector.size() == 1 ? 0 : random<int>(0, this->m_vector.size() - 1);
        typename Array::Iterator arrIt = this->m_array.begin() + n;
        typename Vector::iterator vecIt = this->m_vector.begin() + n;

        this->m_array.remove(arrIt);
        this->m_vector.erase(vecIt);

        ASSERT_EQ(this->m_array.m_length, this->m_vector.size());

        for (int i = 0; i < this->m_array.m_length; i++)
            ASSERT_EQ(this->m_array.m_buffer[i], this->m_vector[i]);
    }
});}

TYPED_TEST(ArrayTest, clear) { this->test([this]()
{
    this->m_array.clear();

    ASSERT_EQ(this->m_array.m_length,   0);
    ASSERT_EQ(this->m_array.m_capacity, 1);
    ASSERT_NE(this->m_array.m_buffer,   nullptr);
});}

TYPED_TEST(ArrayTest, copyAssignementOperator) { this->test([this]() 
{
    using Array   = Array<TypeParam>;
    using Size    = typename Array::Size;
    using Element = typename Array::Element;

    struct data { Size length; Size capacity; };
    for (data input : {(data){0, 1}, (data){1, 2}, (data){3, 4}, (data){128, 255}, (data){3152, 3152}})
    {
        {
            unsigned char bytes[sizeof(Array)] = {};
            Array& array = *reinterpret_cast<Array*>(bytes);

            array.m_length = input.length;
            array.m_capacity = input.capacity;
            array.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

            for (int i = 0; i < array.m_length; i++)
                new (array.m_buffer + i) Element(random<Element>());

            array = this->m_array;

            ASSERT_NE(this->m_array.m_buffer, nullptr);
            ASSERT_NE(array.m_buffer,         nullptr);
            ASSERT_NE(array.m_buffer,         this->m_array.m_buffer);
            ASSERT_EQ(array.m_capacity,       this->m_array.m_capacity);
            ASSERT_EQ(array.m_length,         this->m_array.m_length);

            for (int i = 0; i < array.m_length; i++)
                ASSERT_EQ(array.m_buffer[i], this->m_array.m_buffer[i]);
            
            for (int i = 0; i < array.m_length; i++)
                array.m_buffer[i].~TypeParam();
            ::operator delete(array.m_buffer);
        }
        {
            unsigned char bytes[sizeof(Array)] = {};
            Array& array = *reinterpret_cast<Array*>(bytes);

            array.m_length = input.length;
            array.m_capacity = input.capacity;
            array.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

            for (int i = 0; i < array.m_length; i++)
                new (array.m_buffer + i) Element(random<Element>());

            array = this->m_constArray;

            ASSERT_NE(this->m_constArray.m_buffer, nullptr);
            ASSERT_NE(array.m_buffer,         nullptr);
            ASSERT_NE(array.m_buffer,         this->m_constArray.m_buffer);
            ASSERT_EQ(array.m_capacity,       this->m_constArray.m_capacity);
            ASSERT_EQ(array.m_length,         this->m_constArray.m_length);

            for (int i = 0; i < array.m_length; i++)
                ASSERT_EQ(array.m_buffer[i], this->m_constArray.m_buffer[i]);
            
            for (int i = 0; i < array.m_length; i++)
                array.m_buffer[i].~TypeParam();
            ::operator delete(array.m_buffer);
        }
    }
});}

TYPED_TEST(ArrayTest, moveAssignementOperator) { this->test([this]()
{    
    using Array   = Array<TypeParam>;
    using Size    = typename Array::Size;
    using Element = typename Array::Element;

    struct data { Size length; Size capacity; };
    for (data input : {(data){0, 1}, (data){1, 2}, (data){3, 4}, (data){128, 255}, (data){3152, 3152}})
    {
        unsigned char bytes[sizeof(Array)] = {};
        Array& array = *reinterpret_cast<Array*>(bytes);

        array.m_length = input.length;
        array.m_capacity = input.capacity;
        array.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

        std::vector<Element> vector;
        vector.resize(input.length);
        vector.reserve(input.capacity);

        for (int i = 0; i < array.m_length; i++)
        {
            vector[i] = random<Element>();
            new (array.m_buffer + i) Element(vector[i]);
        }

        this->m_array = std::move(array);

        ASSERT_EQ(array,                    nullptr);
        ASSERT_NE(this->m_array.m_buffer,   nullptr);
        ASSERT_EQ(this->m_array.m_length,   vector.size());
        ASSERT_EQ(this->m_array.m_capacity, vector.capacity());

        for (int i = 0; i < array.m_length; i++)
            ASSERT_EQ(this->m_array.m_buffer[i], vector[i]);        
    }
});}

TYPED_TEST(ArrayTest, equalOperator) { this->test([this]()
{    
    using Array   = Array<TypeParam>;
    using Size    = typename Array::Size;
    using Element = typename Array::Element;

    struct data { Size length; Size capacity; };
    for (data input : {(data){0, 1}, (data){1, 2}, (data){3, 4}, (data){128, 255}, (data){3152, 3152}})
    {
        unsigned char bytes[sizeof(Array)] = {};
        Array& array = *reinterpret_cast<Array*>(bytes);

        array.m_length = input.length;
        array.m_capacity = input.capacity;
        array.m_buffer = (Element*) operator new (sizeof(Element) * input.capacity);

        for (int i = 0; i < array.m_length; i++)
            new (array.m_buffer + i) Element(i < this->m_array.m_length ? this->m_array.m_buffer[i] : random<TypeParam>());
        
        if (input.length == this->m_array.m_length)
        {
            ASSERT_TRUE(array == this->m_array);
            ASSERT_FALSE(array != this->m_array);
        }
        else
        {
            ASSERT_FALSE(array == this->m_array);
            ASSERT_TRUE(array != this->m_array);
        }

        for (int i = 0; i < array.m_length; i++)
            array.m_buffer[i].~TypeParam();
        ::operator delete(array.m_buffer);
    }
});}

}
/*
 * ---------------------------------------------------
 * Array.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 17:58:03
 * ---------------------------------------------------
 */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include "UtilsCPP/Error.hpp"
#include "UtilsCPP/Types.hpp"
#include "UtilsCPP/Func.hpp"
#include "UtilsCPP/Functions.hpp"

#include <initializer_list>
#include <utility>
#include <new>

namespace utils
{

template <typename T>
class Array
{
public:
    ERROR_DEFF(OutOfBoundError, "Out of bound access");

public:
    using Element  = T;
    using Size     = uint64;
    using Index    = Size;

    class Iterator;
    class const_Iterator;

public:
    Array() : m_buffer((Element*)operator new (sizeof(Element) * 1))
    {
    }

    Array(const Array& cp) : m_length(cp.m_length), m_capacity(cp.m_capacity), m_buffer((Element*)operator new (sizeof(Element) * cp.m_capacity))
    {
        for (Index i = 0; i < cp.m_length; i++)
            new (m_buffer + i) Element(cp[i]);
    }

    Array(Array&& mv) noexcept : m_length(mv.m_length), m_capacity(mv.m_capacity), m_buffer(mv.m_buffer)
    {
        mv.m_buffer = nullptr;
    }

    template<typename Iterator>
    Array(const Iterator& begin, const Iterator& end)
    {
        for (Iterator it = begin; it != end; ++it)
        {
            m_length += 1;
            if (m_length > m_capacity)
                m_capacity *= 2;
        }
        
        m_buffer = (Element*)operator new (sizeof(Element) * m_capacity);

        Iterator curr = begin;
        Index idx = 0;
        for (; curr != end; ++curr, idx++)
            new (m_buffer + idx) Element(*curr);
    }

    explicit Array(Size length, const Element& val = Element()) : m_length(length)
    {
        while (m_capacity < m_length)
            m_capacity *= 2;

        m_buffer = (Element*)operator new (sizeof(Element) * m_capacity);

        for (Index i = 0; i < length; i++)
            new (m_buffer + i) Element(val);
    }

    Array(const std::initializer_list<Element>& init_list) : m_length(init_list.size())
    {
        while (m_capacity < m_length)
            m_capacity *= 2;
        
        m_buffer = (Element*)operator new (sizeof(Element) * m_capacity);

        Index i = 0;
        for (const auto& elem : init_list)
            new (m_buffer + i++) Element(elem);
    }

    inline bool isEmpty()  const { return m_length == 0; }
    inline Size length()   const { return m_length; }
    inline Size capacity() const { return m_capacity; }

    inline       Iterator begin()       { return       Iterator(*this, 0); }
    inline const_Iterator begin() const { return const_Iterator(*this, 0); }
    inline       Iterator end()         { return       Iterator(*this, m_length); }
    inline const_Iterator end()   const { return const_Iterator(*this, m_length); }

    Iterator findWhere(const Func<bool(const Element&)>& condition)
    {
        Index index = 0;
        for (; index < m_length; index++)
        {
            if(condition(m_buffer[index]))
                break;
        }
        return Iterator(*this, index);
    }

    const_Iterator findWhere(const Func<bool(const Element&)>& condition) const
    {
        Index index = 0;
        for (; index < m_length; index++)
        {
            if(condition(m_buffer[index]))
                break;
        }
        return const_Iterator(*this, index);
    }

    template<typename S>
    Iterator find(const S& searched)
    {
        Index index = 0;
        for (; index < m_length; index++)
        {
            if(m_buffer[index] == searched)
                break;
        }
        return Iterator(*this, index);
    }

    template<typename S>
    const_Iterator find(const S& searched) const
    {
        Index index = 0;
        for (; index < m_length; index++)
        {
            if(m_buffer[index] == searched)
                break;
        }
        return const_Iterator(*this, index);
    }

    inline bool containWhere(const Func<bool(const Element&)>& condition) const
    {
        return findWhere((Func<bool(const Element&)>&&)condition) != end();
    }

    template<typename S>
    inline bool contain(const S& searched) const
    {
        return find(searched) != end();
    }

    Iterator append(const Element& element)
    {
        if (m_length == m_capacity)
            extendCapacity();
        new (m_buffer + m_length) Element(element);
        ++m_length;
        return Iterator(*this, m_length - 1);
    }

    Iterator append(Element&& element)
    {
        if (m_length == m_capacity)
            extendCapacity();
        new (m_buffer + m_length) Element(std::move(element));
        ++m_length;
        return Iterator(*this, m_length - 1);
    }

    void remove(const Iterator& it)
    {
        Iterator curr = it;
        Iterator id_end = end();
        if (curr == id_end)
            return;
        Iterator it_next = ++Iterator(curr);
        while (it_next != id_end)
            swap(*(curr++), *(it_next++));
        (*curr).~Element();
        --m_length;
        if (m_length <= m_capacity / 2)
            reduceCapacity();
    }

    Element pop(const Iterator& it)
    {
        Iterator curr = it;
        Iterator id_end = end();
        Iterator it_next = ++Iterator(curr);
        while (it_next != id_end)
            swap(*(curr++), *(it_next++));
        Element output = std::move(*curr);
        --m_length;
        if (m_length <= m_capacity / 2)
            reduceCapacity();
        return output;
    }

    void clear()
    {

        for (Size i = 0; i < m_length; ++i)
            m_buffer[i].~Element();
        operator delete (m_buffer);

        m_length = 0;
        m_capacity = 1;

        m_buffer = (Element*)operator new (sizeof(Element) * m_capacity);
    }

    inline       Element& last()        { return m_buffer[m_length - 1]; }
    inline const Element& last()  const { return m_buffer[m_length - 1]; }
    inline       Element& first()       { return m_buffer[0]; }
    inline const Element& first() const { return m_buffer[0]; }

    void sort()
    {
        Func<Index(Index, Index)> partition = [&](Index l, Index r) -> Index {
            Element& pivot = (*this)[r];
            Index pivotDst = l;
            for (Index i = l; i < r; i++)
            {
                if ((*this)[i] < pivot)
                    swap((*this)[pivotDst++], (*this)[i]);
            }
            swap((*this)[pivotDst], pivot);
            return pivotDst;
        };
        Func<void(Index, Index)> quickSort = [&](Index l, Index r) {
            if (l < r)
            {
                Index pivotIdx = partition(l, r);
                quickSort(l, pivotIdx == 0 ? 0 : pivotIdx - 1);
                quickSort(pivotIdx + 1, r);
            }
        };
        quickSort(0, length() - 1);
    }

    void setCapacity(Size newCapacity)
    {
        if (newCapacity == m_capacity)
            return;

        auto* newBuffer = (Element*)operator new (sizeof(Element) * newCapacity);

        for (Size i = 0; i < m_length; i++)
        {
            new (newBuffer + i) Element(std::move(m_buffer[i]));
            m_buffer[i].~Element();
        }

        operator delete (m_buffer);

        m_buffer = newBuffer;
        m_capacity = newCapacity;
    }

    virtual ~Array()
    {
        if (m_buffer == nullptr)
            return;
        for (Size i = 0; i < m_length; ++i)
            m_buffer[i].~Element();
        operator delete (m_buffer);
    }

private:
    inline void extendCapacity() { setCapacity(m_capacity * 2); }
    inline void reduceCapacity() { setCapacity(m_capacity / 2 > 0 ? m_capacity / 2 : 1); }

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
public:
#endif
    Element* m_buffer = nullptr;
    Size m_length = 0;
    Size m_capacity = 1;

public:
    Array& operator = (const Array& cp)
    {
        if (&cp != this)
        {
            if (m_buffer != nullptr)
            {
                for (Size i = 0; i < m_length; ++i)
                    m_buffer[i].~Element();
                operator delete (m_buffer);
            }

            m_length = cp.m_length;
            m_capacity = cp.m_capacity;
            m_buffer = (Element*)operator new (sizeof(Element) * cp.m_capacity);

            for (Index i = 0; i < cp.m_length; i++)
                new (m_buffer + i) Element(cp[i]);
        }
        return *this;
    }

    Array& operator = (Array&& mv) noexcept
    {
        if (&mv != this)
        {
            if (m_buffer != nullptr)
            {
                for (Size i = 0; i < m_length; ++i)
                    m_buffer[i].~Element();
                operator delete (m_buffer);
            }

            m_length = mv.m_length;
            m_capacity = mv.m_capacity;
            m_buffer = mv.m_buffer;

            mv.m_capacity = 0;
            mv.m_length = 0;
            mv.m_buffer = nullptr;
        }
        return *this;
    }

    Element& operator [] (Index idx)
    {
        if (idx >= m_length)
            throw OutOfBoundError();
        return m_buffer[idx];
    }

    const Element& operator [] (Index idx) const
    {
        if (idx >= m_length)
            throw OutOfBoundError();
        return m_buffer[idx];
    }

    bool operator == (const Array& rhs) const
    {
        if (m_length != rhs.m_length)
            return false;
    
        for (Index i = 0; i < m_length; i++)
        {
            if (m_buffer[i] != rhs.m_buffer[i])
                return false;
        }

        return true;
    }

    inline bool operator != (const Array& rhs) const { return !operator==(rhs); }

    bool operator < (const Array& rhs) const
    {
        Index idx = 0;
        for (; idx < m_length && idx < rhs.m_length; idx++)
        {
            if (m_buffer[idx] != rhs.m_buffer[idx])
                return m_buffer[idx] < rhs.m_buffer[idx];
        }
        if (idx < m_length)
            return false;
        if (idx < rhs.m_length)
            return true;
        return false;
    }

    inline operator       Element* ()       { return m_buffer; }
    inline operator const Element* () const { return m_buffer; }

public:
    class Iterator
    {
    private:
        friend class Array<T>;

    public:
        using Element = T;

    public:
        Iterator()                   = default;
        Iterator(const Iterator& cp) = default;
        Iterator(Iterator&& mv)      = default;

        ~Iterator() = default;

    private:
        Iterator(Array& arrayRef, Index idx) : m_arrayRef(&arrayRef), m_idx(idx) {}

        Array* m_arrayRef = nullptr;
        Index m_idx = 0;

    public:
        Iterator& operator = (const Iterator& cp) = default;
        Iterator& operator = (Iterator&& mv)      = default;

        inline Element& operator  * () const { return m_arrayRef->m_buffer[m_idx];  };
        inline Element* operator -> () const { return m_arrayRef->m_buffer + m_idx; };

        inline Iterator& operator ++ ()      { ++m_idx; return *this; }
        inline Iterator  operator ++ (int)   { Iterator temp(*this); ++m_idx; return temp; }
        inline Iterator  operator  + (int n) { return Iterator(*m_arrayRef, m_idx + n); }

        inline Iterator& operator -- ()      { --m_idx; return *this; }
        inline Iterator  operator -- (int)   { Iterator temp(*this); --m_idx; return temp; }
        inline Iterator  operator  - (int n) { return Iterator(*m_arrayRef, m_idx - n); }

        inline bool operator == (const Iterator& rhs) const { return m_arrayRef == rhs.m_arrayRef && m_idx == rhs.m_idx; }
        inline bool operator != (const Iterator& rhs) const { return !(*this == rhs); }

        inline explicit operator Element* () const { return m_arrayRef->m_buffer + m_idx; }
    };

    class const_Iterator
    {
    private:
        friend class Array<T>;

    public:
        using Element = const T;

    public:
        const_Iterator()                      = default;
        const_Iterator(const const_Iterator&) = default;
        const_Iterator(const_Iterator&&)      = default;

        ~const_Iterator() = default;

    private:
        const_Iterator(const Array& arrayRef, Index idx) : m_arrayRef(&arrayRef), m_idx(idx) {}

        const Array* m_arrayRef = nullptr;
        Index m_idx = 0;

    public:
        const_Iterator& operator = (const const_Iterator&) = default;
        const_Iterator& operator = (const_Iterator&&)      = default;

        inline const Element& operator  * () const { return m_arrayRef->m_buffer[m_idx];  };
        inline const Element* operator -> () const { return m_arrayRef->m_buffer + m_idx; };

        inline const_Iterator& operator ++ ()      { ++m_idx; return *this; }
        inline const_Iterator  operator ++ (int)   { const_Iterator temp(*this); ++m_idx; return temp; }
        inline const_Iterator  operator  + (int n) { return Iterator(*m_arrayRef, m_idx + n); }

        inline const_Iterator& operator -- ()      { --m_idx; return *this; }
        inline const_Iterator  operator -- (int)   { const_Iterator temp(*this); --m_idx; return temp; }
        inline const_Iterator  operator  - (int n) { return Iterator(*m_arrayRef, m_idx - n); }

        inline bool operator == (const const_Iterator& rhs) const { return m_arrayRef == rhs.m_arrayRef && m_idx == rhs.m_idx; }
        inline bool operator != (const const_Iterator& rhs) const { return !(*this == rhs); }

        inline explicit operator const Element* () const { return m_arrayRef->m_buffer + m_idx; }
    };
};

}

#endif // ARRAY_HPP
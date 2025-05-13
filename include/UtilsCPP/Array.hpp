/*
 * ---------------------------------------------------
 * Array.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 17:58:03
 * ---------------------------------------------------
 */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "UtilsCPP/Macros.hpp"
#include "UtilsCPP/vector.hpp"
#include "UtilsCPP/Func.hpp"
#include "UtilsCPP/Functions.hpp"

namespace utl
{

template<typename T>
class Array : public vector<T>
{
private:
    using vector = utl::vector<T>;

public:
    using Element = vector::value_type;
    using Size = vector::size_type;
    using Index = Size;

    using Iterator = vector::iterator;
    using const_Iterator = vector::const_iterator;

public:
    Array() = default;

    Array(const Array& other)
        requires std::copy_constructible<Element>
        : vector(other)
    {
    }

    Array(Array&& other) noexcept : vector(std::move(other))
    {
    }

    using vector::vector;

    DEPRECATED("use empty()")
    inline bool isEmpty() const { return vector::empty(); }

    DEPRECATED("use size()")
    inline Size length() const { return vector::size(); }

    Iterator findWhere(const Func<bool(const Element&)>& condition)
    {
        Index index = 0;
        for (; index < vector::m_size; index++)
        {
            if (condition(vector::m_buffer[index]))
                break;
        }
        return Iterator(*this, index);
    }

    const_Iterator findWhere(const Func<bool(const Element&)>& condition) const
    {
        Index index = 0;
        for (; index < vector::m_size; index++)
        {
            if (condition(vector::m_buffer[index]))
                break;
        }
        return const_Iterator(*this, index);
    }

    template<typename S>
    Iterator find(const S& searched)
    {
        Index index = 0;
        for (; index < vector::m_size; index++)
        {
            if (vector::m_buffer[index] == searched)
                break;
        }
        return Iterator(*this, index);
    }

    template<typename S>
    const_Iterator find(const S& searched) const
    {
        Index index = 0;
        for (; index < vector::m_size; index++)
        {
            if (vector::m_buffer[index] == searched)
                break;
        }
        return const_iterator(*this, index);
    }

    inline bool containWhere(const Func<bool(const Element&)>& condition) const
    {
        return findWhere((Func<bool(const Element&)>&&)condition) != vector::end();
    }

    template<typename S>
    inline bool contain(const S& searched) const
    {
        return find(searched) != vector::end();
    }

    Iterator append(const Element& element)
        requires std::copy_constructible<Element>
    {
        vector::push_back(element);
        return --vector::end();
    }

    Iterator append(Element&& element)
        requires std::move_constructible<Element>
    {
        vector::push_back(element);
        return --vector::end();
    }

    inline void remove(const Iterator& it) { (void)vector::erase(it); }

    Element pop(const Iterator& it)
    {
        Iterator curr = it;
        Iterator id_end = vector::end();
        Iterator it_next = ++Iterator(curr);
        while (it_next != id_end)
            swap(*(curr++), *(it_next++));
        Element output = std::move(*curr);
        --vector::m_size;
        if (vector::m_size <= vector::m_capacity / 2)
            vector::reduceCapacity();
        return output;
    }

    DEPRECATED("use back()")
    inline Element& last() { return vector::back(); }

    DEPRECATED("use back()")
    inline const Element& last() const { return vector::back(); }

    DEPRECATED("use front()")
    inline Element& first() { return vector::front(); }

    DEPRECATED("use front()")
    inline const Element& first() const { return vector::front(); }

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
                const Index pivotIdx = partition(l, r);
                quickSort(l, pivotIdx == 0 ? 0 : pivotIdx - 1);
                quickSort(pivotIdx + 1, r);
            }
        };
        quickSort(0, vector::m_size - 1);
    }

    using vector::setCapacity;

    ~Array() = default;

public:
    Array& operator=(const Array& other)
    {
        (void)vector::operator=(other);
        return *this;
    }

    Array& operator=(Array&& other) noexcept
    {
        (void)vector::operator=(other);
        return *this;
    }

    inline operator Element*() { return vector::m_buffer; }
    inline operator const Element*() const { return vector::m_buffer; }
};

} // namespace utl

#ifndef UTILS_NAMESPACE
#define UTILS_NAMESPACE
namespace utils = utl; // NOLINT
#endif

#endif // ARRAY_HPP

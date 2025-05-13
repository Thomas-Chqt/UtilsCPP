/*
 * ---------------------------------------------------
 * vector.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/06 08:03:55
 * ---------------------------------------------------
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>
#include <new>

namespace utl
{

template<typename T>
class vector
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

protected:
    using Index = size_type;

private:
    template<bool IsConst>
    class iterator_base
    {
    public:
        using value_type = vector::value_type;
        using difference_type = vector::difference_type;
        using reference = std::conditional_t<IsConst, vector::const_reference, vector::reference>;
        using pointer = std::conditional_t<IsConst, vector::const_pointer, vector::pointer>;
        using iterator_category = std::random_access_iterator_tag;

    private:
        friend class vector<T>;
        using container_type = std::conditional_t<IsConst, const vector, vector>;

    public:
        iterator_base() = default;
        iterator_base(const iterator_base& cp) = default;
        iterator_base(iterator_base&& mv) = default;

        ~iterator_base() = default;

    private:
        iterator_base(container_type& vectorRef, Index idx) : m_vectorRef(&vectorRef), m_idx(idx) {}

        container_type* m_vectorRef = nullptr;
        Index m_idx = 0;

    public:
        iterator_base& operator=(const iterator_base& cp) = default;
        iterator_base& operator=(iterator_base&& mv) = default;

        inline reference operator*() const { return m_vectorRef->m_buffer[m_idx]; };
        inline pointer operator->() const { return m_vectorRef->m_buffer + m_idx; };

        inline iterator_base& operator++() { return ++m_idx, *this; }
        inline iterator_base operator++(int)
        {
            iterator_base temp(*this);
            ++m_idx;
            return temp;
        }

        inline iterator_base& operator--() { return --m_idx, *this; }
        inline iterator_base operator--(int)
        {
            iterator_base temp(*this);
            --m_idx;
            return temp;
        }
        
        inline iterator_base& operator+=(difference_type n) { return m_idx += n, *this; }
        inline iterator_base operator+(difference_type n) const { return iterator_base(*m_vectorRef, m_idx + n); }
        friend inline iterator_base operator+(difference_type n, const iterator_base& it) { return iterator_base(*it.m_vectorRef, it.m_idx + n); }

        inline iterator_base& operator-=(difference_type n) { return m_idx -= n, *this; }
        inline iterator_base operator-(difference_type n) const { return iterator_base(*m_vectorRef, m_idx - n); }
        friend inline iterator_base operator-(difference_type n, const iterator_base& it) { return iterator_base(*it.m_vectorRef, it.m_idx - n); }

        inline difference_type operator-(const iterator_base& other) const { return static_cast<difference_type>(m_idx - other.m_idx); }

        inline reference operator[](difference_type n) const { return m_vectorRef->m_buffer[m_idx + n]; }

        inline bool operator==(const iterator_base& rhs) const { return m_vectorRef == rhs.m_vectorRef && m_idx == rhs.m_idx; }
        inline bool operator!=(const iterator_base& rhs) const { return !(*this == rhs); }
        inline bool operator<(const iterator_base& rhs) const { return m_vectorRef == rhs.m_vectorRef && m_idx < rhs.m_idx; }
        inline bool operator<=(const iterator_base& rhs) const { return m_vectorRef == rhs.m_vectorRef && m_idx <= rhs.m_idx; }
        inline bool operator>(const iterator_base& rhs) const { return m_vectorRef == rhs.m_vectorRef && m_idx > rhs.m_idx; }
        inline bool operator>=(const iterator_base& rhs) const { return m_vectorRef == rhs.m_vectorRef && m_idx >= rhs.m_idx; }

        inline explicit operator pointer() const { return m_vectorRef->m_buffer + m_idx; }
    };

public:
    using iterator = iterator_base<false>;
    using const_iterator = iterator_base<true>;

public:
    vector() = default;

    vector(const vector& other)
        requires std::copy_constructible<value_type>
    {
        if (other.m_size > 0)
        {
            m_size = other.m_size;
            m_capacity = other.m_size;
            m_buffer = (value_type*)operator new(sizeof(value_type) * m_capacity);
            for (Index i = 0; i < m_size; i++)
                new (m_buffer + i) value_type(other[i]);
        }
    }

    vector(vector&& other) noexcept : m_buffer(other.m_buffer), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        assert(other.m_size <= other.m_capacity);
        other.m_buffer = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    explicit vector(size_type count)
        requires std::default_initializable<value_type>
        : m_size(count),
          m_capacity(count),
          m_buffer((value_type*)operator new(sizeof(value_type) * count))
    {
        for (Index i = 0; i < count; i++)
            new (m_buffer + i) value_type();
    }

    explicit vector(size_type count, const value_type& val)
        requires std::copy_constructible<value_type>
        : m_size(count),
          m_capacity(count),
          m_buffer((value_type*)operator new(sizeof(value_type) * count))
    {
        for (Index i = 0; i < count; i++)
            new (m_buffer + i) value_type(val);
    }

    template<std::input_iterator InputIt>
    vector(const InputIt& begin, const InputIt& end)
        requires std::copy_constructible<value_type>
        : m_size(std::distance(begin, end))
    {
        m_capacity = m_size;
        m_buffer = (value_type*)operator new(sizeof(value_type) * m_capacity);
        std::input_iterator auto curr = begin;
        Index idx = 0;
        for (; curr != end; ++curr, idx++)
            new (m_buffer + idx) value_type(*curr);
    }

    vector(const std::initializer_list<value_type>& init)
        requires std::copy_constructible<value_type>
        : m_size(init.size()),
          m_capacity(init.size()),
          m_buffer((value_type*)operator new(sizeof(value_type) * init.size()))
    {
        for (Index i = 0; const value_type& elem : init)
            new (m_buffer + i++) value_type(elem);
    }

    inline bool empty() const { return m_size == 0; }
    inline size_type size() const { return m_size; }
    inline size_type capacity() const { return m_capacity; }

    inline iterator begin() { return iterator(*this, 0); }
    inline const_iterator begin() const { return const_iterator(*this, 0); }
    inline iterator end() { return iterator(*this, m_size); }
    inline const_iterator end() const { return const_iterator(*this, m_size); }

    void push_back(const value_type& value)
        requires std::copy_constructible<value_type>
    {
        if (m_size == m_capacity)
            extendCapacity();
        new (m_buffer + m_size) value_type(value);
        ++m_size;
    }

    void push_back(value_type&& value)
        requires std::move_constructible<value_type>
    {
        if (m_size == m_capacity)
            extendCapacity();
        new (m_buffer + m_size) value_type(std::move(value));
        ++m_size;
    }

    iterator erase(const iterator& it)
    {
        iterator curr = it;
        for (; std::next(curr) != end(); ++curr)
            std::iter_swap(curr, std::next(curr));
        (*curr).~value_type();
        --m_size;
        return iterator(it);
    }

    inline void pop_back() { (void)erase(--end()); }

    void clear()
    {
        for (size_type i = 0; i < m_size; ++i)
            m_buffer[i].~value_type();
        m_size = 0;
    }

    inline reference back() { return m_buffer[m_size - 1]; }
    inline const_reference back() const { return m_buffer[m_size - 1]; }

    inline reference front() { return m_buffer[0]; }
    inline const_reference front() const { return m_buffer[0]; }

    void reserve(size_type new_cap)
    {
        if (new_cap > m_capacity)
            setCapacity(new_cap);
    }

    virtual ~vector()
    {
        if (m_buffer == nullptr)
            return;
        for (size_type i = 0; i < m_size; ++i)
            m_buffer[i].~value_type();
        operator delete(m_buffer);
    }

protected:
    void setCapacity(size_type newCapacity)
    {
        if (newCapacity == m_capacity)
            return;

        auto* newBuffer = (value_type*)operator new(sizeof(value_type) * newCapacity);

        for (size_type i = 0; i < m_size; i++)
        {
            new (newBuffer + i) value_type(std::move(m_buffer[i]));
            m_buffer[i].~value_type();
        }

        operator delete(m_buffer);

        m_buffer = newBuffer;
        m_capacity = newCapacity;
    }

    inline void extendCapacity() { setCapacity(m_capacity == 0 ? 1 : m_capacity * 2); }

    value_type* m_buffer = nullptr;
    size_type m_size = 0;
    size_type m_capacity = 0;

public:
    vector& operator=(const vector& other)
        requires std::copy_constructible<value_type>
    {
        if (&other != this)
        {
            if (m_buffer != nullptr)
            {
                for (size_type i = 0; i < m_size; ++i)
                    m_buffer[i].~value_type();
                operator delete(m_buffer);
            }

            m_size = other.m_size;
            if (m_capacity != other.m_capacity)
            {
                m_capacity = other.m_capacity;
                m_buffer = (value_type*)operator new(sizeof(value_type) * m_capacity);
            }

            for (Index i = 0; i < m_size; i++)
                new (m_buffer + i) value_type(other[i]);
        }
        return *this;
    }

    vector& operator=(vector&& other) noexcept
    {
        if (&other != this)
        {
            if (m_buffer != nullptr)
            {
                for (size_type i = 0; i < m_size; ++i)
                    m_buffer[i].~value_type();
                operator delete(m_buffer);
            }

            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_buffer = other.m_buffer;

            other.m_capacity = 0;
            other.m_size = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }

    reference operator[](size_type pos)
    {
        assert(pos < m_size);
        return m_buffer[pos];
    }

    const_reference operator[](size_type pos) const
    {
        assert(pos < m_size);
        return m_buffer[pos];
    }

    bool operator==(const vector& rhs) const
    {
        if (m_size != rhs.m_size)
            return false;

        for (Index i = 0; i < m_size; i++)
        {
            if (m_buffer[i] != rhs.m_buffer[i])
                return false;
        }

        return true;
    }

    inline bool operator!=(const vector& rhs) const { return !operator==(rhs); }

    bool operator<(const vector& rhs) const
    {
        Index idx = 0;
        for (; idx < m_size && idx < rhs.m_size; idx++)
        {
            if (m_buffer[idx] != rhs.m_buffer[idx])
                return m_buffer[idx] < rhs.m_buffer[idx];
        }
        if (idx < m_size)
            return false;
        if (idx < rhs.m_size)
            return true;
        return false;
    }
};

} // namespace utl

#endif // VECTOR_HPP

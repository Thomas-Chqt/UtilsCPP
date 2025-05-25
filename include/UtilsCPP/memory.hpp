/*
 * ---------------------------------------------------
 * memory.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/05/24 08:52:55
 * ---------------------------------------------------
 */

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <type_traits>

namespace utl
{

template<typename T>
class unique_ptr
{
public:
    using element_type = std::remove_extent_t<T>;
    using pointer = element_type*;

public:
    constexpr unique_ptr() noexcept = default;

    explicit unique_ptr(pointer p) noexcept : m_ptr(p)
    {
    }

    unique_ptr(const unique_ptr&) = delete;

    // unique_ptr(unique_ptr&& u) noexcept : unique_ptr(u.release())
    // {
    // }

    template<typename U>
    requires std::is_convertible_v<U*, T*>
    unique_ptr(unique_ptr<U>&& u) noexcept : unique_ptr(u.release())
    {
    }

    pointer release() noexcept
    {
        pointer tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    void reset(pointer ptr = nullptr) noexcept
    {
        if constexpr (std::is_array_v<T>)
            delete[] m_ptr;
        else
            delete m_ptr;
        m_ptr = ptr;
    }

    inline pointer get() const noexcept { return m_ptr; }

    virtual ~unique_ptr() noexcept
    {
        reset();
    }

private:
    pointer m_ptr = nullptr;

public:
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr&& rhs) noexcept
    {
        if (rhs != *this)
            reset(rhs.release());
        return *this;
    }

    inline std::add_lvalue_reference_t<element_type> operator*() const
        requires(!std::is_array_v<T>)
    {
        return *m_ptr;
    }

    inline pointer operator->() const
        requires(!std::is_array_v<T>)
    {
        return m_ptr;
    }

    inline element_type& operator[](std::size_t i) const
        requires(std::is_array_v<T>)
    {
        return m_ptr[i];
    }

    explicit inline operator bool() const noexcept { return get() != nullptr; }
};

template<typename T, typename... ARGS>
unique_ptr<T> make_unique(ARGS&&... args)
    requires(!std::is_array_v<T>)
{
    return unique_ptr<T>(new T(std::forward<ARGS>(args)...));
}

template<typename T1, typename T2>
inline bool operator==(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() == rhs.get(); }

template<typename T1, typename T2>
inline bool operator!=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() != rhs.get(); }

template<typename T1, typename T2>
inline bool operator<(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() < rhs.get(); }

template<typename T1, typename T2>
inline bool operator<=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() <= rhs.get(); }

template<typename T1, typename T2>
inline bool operator>(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() > rhs.get(); }

template<typename T1, typename T2>
inline bool operator>=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) { return lhs.get() >= rhs.get(); }

} // namespace utl

#endif // MEMORY_HPP

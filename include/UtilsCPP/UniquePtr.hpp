/*
 * ---------------------------------------------------
 * UniquePtr.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 16:58:38
 * ---------------------------------------------------
 */

#ifndef UNIQUEPTR_HPP
# define UNIQUEPTR_HPP

#include <utility>

namespace utils
{

template<typename T>
class UniquePtr
{
    template<typename Y> friend class UniquePtr;

public:
    using Type = T;

public:
    UniquePtr()                 = default;
    UniquePtr(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& mv) : m_pointer(mv.m_pointer)
    {
        mv.m_pointer = nullptr;
    }

    template<typename Y, typename... ARGS>
    friend inline UniquePtr<Y> makeUnique(ARGS&&... args);

    template<typename Y>
    UniquePtr<Y> staticCast()
    {
        UniquePtr<Y> output(static_cast<Y*>(m_pointer));
        m_pointer = nullptr;
        return output;
    }

    void clear()
    {
        delete m_pointer;
        m_pointer = nullptr;
    }
    
    ~UniquePtr()
    {
        clear();
    }

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
public:
#else
private:
#endif
    UniquePtr(Type* ptr) : m_pointer(ptr) 
    {
    }

    Type* m_pointer = nullptr;

public:
    UniquePtr& operator = (const UniquePtr&) = delete;

    UniquePtr& operator = (UniquePtr&& rhs)
    {
        if (rhs != *this)
        {
            clear();
            m_pointer = rhs.m_pointer;
            rhs.m_pointer = nullptr;
        }
        return *this;
    }

    inline Type& operator  * () const { return *m_pointer; } // TODO add throw
    inline Type* operator -> () const { return  m_pointer; }

    inline operator T* () const { return m_pointer; }

    template<typename Y> inline bool operator == (const UniquePtr<Y>& rhs) const { return (void*)m_pointer == (void*)rhs.m_pointer; }
    template<typename Y> inline bool operator != (const UniquePtr<Y>& rhs) const { return (void*)m_pointer != (void*)rhs.m_pointer; }

    inline operator bool () const { return m_pointer != nullptr; }
};

template<typename T, typename... ARGS>
inline UniquePtr<T> makeUnique(ARGS&&... args) { return UniquePtr<T>(new T(std::forward<ARGS>(args)...)); }

}

#endif // UNIQUEPTR_HPP
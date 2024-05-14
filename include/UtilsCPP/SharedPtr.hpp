/*
 * ---------------------------------------------------
 * SharedPtr.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 21:58:25
 * ---------------------------------------------------
 */

#ifndef SHAREDPTR_HPP
# define SHAREDPTR_HPP

#include <utility>

#include "UtilsCPP/Types.hpp"

namespace utils
{

template<typename T>
class SharedPtr
{
public:
    using Type = T;

public:
    SharedPtr() : m_pointer(nullptr), m_refCount(nullptr)
    {
    }

    SharedPtr(const SharedPtr& cp) : m_pointer(cp.m_pointer), m_refCount(cp.m_refCount)
    {
        if (m_refCount != nullptr)
            *m_refCount += 1;
    }

    SharedPtr(SharedPtr&& mv) : m_pointer(mv.m_pointer), m_refCount(mv.m_refCount)
    {
        mv.m_pointer = nullptr;
        mv.m_refCount = nullptr;
    }

    template<typename Y, typename... ARGS>
    friend inline SharedPtr<Y> makeShared(ARGS&&... args);

    inline uint32 refCount() const { return m_refCount == nullptr ? 0 : *m_refCount; }

    void clear()
    {
        if (m_refCount == nullptr)
            return;
        *m_refCount -= 1;
        if (*m_refCount == 0)
        {
            delete m_pointer;
            delete m_refCount;
            m_pointer = nullptr;
            m_refCount = nullptr;
        }
    }

    ~SharedPtr()
    {
        clear();
    }

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
public:
#else
private:
#endif
    SharedPtr(Type* pointer) : m_pointer(pointer), m_refCount(new uint32(1))
    {
    }

    Type* m_pointer;
    uint32* m_refCount;

public:
    SharedPtr& operator = (const SharedPtr& rhs)
    {
        if (rhs != *this)
        {
            clear();
            m_pointer = rhs.m_pointer;
            m_refCount = rhs.m_refCount;
            *m_refCount += 1;
        }
        return *this;
    }

    SharedPtr& operator = (SharedPtr&& rhs)
    {
        if (rhs != *this)
        {
            clear();
            m_pointer = rhs.m_pointer;
            m_refCount = rhs.m_refCount;
            rhs.clear();
        }
        return *this;
    }

    inline Type& operator  * () const { return *m_pointer; } // TODO add throw
    inline Type* operator -> () const { return  m_pointer; }

    inline operator T* () const { return m_pointer; }

    template<typename Y> inline bool operator == (const SharedPtr<Y>& rhs) const { return (void*)m_pointer == (void*)rhs.m_pointer; }
    template<typename Y> inline bool operator != (const SharedPtr<Y>& rhs) const { return (void*)m_pointer != (void*)rhs.m_pointer; }

    inline operator bool () const { return m_pointer != nullptr; }
};

template<typename T, typename... ARGS>
inline SharedPtr<T> makeShared(ARGS&&... args) { return SharedPtr<T>(new T(std::forward<ARGS>(args)...)); }

}

#endif // SHAREDPTR_HPP
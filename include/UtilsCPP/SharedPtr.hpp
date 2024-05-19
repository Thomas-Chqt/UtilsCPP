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

#include "UtilsCPP/Types.hpp"

namespace utils
{

template<typename T>
class SharedPtr
{
private:
    template<typename Y> friend class SharedPtr;

public:
    using Type = T;

public:
    SharedPtr() = default;

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

    explicit SharedPtr(Type* pointer) : m_pointer(pointer), m_refCount(new uint32(1))
    {
    }

    inline uint32 refCount() const { return m_refCount == nullptr ? 0 : *m_refCount; }

    template<typename Y>
    SharedPtr<Y> staticCast() const
    {
        SharedPtr<Y> output;

        output.m_pointer = static_cast<Y*>(m_pointer);
        output.m_refCount = m_refCount;

        if (output.m_refCount != nullptr)
            *output.m_refCount += 1;

        return output;
    }

    template<typename Y>
    SharedPtr<Y> dynamicCast() const
    {
        SharedPtr<Y> output;

        output.m_pointer = dynamic_cast<Y*>(m_pointer);
        if (output.m_pointer == nullptr)
            return SharedPtr<Y>();

        output.m_refCount = m_refCount;

        if (output.m_refCount != nullptr)
            *output.m_refCount += 1;

        return output;
    }

    void clear()
    {
        if (m_refCount == nullptr)
            return;
        *m_refCount -= 1;
        if (*m_refCount == 0)
        {
            delete m_pointer;
            delete m_refCount;
        }
        m_pointer = nullptr;
        m_refCount = nullptr;
    }

    ~SharedPtr()
    {
        clear();
    }

private:
    Type* m_pointer = nullptr;
    uint32* m_refCount = nullptr;

public:
    SharedPtr& operator = (const SharedPtr& rhs)
    {
        if (rhs != *this)
        {
            clear();
            m_pointer = rhs.m_pointer;
            m_refCount = rhs.m_refCount;
            if (m_refCount != nullptr)
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
            rhs.m_pointer = nullptr;
            rhs.m_refCount = nullptr;
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

}

#endif // SHAREDPTR_HPP
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

#include "UtilsCPP/Error.hpp"

namespace utils
{

template<typename T>
class UniquePtr
{
public:
    struct NullPointerError : public Error { inline const char* description() const override { return "Dereferencing a null pointer"; } };

private:
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

    explicit UniquePtr(Type* ptr) : m_pointer(ptr) 
    {
    }

    template<typename Y>
    UniquePtr<Y> staticCast()
    {
        UniquePtr<Y> output;

        output.m_pointer = static_cast<Y*>(m_pointer);
        m_pointer = nullptr;

        return output;
    }

    Type* getOwnership()
    {
        Type* tmp = m_pointer;
        m_pointer = nullptr;
        return tmp;
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

    Type& operator  * () const
    {
        if (m_pointer == nullptr)
            throw NullPointerError();
        return *m_pointer;
    }

    inline Type* operator -> () const { return  m_pointer; }

    inline operator T* () const { return m_pointer; }

    template<typename Y> inline bool operator == (const UniquePtr<Y>& rhs) const { return (void*)m_pointer == (void*)rhs.m_pointer; }
    template<typename Y> inline bool operator != (const UniquePtr<Y>& rhs) const { return (void*)m_pointer != (void*)rhs.m_pointer; }

    inline operator bool () const { return m_pointer != nullptr; }
};

}

#endif // UNIQUEPTR_HPP
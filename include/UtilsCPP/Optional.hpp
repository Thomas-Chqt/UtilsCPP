/*
 * ---------------------------------------------------
 * Optional.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/07/18 12:56:53
 * ---------------------------------------------------
 */

#ifndef OPTIONAL_HPP
# define OPTIONAL_HPP

namespace utils
{

template<typename T>
class Optional
{
public:
    Optional()                = default;
    Optional(const Optional&) = default;
    Optional(Optional&&)      = default;
    
    Optional(const T& data) : m_null(false), m_data(data)
    {
    }

    ~Optional() = default;

private:
    bool m_null = true;
    T m_data;

public:
    Optional& operator = (const Optional&) = default;
    Optional& operator = (Optional&&)      = default;
    
    Optional& operator = (const T& data)
    {
        m_null = false;
        m_data = data;
        return *this;
    }
    
    inline       T& operator  * ()       { return  m_data; }
    inline const T& operator  * () const { return  m_data; }
    inline       T* operator -> ()       { return &m_data; }
    inline const T* operator -> () const { return &m_data; }

    inline operator bool () const { return m_null == false; }
};

}

#endif // OPTIONAL_HPP
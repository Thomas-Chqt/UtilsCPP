/*
 * ---------------------------------------------------
 * String.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 16:50:38
 * ---------------------------------------------------
 */

#ifndef STRING_HPP
# define STRING_HPP

#include "UtilsCPP/Types.hpp"
#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/Macros.hpp"
#include <istream>

#define SAFECPY(dst) safecpy(dst, sizeof(dst))

namespace utils
{

class UTILSCPP_API String
{
public:
    using Size  = uint64;
    using Index = Size;

    using Iterator       = Array<char>::Iterator;
    using const_Iterator = Array<char>::const_Iterator;

public:
    String();
    String(const String&)     = default;
    String(String&&) noexcept = default;

    String(const char* literal);
    explicit String(Size length, char c = '\0');
    
    static String contentOf(std::istream&);
    static String contentOfFile(const String& path);
    static String fromUInt(uint32);

    inline Size length()   const { return m_characters.length() - 1; }
    inline Size capacity() const { return m_characters.capacity(); } // capacity include the \0 character 
    inline bool isEmpty()  const { return (m_characters.length() - 1) == 0; }

    inline       Iterator begin()       { return   m_characters.begin(); }
    inline const_Iterator begin() const { return   m_characters.begin(); }
    inline       Iterator end()         { return --m_characters.end();   }
    inline const_Iterator end()   const { return --m_characters.end();   }

    void append(char c);

    Index lastIndexOf(char c) const;
    String substr(Index start, Size len) const;

    void safecpy(char* dst, uint64 buffSize) const;

    ~String() = default;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
public:
#else
private:
#endif
    Array<char> m_characters;

public:
    String& operator = (const String&)     = default;
    String& operator = (String&&) noexcept = default;

    inline bool operator == (const String& rhs) const { return m_characters == rhs.m_characters; }
    inline bool operator != (const String& rhs) const { return m_characters != rhs.m_characters; };

    inline bool operator < (const String& rhs) const { return m_characters < rhs.m_characters; }

    inline       char& operator [] (Index idx)       { return m_characters[idx]; };
    inline const char& operator [] (Index idx) const { return m_characters[idx]; };

    inline operator       char* ()       { return (      char*)m_characters; }
    inline operator const char* () const { return (const char*)m_characters; }

    friend UTILSCPP_API String operator + (const String& s1, const String& s2);
};

}

#endif // STRING_HPP
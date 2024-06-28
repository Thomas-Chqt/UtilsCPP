/*
 * ---------------------------------------------------
 * String.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 16:50:49
 * ---------------------------------------------------
 */

#include "UtilsCPP/String.hpp"
#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/Types.hpp"

#include <cstring>
#include <istream>
#include <fstream>
#include <utility>

namespace utils
{

String::String() : m_characters(1, '\0')
{
}

String::String(const char* literal) : m_characters(literal, literal + (std::strlen(literal) + 1))
{
}

String::String(Size length, char c) : m_characters(length + 1, c)
{
    m_characters.last() = '\0';
}

String::String(const Array<char>& arr) : m_characters(arr)
{
}

String::String(Array<char>&& arr) : m_characters(std::move(arr))
{
}

String String::contentOf(std::istream& istream)
{
    String output;

    int c = istream.get();
    while (c != std::istream::traits_type::eof())
    {
        output.append(c);
        c = istream.get();
    }

    return output;
}

String String::contentOfFile(const String& path)
{
    std::ifstream ifstream(std::string((const char*)path));
    return String::contentOf(ifstream);
}

String String::fromUInt(uint32 nbr)
{
    if (nbr / 10 == 0)
        return String(1, (char)(nbr + '0'));
    return String::fromUInt(nbr / 10) + String(1, (char)(nbr % 10 + '0'));
}

void String::append(char c)
{
    m_characters.last() = c;
    m_characters.append('\0');
}

String::Index String::lastIndexOf(char c) const
{
    Index idx = length() - 1;
    while (m_characters[idx] != c)
        idx--;
    return idx;
}

String String::substr(Index start, Size len) const
{
    String newStr(len, '\0');
    for (Index idx = 0; idx < len; idx++)
        newStr[idx] = m_characters[start + idx];
    return newStr;
}

String operator + (const String& s1, const String& s2)
{
    Array<char> characters((const char*)s1, (const char*)s1 + s1.length());
    characters.append((const char*)s2, (const char*)s2 + s2.length() + 1);
    return String(std::move(characters));
}

}
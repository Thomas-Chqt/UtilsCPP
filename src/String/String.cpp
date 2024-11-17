/*
 * ---------------------------------------------------
 * String.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 16:50:49
 * ---------------------------------------------------
 */

#include "UtilsCPP/String.hpp"
#include "UtilsCPP/Types.hpp"

#include <cstring>
#include <istream>
#include <fstream>

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

String String::contentOf(std::istream& istream)
{
    String output;

    char c = (char)istream.get();
    while (c != std::istream::traits_type::eof())
    {
        output.append(c);
        c = (char)istream.get();
    }

    return output;
}

String String::contentOfFile(const String& path)
{
    std::ifstream ifstream(std::string((const char*)path));
    return String::contentOf(ifstream);
}

String String::fromUInt(uint32 nbr) // NOLINT(misc-no-recursion)
{
    if (nbr / 10 == 0) // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        return String(1, (char)(nbr + '0'));
    return String::fromUInt(nbr / 10) + String(1, (char)(nbr % 10 + '0')); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
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

String String::substr(Index start, Size len) const // NOLINT(bugprone-easily-swappable-parameters)
{
    String newStr(len, '\0');
    for (Index idx = 0; idx < len; idx++)
        newStr[idx] = m_characters[start + idx];
    return newStr;
}

void String::safecpy(char* dst, uint64 buffSize) const
{
    uint64 i = 0;
    for (; i < buffSize - 1 && i < length(); i++)
        dst[i] = m_characters[i];
    dst[i] = '\0';
}

String operator + (const String& s1, const String& s2)
{
    String output(s1.length() + s2.length());
    std::memcpy(&output[0],           (const char*)s1, s1.length());
    std::memcpy(&output[s1.length()], (const char*)s2, s2.length());
    return output;
}

}
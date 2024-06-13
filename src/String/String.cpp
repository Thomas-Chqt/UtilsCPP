/*
 * ---------------------------------------------------
 * String.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/12/01 16:50:49
 * ---------------------------------------------------
 */

#include "UtilsCPP/String.hpp"

#include <cstring>
#include <istream>
#include <fstream>

namespace utils
{

String::String() : m_characters(1, '\0')
{
}

String::String(const char *&& literal) : m_characters(literal, literal + (std::strlen(literal) + 1))
{
}

String::String(Size length, char c) : m_characters(length + 1, c)
{
    m_characters.last() = '\0';
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

void String::append(char c)
{
    m_characters.last() = c;
    m_characters.append('\0');
}

String operator + (const String& s1, const String& s2)
{
    String output(s1.length() + s2.length());
    std::memcpy(&output[0],           (const char*)s1, s1.length());
    std::memcpy(&output[s1.length()], (const char*)s2, s2.length());
    return output;
}

}
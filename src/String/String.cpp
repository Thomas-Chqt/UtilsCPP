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

String String::contentOfFile(const std::string& path)
{
    std::ifstream ifstream(path);
    return String::contentOf(ifstream);
}

void String::append(char c)
{
    m_characters.last() = c;
    m_characters.append('\0');
}

}
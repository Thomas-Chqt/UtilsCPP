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

}
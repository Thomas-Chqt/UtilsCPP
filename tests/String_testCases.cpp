/*
 * ---------------------------------------------------
 * String_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 15:18:50
 * ---------------------------------------------------
 */

#include <gtest/gtest.h>

#include "UtilsCPP/String.hpp"
#include "./random.hpp"
#include <cstring>

namespace utils_tests
{

using byte = unsigned char;

class String : public testing::TestWithParam<std::string>
{
public:
    String() : string(*reinterpret_cast<utils::String*>(stringBytes)),
               editableConstString(*reinterpret_cast<utils::String*>(cosntStringBytes)),
               constString(*reinterpret_cast<utils::String*>(cosntStringBytes))
    {
        string.m_characters.m_length = GetParam().size();
        string.m_characters.m_capacity = random<utils::String::Size>(GetParam().size(), GetParam().size() * 3);
        string.m_characters.m_buffer = (char*)::operator new (string.m_characters.m_capacity);
        std::strncpy(string.m_characters.m_buffer, GetParam().c_str(), string.m_characters.m_length);

        editableConstString.m_characters.m_length = GetParam().size();
        editableConstString.m_characters.m_capacity = string.m_characters.m_capacity;
        editableConstString.m_characters.m_buffer = (char*)::operator new (editableConstString.m_characters.m_capacity);
        std::strncpy(editableConstString.m_characters.m_buffer, GetParam().c_str(), editableConstString.m_characters.m_length);
    }

    ~String()
    {
        ::operator delete (string.m_characters.m_buffer);
        ::operator delete (editableConstString.m_characters.m_buffer);
    }

private:
    byte stringBytes[sizeof(utils::String)] = {};
    byte cosntStringBytes[sizeof(utils::String)] = {};
    utils::String& editableConstString;

protected:
    utils::String& string;
    const utils::String& constString;
};

INSTANTIATE_TEST_SUITE_P(, String, testing::Values(
    "", "qwerty", "\t\r\n", "可愛い猫"
));

TEST_P(String, defaultConstructor)
{
    using String = utils::String;

    byte bytes[sizeof(String)] = {};
    String& string = *reinterpret_cast<String*>(bytes);

    new (&string) String();

    EXPECT_EQ(string.m_characters.m_length,       1);
    EXPECT_TRUE(string.m_characters.m_capacity >= 1);
    EXPECT_NE(string.m_characters.m_buffer,       nullptr);
    EXPECT_EQ(string.m_characters[0],             '\0');

    ::operator delete (string.m_characters.m_buffer);
}

TEST_P(String, literalConstructor)
{
    using String = utils::String;
    using Index = utils::String::Index;

    byte bytes[sizeof(String)] = {};
    String& string = *reinterpret_cast<String*>(bytes);

    new (&string) String(GetParam().c_str());

    EXPECT_EQ(string.m_characters.m_length, GetParam().size() + 1);
    EXPECT_TRUE(string.m_characters.m_capacity >= GetParam().size() + 1);
    EXPECT_NE(string.m_characters.m_buffer, nullptr);
    EXPECT_EQ(string.m_characters[string.m_characters.m_length - 1], '\0');

    for (Index i = 0; i < string.m_characters.m_length - 1; i++)
        EXPECT_EQ(string.m_characters.m_buffer[i], GetParam()[i]);

    ::operator delete (string.m_characters.m_buffer);
}

}
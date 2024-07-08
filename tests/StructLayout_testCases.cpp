/*
 * ---------------------------------------------------
 * StructLayout_testCases.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/07/07 19:21:42
 * ---------------------------------------------------
 */

#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/StructLayout.hpp"
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

namespace utils_tests
{

TEST(StructLayoutTest, sizeOf1)
{
    struct structA
    {
        int a;
        int b;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(int, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 1, "b")
    };

    ASSERT_EQ(sizeof(structA), sizeOf(structALayout));
}

TEST(StructLayoutTest, sizeOf2)
{
    struct structA
    {
        char a;
        int b;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(char, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 1, "b")
    };

    ASSERT_EQ(sizeof(structA), sizeOf(structALayout));
}

TEST(StructLayoutTest, sizeOf3)
{
    struct structA
    {
        char a;
        int b[3];
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(char, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 3, "b")
    };

    ASSERT_EQ(sizeof(structA), sizeOf(structALayout));
}

TEST(StructLayoutTest, sizeOf4)
{
    struct structA
    {
        char a;
        int b[3];
        long c;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(char, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 3, "b"),
        STRUCT_LAYOUT_ELEMENT(long, 1, "c")
    };

    ASSERT_EQ(sizeof(structA), sizeOf(structALayout));
}

TEST(StructLayoutTest, offsets1)
{
    struct structA
    {
        char a;
        char b;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(char, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(char, 1, "b")
    };

    std::vector<size_t> alignement = { 
        offsetof(structA, a),
        offsetof(structA, b)
    };

    std::vector<size_t>::iterator it = alignement.begin();
    for (auto& element : structALayout)
        EXPECT_EQ(element.offset, *it++);
}

TEST(StructLayoutTest, offsets2)
{
    struct structA
    {
        long a;
        char b;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(long, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(char, 1, "b")
    };

    std::vector<size_t> alignement = { 
        offsetof(structA, a),
        offsetof(structA, b)
    };

    std::vector<size_t>::iterator it = alignement.begin();
    for (auto& element : structALayout)
        EXPECT_EQ(element.offset, *it++);
}

TEST(StructLayoutTest, offsets3)
{
    struct structA
    {
        long a;
        int b;
        char c;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(long, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 1, "b"),
        STRUCT_LAYOUT_ELEMENT(char, 1, "c")
    };

    std::vector<size_t> alignement = { 
        offsetof(structA, a),
        offsetof(structA, b),
        offsetof(structA, c)
    };

    std::vector<size_t>::iterator it = alignement.begin();
    for (auto& element : structALayout)
        EXPECT_EQ(element.offset, *it++);
}

TEST(StructLayoutTest, offsets4)
{
    struct structA
    {
        long a;
        int b[3];
        char c;
    };

    utils::StructLayout structALayout = {
        STRUCT_LAYOUT_ELEMENT(long, 1, "a"),
        STRUCT_LAYOUT_ELEMENT(int, 3, "b"),
        STRUCT_LAYOUT_ELEMENT(char, 1, "c")
    };

    std::vector<size_t> alignement = { 
        offsetof(structA, a),
        offsetof(structA, b),
        offsetof(structA, c)
    };

    std::vector<size_t>::iterator it = alignement.begin();
    for (auto& element : structALayout)
        EXPECT_EQ(element.offset, *it++);
}

}
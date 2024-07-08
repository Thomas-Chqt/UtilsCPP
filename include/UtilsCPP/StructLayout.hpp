/*
 * ---------------------------------------------------
 * StructLayout.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/07/07 10:29:44
 * ---------------------------------------------------
 */

#ifndef STRUCTLAYOUT_HPP
# define STRUCTLAYOUT_HPP

#include "UtilsCPP/Array.hpp"
#include "UtilsCPP/String.hpp"
#include "UtilsCPP/Types.hpp"
#include <initializer_list>

#define STRUCT_LAYOUT_ELEMENT(type, count, name) { utils::getTypeID<type>(), count, name, sizeof(type), alignof(type), 0, utils::getLayout<type>() }

#define TYPEID_UCHAR  1
#define TYPEID_CHAR   2
#define TYPEID_USHORT 3
#define TYPEID_SHORT  4
#define TYPEID_UINT   5
#define TYPEID_INT    6
#define TYPEID_FLOAT  7
#define TYPEID_ULONG  8
#define TYPEID_LONG   9
#define TYPEID_DOUBLE 10
#define TYPEID_ULLONG 11
#define TYPEID_LLONG  12

namespace utils
{

struct StructLayoutElement;

class StructLayout : public Array<StructLayoutElement>
{
public:
    StructLayout()                    = default;
    StructLayout(const StructLayout&) = default;
    StructLayout(StructLayout&&)      = default;
    
    StructLayout(const std::initializer_list<Element>&);

    void recomputeOffsetsAndSize();
    friend inline uint32 sizeOf(const StructLayout& layout);

    ~StructLayout() override = default;

private:
    uint32 m_size = 0;

public:
    StructLayout& operator = (const StructLayout&) = default;
    StructLayout& operator = (StructLayout&&)      = default;
};

struct StructLayoutElement
{
    uint32 typeId;
    uint32 count;
    String name;
    uint32 size;
    uint32 align;
    uint32 offset;
    StructLayout layout;
};

template<typename T> StructLayout getLayout();
template<typename T> uint32 getTypeID();

inline uint32 sizeOf(const StructLayout& layout) { return layout.m_size; }

}

#endif // STRUCTLAYOUT_HPP
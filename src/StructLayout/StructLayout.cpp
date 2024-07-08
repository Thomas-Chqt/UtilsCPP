/*
 * ---------------------------------------------------
 * StructLayout.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/07/07 15:55:38
 * ---------------------------------------------------
 */

#include "UtilsCPP/StructLayout.hpp"
#include "UtilsCPP/Types.hpp"

namespace utils
{

StructLayout::StructLayout(const std::initializer_list<Element>& init_list)
    : Array<StructLayoutElement>(init_list)
{
    recomputeOffsetsAndSize();
}

void StructLayout::recomputeOffsetsAndSize()
{
    m_size = 0;
    utils::uint32 maxAlign = 1;
    for (auto& element : *this)
    {
        maxAlign = maxAlign > element.align ? maxAlign : element.align;
        m_size = (m_size + element.align - 1) & ~(element.align - 1);
        element.offset = m_size;
        m_size += element.size * element.count;
    }
    m_size = (m_size + maxAlign - 1) & ~(maxAlign - 1);
}

template<> StructLayout getLayout<unsigned char>() { return StructLayout(); }
template<> uint32 getTypeID<unsigned char>() { return TYPEID_UCHAR; }

template<> StructLayout getLayout<char>() { return StructLayout(); }
template<> uint32 getTypeID<char>() { return TYPEID_CHAR; }

template<> StructLayout getLayout<unsigned short>() { return StructLayout(); }
template<> uint32 getTypeID<unsigned short>() { return TYPEID_USHORT; }

template<> StructLayout getLayout<short>() { return StructLayout(); }
template<> uint32 getTypeID<short>() { return TYPEID_SHORT; }

template<> StructLayout getLayout<unsigned int>() { return StructLayout(); }
template<> uint32 getTypeID<unsigned int>() { return TYPEID_UINT; }

template<> StructLayout getLayout<int>() { return StructLayout(); }
template<> uint32 getTypeID<int>() { return TYPEID_INT; }

template<> StructLayout getLayout<float>() { return StructLayout(); }
template<> uint32 getTypeID<float>() { return TYPEID_INT; }

template<> StructLayout getLayout<unsigned long>() { return StructLayout(); }
template<> uint32 getTypeID<unsigned long>() { return TYPEID_ULONG; }

template<> StructLayout getLayout<long>() { return StructLayout(); }
template<> uint32 getTypeID<long>() { return TYPEID_LONG; }

template<> StructLayout getLayout<double>() { return StructLayout(); }
template<> uint32 getTypeID<double>() { return TYPEID_DOUBLE; }

template<> StructLayout getLayout<unsigned long long>() { return StructLayout(); }
template<> uint32 getTypeID<unsigned long long>() { return TYPEID_ULLONG; }

template<> StructLayout getLayout<long long>() { return StructLayout(); }
template<> uint32 getTypeID<long long>() { return TYPEID_LLONG; }

}
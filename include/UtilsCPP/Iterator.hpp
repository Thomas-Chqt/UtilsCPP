/*
 * ---------------------------------------------------
 * Iterator.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/04/30 22:57:42
 * ---------------------------------------------------
 */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "Types.hpp"
#include <algorithm>

namespace utils
{

template<typename Iterator>
void swap(const Iterator& ita, const Iterator& itb)
{
    typename Iterator::Element temp = std::move(*ita);
    *ita = std::move(*itb);
    *itb = std::move(temp);
}

template<typename Iterator>
Iterator& operator += (Iterator& it, uint32 n)
{
    for (uint32 i = 0; i < n; i++)
        ++it;
    return it;
}

template<typename Iterator>
Iterator operator + (const Iterator& it, uint32 n)
{
    Iterator outuput = it;
    for (uint32 i = 0; i < n; i++)
        ++outuput;
    return outuput;
}

}


#endif // ITERATOR_HPP
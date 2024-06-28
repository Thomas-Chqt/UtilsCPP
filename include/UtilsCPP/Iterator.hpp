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

}


#endif // ITERATOR_HPP
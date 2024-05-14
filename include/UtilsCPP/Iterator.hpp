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

#include <cstring>

#include "UtilsCPP/Types.hpp"

namespace utils
{

// template<typename Iterator>
// void swap(const Iterator& ita, const Iterator& itb)
// {
//     typename Iterator::Element* temp = (typename Iterator::Element*)operator new (sizeof(typename Iterator::Element));

//     std::memcpy(temp,                             (typename Iterator::Element*)ita, sizeof(typename Iterator::Element));
//     std::memcpy((typename Iterator::Element*)ita, (typename Iterator::Element*)itb, sizeof(typename Iterator::Element));
//     std::memcpy((typename Iterator::Element*)itb, temp,                             sizeof(typename Iterator::Element));

//     operator delete (temp);
// }

}


#endif // ITERATOR_HPP
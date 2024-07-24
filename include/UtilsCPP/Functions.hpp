/*
 * ---------------------------------------------------
 * Functions.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2024/07/23 13:42:49
 * ---------------------------------------------------
 */

#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

namespace utils
{

template<typename T>
void swap(T& a, T& b)
{
    T tmp = b;
    b = a;
    a = tmp;
}

}

#endif // FUNCTIONS_HPP
/*
 * ---------------------------------------------------
 * Types.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/11/29 19:01:51
 * ---------------------------------------------------
 */

#ifndef UCPP_TYPES_HPP
# define UCPP_TYPES_HPP

static_assert(sizeof(unsigned char) == 1, "unsigned char is not 1 byte");

namespace utils
{
    using uint8  = unsigned char;
    using uint16 = unsigned short;
    using uint32 = unsigned int;
    using uint64 = unsigned long;

    using byte = uint8;
}

#endif // UCPP_TYPES_HPP
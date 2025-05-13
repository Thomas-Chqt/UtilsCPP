/*
 * ---------------------------------------------------
 * Types.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2023/11/29 19:01:51
 * ---------------------------------------------------
 */

#ifndef UTL_TYPES_HPP
#define UTL_TYPES_HPP

#include <cstdint>

static_assert(sizeof(unsigned char) == 1, "unsigned char is not 1 byte");

namespace utl
{
    using uint8  = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;

    using byte = uint8;
}

#ifndef UTILS_NAMESPACE
#define UTILS_NAMESPACE
namespace utils = utl; // NOLINT
#endif

#endif // UTL_TYPES_HPP

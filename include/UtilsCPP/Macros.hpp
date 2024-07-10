/*
 * ---------------------------------------------------
 * Macros.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/06/17 22:01:20
 * ---------------------------------------------------
 */

#ifndef DEPRECATED
    #if defined(__GNUC__) || defined(__clang__)
        #define DEPRECATED(msg) __attribute__((deprecated(msg)))
    #elif defined(_MSC_VER)
        #define DEPRECATED(msg) __declspec(deprecated(msg))
    #else
        #pragma message("WARNING: You need to implement DEPRECATED for this compiler")
        #define DEPRECATED(msg)
    #endif
#endif

#ifndef UNREACHABLE
    #if defined(_MSC_VER) && !defined(__clang__) // MSVC
        #define UNREACHABLE __assume(false);
    #else // GCC, Clang
        #define UNREACHABLE __builtin_unreachable();
    #endif
#endif
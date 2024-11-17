/*
 * ---------------------------------------------------
 * Macros.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/06/17 22:01:20
 * ---------------------------------------------------
 */

#ifndef UTILSCPP_MACROS_HPP
#define UTILSCPP_MACROS_HPP

#if defined(__GNUC__) || defined(__clang__)
    #define DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
    #define DEPRECATED(msg) __declspec(deprecated(msg))
#else
    #warning "DEPRECATED is not implemented for this compiler"
    #define DEPRECATED(msg)
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define UNREACHABLE __builtin_unreachable();
#elif defined(_MSC_VER)
    #define UNREACHABLE __assume(false);
#else
    #warning "UNREACHABLE is not implemented for this compiler"
    #define UNREACHABLE;
#endif

#if (defined(__GNUC__) || defined(__clang__)) && defined(UTILSCPP_API_EXPORT)
    #define UTILSCPP_API __attribute__((visibility("default")))
#elif defined(_MSC_VER) && defined(UTILSCPP_API_EXPORT)
    #define UTILSCPP_API __declspec(dllexport)
#elif defined(_MSC_VER) && defined(UTILSCPP_API_IMPORT)
    #define UTILSCPP_API __declspec(dllimport)
#else
    #define UTILSCPP_API
#endif

#endif // UTILSCPP_MACROS_HPP

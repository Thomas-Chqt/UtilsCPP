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

#if defined (__cpp_attributes) && __has_attribute(deprecated)
    #define DEPRECATED(msg) [[deprecated(msg)]]
#elif defined(__GNUC__) || defined(__clang__)
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

#ifdef UTL_API_EXPORT
    #ifdef _WIN32
        #define UTL_API __declspec(dllexport)
    #else
        #define UTL_API __attribute__((visibility("default")))
    #endif
#elif UTL_API_IMPORT
    #ifdef _WIN32
        #define UTL_API __declspec(dllimport)
    #else
        #define UTL_API
    #endif
#else
    #define UTL_API
#endif

#define UTILSCPP_API UTL_API // backward compatibility

#endif // UTILSCPP_MACROS_HPP

/*
 * ---------------------------------------------------
 * UniquePtr.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/05 16:58:38
 * ---------------------------------------------------
 */

#ifndef UNIQUEPTR_HPP
#define UNIQUEPTR_HPP

#include "UtilsCPP/Macros.hpp"
#include "UtilsCPP/memory.hpp"
#include "UtilsCPP/Error.hpp"

namespace utl
{

template<typename T>
    requires(!std::is_array_v<T>)
class UniquePtr : public utl::unique_ptr<T>
{
public:
    ERROR_DEFF(NullPointerError, "Dereferencing a null pointer");

public:
    using Type = T;

private:
    using unique_ptr = unique_ptr<T>;

public:
    using unique_ptr::unique_ptr;

    UniquePtr() = default;
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& mv) noexcept : unique_ptr(std::move(mv)) {}

    template<typename Y>
    DEPRECATED("use move constructor") inline UniquePtr<Y> staticCast() { return UniquePtr<Y>(static_cast<Y*>(unique_ptr::release())); }

    DEPRECATED("use release") inline Type* getOwnership() { return unique_ptr::release(); }

    DEPRECATED("use reset") inline void clear() { return unique_ptr::reset(nullptr); }

    ~UniquePtr() = default;

public:
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& rhs) noexcept
    {
        (void)unique_ptr::operator=(std::move(rhs));
        return *this;
    }

    Type& operator*() const
    {
        if (unique_ptr::operator bool())
            throw NullPointerError();
        return unique_ptr::operator*();
    }

    DEPRECATED("use get") inline operator T*() const { return unique_ptr::get(); } // NOLINT(*-explicit-constructor)

    inline operator bool () const { return unique_ptr::get() != nullptr; } // NOLINT(*-explicit-constructor)
};

template<typename T, typename... ARGS>
UniquePtr<T> makeUnique(ARGS&&... args)
{
    return UniquePtr<T>(new T(std::forward<ARGS>(args)...));
}

} // namespace utl

#ifndef UTILS_NAMESPACE
    #define UTILS_NAMESPACE
namespace utils = utl; // NOLINT
#endif

#endif // UNIQUEPTR_HPP

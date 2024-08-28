/*
 * ---------------------------------------------------
 * Error.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/24 22:49:54
 * ---------------------------------------------------
 */

#ifndef ERROR_HPP
# define ERROR_HPP

#include <ostream>
#include <exception>
#include "UtilsCPP/Macros.hpp"

#define ERR_DESC(str) inline const char* description() const override { return str; }
#define ERROR_DEFF(Type, desc) struct Type : public utils::Error { ERR_DESC(desc) }

namespace utils
{

class UTILSCPP_API Error : public std::exception
{
public:
    Error(const Error&) = default;
    Error(Error&&)      = default;

    virtual const char* description() const = 0;
    inline const char* what() const noexcept override { return description(); };
    
    ~Error() override = default;

protected:
    Error() = default;

public:
    Error& operator = (const Error&) = default;
    Error& operator = (Error&&)      = default;

    UTILSCPP_API inline friend std::ostream& operator << (std::ostream& os, const Error& err) { return os << err.description(); }
};

}

#endif // ERROR_HPP
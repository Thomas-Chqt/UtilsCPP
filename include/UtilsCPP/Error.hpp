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

namespace utils
{

class Error
{
public:
    Error(const Error&) = default;
    Error(Error&&)      = default;

    virtual const char* description() const = 0;
    
    virtual ~Error() = default;

protected:
    Error() = default;

public:
    Error& operator = (const Error&) = default;
    Error& operator = (Error&&)      = default;

    inline friend std::ostream& operator << (std::ostream& os, const Error& err) { return os << err.description(); }
};

}

#endif // ERROR_HPP
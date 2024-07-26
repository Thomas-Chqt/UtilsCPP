/*
 * ---------------------------------------------------
 * RuntimeError.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/25 11:41:50
 * ---------------------------------------------------
 */

#ifndef RUNTIMEERROR_HPP
# define RUNTIMEERROR_HPP

#include "UtilsCPP/Error.hpp"
#include "UtilsCPP/String.hpp"

namespace utils
{

class RuntimeError : public Error
{
public:
    RuntimeError()                        = delete;
    RuntimeError(const RuntimeError&)     = default;
    RuntimeError(RuntimeError&&) noexcept = default;

    explicit RuntimeError(String);

    inline const char* description() const override { return (const char*)m_description; }

    ~RuntimeError() override = default;

private:
    String m_description;

public:
    RuntimeError& operator = (const RuntimeError&) = default;
    RuntimeError& operator = (RuntimeError&&)      = default;
};


}

#endif // RUNTIMEERROR_HPP
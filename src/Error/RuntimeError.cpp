/*
 * ---------------------------------------------------
 * RuntimeError.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/25 10:05:38
 * ---------------------------------------------------
 */

#include "UtilsCPP/RuntimeError.hpp"

#include <utility>

namespace utils
{

RuntimeError::RuntimeError(String desc) : m_description(std::move(desc))
{
}

}
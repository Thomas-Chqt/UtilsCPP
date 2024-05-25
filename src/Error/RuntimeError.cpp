/*
 * ---------------------------------------------------
 * RuntimeError.cpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/25 10:05:38
 * ---------------------------------------------------
 */

#include "UtilsCPP/RuntimeError.hpp"

namespace utils
{

RuntimeError::RuntimeError(const String& desc) : m_description(desc)
{
}

}
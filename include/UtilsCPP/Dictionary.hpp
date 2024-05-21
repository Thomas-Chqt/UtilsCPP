/*
 * ---------------------------------------------------
 * Dictionary.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/05/21 13:01:50
 * ---------------------------------------------------
 */

#ifndef DICTIONARY_HPP
# define DICTIONARY_HPP

#include "UtilsCPP/Array.hpp"
#include <algorithm>
#include <cstdlib>

namespace utils
{

template<typename Key, typename Value>
class Dictionary
{
private:
    struct KeyValPair
    {
        Key key;
        Value val;
        inline bool operator == (const Key& rhs) { return key == rhs; }
    };

public:
    using DataStructure = Array<KeyValPair>; // TODO use tree
    using Size          = typename DataStructure::Size;

public:
    Dictionary()                  = default;
    Dictionary(const Dictionary&) = default;
    Dictionary(Dictionary&&)      = default;

    inline bool contain(const Key& key) const { return m_data.contain(key); }
    inline Size size() const { return m_data.length(); }

    void insert(const Key& key, const Value& val)
    {
        if (m_data.contain(key))
            std::abort(); // TODO use throw
        m_data.append((KeyValPair){ Key(key), Value(val) });
    }

    void insert(const Key& key, Value&& val)
    {
        if (m_data.contain(key))
            std::abort(); // TODO use throw
        m_data.append((KeyValPair){ Key(key), Value(std::move(val)) });
    }

    void remove(const Key& key)
    {
        typename DataStructure::Iterator it = m_data.find(key);
        if (it == m_data.end())
            return;
        m_data.remove(it);
    }

private:
    DataStructure m_data;

public:
    Dictionary& operator = (const Dictionary&) = default;
    Dictionary& operator = (Dictionary&&)      = default;

    Value& operator [] (const Key& key)
    {
        typename DataStructure::Iterator it = m_data.find(key);

        if (it == m_data.end())
            std::abort(); // TODO use throw

        return it->val;
    }

    const Value& operator [] (const Key& key) const
    {
        typename DataStructure::const_Iterator it = m_data.find(key);

        if (it == m_data.end())
            std::abort(); // TODO use throw

        return it->val;
    }
};

}

#endif // DICTIONARY_HPP
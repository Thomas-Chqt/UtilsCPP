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
#include "UtilsCPP/Error.hpp"
#include <algorithm>
#include <cstdlib>

namespace utils
{

template<typename Key, typename Value>
class Dictionary
{
public:
    struct DuplicateKeyError : public Error { inline const char* description() const override { return "Key already in the dictionary"; } };
    struct KeyNoFoundError : public Error { inline const char* description() const override { return "Key not in the dictionary"; } };

public:
    struct KeyValPair
    {
        Key key;
        Value val;
    };

public:
    using DataStructure  = Array<KeyValPair>; // TODO use tree
    using Size           = typename DataStructure::Size;
    using Iterator       = typename DataStructure::Iterator;
    using const_Iterator = typename DataStructure::const_Iterator;

public:
    Dictionary()                  = default;
    Dictionary(const Dictionary&) = default;
    Dictionary(Dictionary&&)      = default;

    inline bool contain(const Key& key) const { return m_data.containWhere([&key](const KeyValPair& e){ return e.key == key; }); }
    inline Size size() const { return m_data.length(); }

    inline       Iterator begin()       { return m_data.begin(); }
    inline const_Iterator begin() const { return m_data.begin(); }
    inline       Iterator end()         { return m_data.end(); }
    inline const_Iterator end()   const { return m_data.end(); }

    void insert(const Key& key, const Value& val)
    {
        if (m_data.containWhere([&key](const KeyValPair& e){ return e.key == key; }))
            throw DuplicateKeyError();
        m_data.append(KeyValPair{ Key(key), Value(val) });
    }

    void insert(const Key& key, Value&& val)
    {
        if (m_data.containWhere([&key](const KeyValPair& e){ return e.key == key; }))
            throw DuplicateKeyError();
        m_data.append(KeyValPair{ Key(key), Value(std::move(val)) });
    }

    void remove(const Key& key)
    {
        typename DataStructure::Iterator it = m_data.findWhere([&key](const KeyValPair& e){ return e.key == key; });
        if (it == m_data.end())
            return;
        m_data.remove(it);
    }

    inline void clear() { m_data.clear(); }

private:
    DataStructure m_data;

public:
    Dictionary& operator = (const Dictionary&) = default;
    Dictionary& operator = (Dictionary&&)      = default;

    Value& operator [] (const Key& key)
    {
        typename DataStructure::Iterator it = m_data.findWhere([&key](const KeyValPair& e){ return e.key == key; });

        if (it == m_data.end())
            throw KeyNoFoundError();

        return it->val;
    }

    const Value& operator [] (const Key& key) const
    {
        typename DataStructure::const_Iterator it = m_data.findWhere([&key](const KeyValPair& e){ return e.key == key; });

        if (it == m_data.end())
            throw KeyNoFoundError();

        return it->val;
    }
};

}

#endif // DICTIONARY_HPP

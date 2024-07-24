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

#include "Set.hpp"
#include "Error.hpp"
#include <algorithm>
#include <cstdlib>
#include "Macros.hpp"

namespace utils
{

template<typename Key, typename Value>
class Dictionary
{
public:
    struct KeyNoFoundError : public Error { inline const char* description() const override { return "Key not in the dictionary"; } };

public:
    struct KeyValPair
    {
        Key key;
        Value val;

        inline bool operator == (const KeyValPair& rhs) { return key == rhs.key ; }
        inline bool operator  < (const KeyValPair& rhs) { return key  < rhs.key ; }

        inline bool operator == (const Key& rhsKey) { return key == rhsKey; }
        inline bool operator  < (const Key& rhsKey) { return key  < rhsKey; }
    };

public:
    using DataStructure  = Set<KeyValPair>;
    using Size           = typename DataStructure::Size;
    using Iterator       = typename DataStructure::Iterator;
    using const_Iterator = typename DataStructure::const_Iterator;

public:
    Dictionary()                  = default;
    Dictionary(const Dictionary&) = default;
    Dictionary(Dictionary&&)      = default;

    inline bool contain(const Key& key) const { return m_data.contain(key); }
    inline Size size() const { return m_data.size(); }

    inline       Iterator begin()       { return m_data.begin(); }
    inline const_Iterator begin() const { return m_data.begin(); }
    inline       Iterator end()         { return m_data.end(); }
    inline const_Iterator end()   const { return m_data.end(); }

    inline void insert(const Key& key, const Value& val) { m_data.insert(KeyValPair{key, val}); }
    inline void insert(const Key& key, Value&& val) { m_data.insert(KeyValPair{key, std::move(val)}); }

    inline void remove(const Key& key) { } // TODO

    inline void clear() { m_data.clear(); }

    DEPRECATED("will be remove or changed")
    Value& get(const Key& key, const Value& deff = Value())
    {
        if (contain(key) == false)
            insert(key, deff);
        return operator[](key);
    }

    ~Dictionary() = default;

private:
    DataStructure m_data;

public:
    Dictionary& operator = (const Dictionary&) = default;
    Dictionary& operator = (Dictionary&&)      = default;

    Value& operator [] (const Key& key)
    {
        typename DataStructure::Iterator it = m_data.find(key);

        if (it == m_data.end())
            throw KeyNoFoundError();

        return it->val;
    }

    const Value& operator [] (const Key& key) const
    {
        typename DataStructure::const_Iterator it = m_data.find(key);

        if (it == m_data.end())
            throw KeyNoFoundError();

        return it->val;
    }
};

}

#endif // DICTIONARY_HPP

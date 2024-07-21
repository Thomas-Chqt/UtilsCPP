/*
 * ---------------------------------------------------
 * Set.hpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2024/07/21 14:28:25
 * ---------------------------------------------------
 */

#ifndef SET_HPP
# define SET_HPP

#include "UtilsCPP/Error.hpp"
#include "UtilsCPP/Types.hpp"
#include "UtilsCPP/UniquePtr.hpp"
#include <utility>

namespace utils
{

template<typename T>
class Set
{
public:
    struct DuplicateElementError : public Error { inline const char* description() const override { return "Element already in the set"; } };

public:
    using Element = T;

    class Iterator;
    class const_Iterator;

public:
    Set() = default;
    Set(const Set& cp) : m_root(cloneSubTree(cp.m_root, nullptr)) {}
    Set(Set&& mv) = default;

    inline bool isEmpty() { return m_root == false; }
    inline uint32 size() { return subTreeSize(m_root); }

    Iterator begin()
    {
        Node* curr = m_root;
        while (curr->left != nullptr)
            curr = curr->left;
        return Iterator(curr);
    }

    inline Iterator end() { return Iterator(nullptr); }

    Iterator insert(const Element& value)
    {
        if (m_root)
            return insertNodeInSubTree(m_root, UniquePtr<Node>(new Node(value)));
        m_root = UniquePtr<Node>(new Node(value));
        return &m_root;
    }

    inline Iterator find(const Element& value) { return findNodeInSubTree(m_root, value); }

    void remove(const Iterator& it)
    {
        UniquePtr<Node>& node
    }
    
    ~Set() = default;

private:
    struct Node
    {
        Node(const T& value) : value(value) {}
        T value;
        Node* parent;
        UniquePtr<Node> left;
        UniquePtr<Node> right;
    };

    static UniquePtr<Node> cloneSubTree(const UniquePtr<Node>& src, Node* parent)
    {
        if (src == false)
            return utils::UniquePtr<Node>();
        utils::UniquePtr<Node> newNode = utils::UniquePtr<Node>(new Node(src->value));
        newNode->parent = parent;
        newNode->left = cloneSubTree(src->left, newNode);
        newNode->right = cloneSubTree(src->right, newNode);
        return newNode;
    }

    static uint32 subTreeSize(const UniquePtr<Node>& root)
    {
        if (root == false)
            return 0;
        return 1 + subTreeSize(root->left) + subTreeSize(root->right);
    }

    static const UniquePtr<Node>* insertNodeInSubTree(const UniquePtr<Node>& subTreeRoot, utils::UniquePtr<Node>&& newNode)
    {
        if (subTreeRoot->value == newNode->value)
            throw DuplicateElementError();
        if (newNode->value < subTreeRoot->value)
        {
            if (subTreeRoot->left == nullptr)
            {
                newNode->parent = subTreeRoot;
                subTreeRoot->left = std::move(newNode);
                return &subTreeRoot->left;
            }
            else
                return insertNodeInSubTree(subTreeRoot->left, std::move(newNode));
        }
        else if (subTreeRoot->right == nullptr)
        {
            newNode->parent = subTreeRoot;
            subTreeRoot->right = std::move(newNode);
            return &subTreeRoot->right;
        }
        else   
            return insertNodeInSubTree(subTreeRoot->right, std::move(newNode));
    }

    static const UniquePtr<Node>* findNodeInSubTree(const UniquePtr<Node>& subTreeRoot, const Element& value)
    {
        if (subTreeRoot == nullptr)
            return nullptr;

        if (subTreeRoot->value == value)
            return &subTreeRoot;
        
        if (value < subTreeRoot->value)
            return findNodeInSubTree(subTreeRoot->left, value);
        return findNodeInSubTree(subTreeRoot->right, value);
    }

    UniquePtr<Node> m_root;

public:
    class Iterator
    {
    private:
        friend class Set<T>;

    public:
        Iterator()                   = default;
        Iterator(const Iterator& cp) = default;
        Iterator(Iterator&& mv)      = default;

    private:
        Iterator(const UniquePtr<Node>& node) : m_node(&node) {}
        Iterator(const UniquePtr<Node>* node) : m_node(node) {}

        const UniquePtr<Node>* m_node = nullptr;

    public:
        Iterator& operator = (const Iterator& cp) = default;
        Iterator& operator = (Iterator&& mv)      = default;

        inline Element& operator  * () const { return  (*m_node)->value;  };
        inline Element* operator -> () const { return &(*m_node)->value; };

        inline bool operator == (const Iterator& rhs) const { return m_node == rhs.m_node; }
        inline bool operator != (const Iterator& rhs) const { return !(*this == rhs); }

    };
};

}

#endif // SET_HPP
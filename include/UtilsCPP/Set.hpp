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
#include "UtilsCPP/Func.hpp"
#include "UtilsCPP/Types.hpp"
#include "UtilsCPP/UniquePtr.hpp"

#include <utility>

namespace utils
{

template<typename T>
class Set
{
public:
    ERROR_DEFF(DuplicateElementError, "Element already in the set");

public:
    using Element = T;
    using Size    = uint64;

    class Iterator;
    class const_Iterator;

public:
    Set() = default;

    Set(const Set& cp)
    {
        Func<UniquePtr<Node>(const UniquePtr<Node>&)> cloneSubTree = [&](const UniquePtr<Node>& src)
        {
            if (src == nullptr)
                return utils::UniquePtr<Node>();
            utils::UniquePtr<Node> newNode = utils::UniquePtr<Node>(new Node(src->value));
            newNode->left = cloneSubTree(src->left);
            if (newNode->left != nullptr)
                newNode->left->parent = newNode;
            newNode->right = cloneSubTree(src->right);
            if (newNode->right != nullptr)
                newNode->right->parent = newNode;
            return newNode;
        };
        m_root = cloneSubTree(cp.m_root);
    }

    Set(Set&&) = default;

    Set(std::initializer_list<Element>&& init_list)
    {
        for (auto&& elem : init_list)
            insert(std::move(elem));
    }

    inline bool isEmpty() const { return m_root == false; }
    
    Size size() const
    {
        Func<Size(const UniquePtr<Node>&)> subTreeSize = [&](const UniquePtr<Node>& root) -> Size
        {
            if (root == false)
                return 0;
            return 1 + subTreeSize(root->left) + subTreeSize(root->right);
        };
        return subTreeSize(m_root);
    }

    Iterator begin()
    {
        Node* curr = m_root;
        while (curr != nullptr && curr->left != nullptr)
            curr = curr->left;
        return Iterator(curr);
    }

    const_Iterator begin() const { return const_Iterator(const_cast<Set*>(this)->begin()); }

    inline Iterator end() { return Iterator(nullptr); }
    inline const_Iterator end() const { return const_Iterator(const_cast<Set*>(this)->end()); }

    Iterator insert(Element&& value)
    {
        Func<Node*(Node*)> insertInSubTree = [&](Node* root) -> Node* {
            if (root->value == value)
                throw DuplicateElementError();
            if (value < root->value)
            {
                if (root->left == nullptr)
                    return root->left = makeUnique<Node>(std::move(value), root);
                return insertInSubTree(root->left);
            }
            else
            {
                if (root->right == nullptr)
                    return root->right = makeUnique<Node>(std::move(value), root);
                return insertInSubTree(root->right);
            }
        };
        if (m_root == nullptr)
            return Iterator(m_root = makeUnique<Node>(std::move(value), nullptr));
        return Iterator(insertInSubTree(m_root));
    }

    // TODO iterator insert

    inline Iterator insert(const Element& value) { return insert((Element&&)Element(value)); }
    
    template<typename Y>
    Iterator find(const Y& value)
    {
        Func<Node*(Node*)> findInSubTree = [&](Node* root) -> Node* {
            if (root == nullptr)
                return nullptr;
            if (root->value == value)
                return root;
            if (root->value < value)
                return findInSubTree(root->right);
            else
                return findInSubTree(root->left);
        };
        return Iterator(findInSubTree(m_root));
    }

    template<typename Y>
    inline const_Iterator find(const Y& value) const { return const_Iterator(const_cast<Set*>(this)->find(value)); }

    template<typename Y>
    inline bool contain(const Y& value) const { return find(value) != end(); }

    inline bool contain(const Set& other) const
    {
        for (const auto& element : other)
        {
            if (contain(element) == false)
                return false;
        }
        return true;
    }

    inline void clear() { m_root.clear(); }

    void remove(const Iterator& it)
    {
        if (it == end())
            return;
        UniquePtr<Node>& node = it.m_node->parent == nullptr ? m_root : (it.m_node->parent->right == it.m_node ? it.m_node->parent->right : it.m_node->parent->left);
        if (node->left == nullptr && node->right == nullptr)
            node.clear();
        else if ((node->left == nullptr && node->right != nullptr) || (node->right == nullptr && node->left != nullptr))
        {
            UniquePtr<Node> tmp = std::move(node->left == nullptr ? node->right : node->left);
            tmp->parent = node->parent;
            node = std::move(tmp);
        }
        else
        {
            UniquePtr<Node>* next = &node->right;
            while ((*next)->left != nullptr)
                next = &(*next)->left;
            if (node->right == (*next))
            {
                UniquePtr<Node> b = std::move(node->right);
                UniquePtr<Node> bl = std::move(b->left);
                UniquePtr<Node> br = std::move(b->right);

                b->parent = node->parent;
                b->setLeft(std::move(node->left));
                b->setRight(std::move(node));

                b->right->setLeft(std::move(bl));
                b->right->setRight(std::move(br));

                node = std::move(b);
            }
            else
            {
                UniquePtr<Node> b = std::move((*next));

                Node* bp = b->parent;
                UniquePtr<Node> bl = std::move(b->left);
                UniquePtr<Node> br = std::move(b->right);

                Node* ap = node->parent;
                UniquePtr<Node> al = std::move(node->left);
                UniquePtr<Node> ar = std::move(node->right);

                b->parent = ap;
                b->setLeft(std::move(al));
                b->setRight(std::move(ar));
                
                node->parent = bp;
                node->setLeft(std::move(bl));
                node->setRight(std::move(br));

                (*next) = std::move(node);
                node = std::move(b);
            }
            remove(it);
        }
    }

    Element pop(const Iterator& it)
    {
        Element output = std::move(it.m_node->value);
        remove(it);
        return output;
    }

    ~Set() = default;

private:
    struct Node
    {        
        Element value;
        Node* parent = nullptr;
        UniquePtr<Node> left;
        UniquePtr<Node> right;
     
        Node() = default;
        Node(const Element& v, Node* parent = nullptr) : value(v), parent(parent) {}
        Node(Element&& v, Node* parent = nullptr) : value(std::move(v)), parent(parent) {}

        void setLeft(UniquePtr<Node>&& node)
        {
            if (node != nullptr)
                node->parent = this;
            left = std::move(node);
        }

        void setRight(UniquePtr<Node>&& node)
        {
            if (node != nullptr)
                node->parent = this;
            right = std::move(node);
        }
    };

    UniquePtr<Node> m_root;

public:
    Set& operator = (const Set& cp)
    {
        if (this != &cp)
            *this = Set(cp);
        return *this;
    }

    Set& operator = (Set&&) = default;

    bool operator == (const Set& rhs) const
    {
        const_Iterator thsCurr = this->begin();
        const_Iterator rhsCurr =   rhs.begin();
        for (; thsCurr != this->end() && rhsCurr != rhs.end(); ++thsCurr, ++rhsCurr)
        {
            if (*thsCurr != *rhsCurr)
                return false;
        }
        return thsCurr == this->end() && rhsCurr == rhs.end();
    }

    inline bool operator != (const Set& rhs) const { return !(*this == rhs); }

    bool operator < (const Set& rhs) const
    {
        const_Iterator itA = begin();
        const_Iterator itB = rhs.begin();
        for (; itA != end() && itB != rhs.end(); ++itA, ++itB)
        {
            if (*itA != *itB)
                return *itA < *itB;
        }
        if (itA != end())
            return false;
        if (itB != rhs.end())
            return true;
        return false;
    }

    Set operator + (Element&& value) const
    {
        Set newSet = *this;
        newSet.insert(std::move(value));
        return newSet;
    }

    inline Set operator + (const Element& value) const { return operator + ((Element&&)Element(value)); }

    Set operator - (const Element& value) const
    {
        Set newSet = *this;
        newSet.remove(newSet.find(value));
        return newSet;
    }

    Set& operator += (const Set& rhs)
    {
        for (const auto& element : rhs)
            insert(element);
        return *this;
    }

    Set operator + (const Set& rhs) const
    {
        Set newSet = *this;
        newSet += rhs;
        return newSet;
    }

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
        Iterator(Node* currNode) : m_node(currNode) {}

        Node* m_node = 0x1;

    public:
        Iterator& operator = (const Iterator& cp) = default;
        Iterator& operator = (Iterator&& mv)      = default;

        inline Element& operator  * () const { return  m_node->value; };
        inline Element* operator -> () const { return &m_node->value; };

        inline bool operator == (const Iterator& rhs) const { return m_node == rhs.m_node; }
        inline bool operator != (const Iterator& rhs) const { return !(*this == rhs); }

        Iterator& operator ++ ()
        {
            if (m_node->right == nullptr)
            {
                const Node* prev = m_node;
                do
                    m_node = m_node->parent;
                while (m_node != nullptr && m_node->value < prev->value);
            }
            else
            {
                m_node = m_node->right;
                while (m_node->left != nullptr)
                    m_node = m_node->left;
            }
            return *this;
        }

        inline Iterator  operator ++ (int) { Iterator temp(*this); ++(*this); return temp; }
    };

    class const_Iterator
    {
    private:
        friend class Set<T>;

    public:
        const_Iterator()                         = default;
        const_Iterator(const const_Iterator& cp) = default;
        const_Iterator(const_Iterator&& mv)      = default;

    private:
        const_Iterator(const Node* node) : m_node(node) {}
        const_Iterator(const Iterator& it) : m_node(it.m_node) {}

        const Node* m_node = 0x1;

    public:
        const_Iterator& operator = (const const_Iterator& cp) = default;
        const_Iterator& operator = (const_Iterator&& mv)      = default;

        inline const Element& operator  * () const { return  m_node->value; };
        inline const Element* operator -> () const { return &m_node->value; };

        inline bool operator == (const const_Iterator& rhs) const { return m_node == rhs.m_node; }
        inline bool operator != (const const_Iterator& rhs) const { return !(*this == rhs); }

        const_Iterator& operator ++ ()
        {
            if (m_node->right == nullptr)
            {
                const Node* prev = m_node;
                do
                    m_node = m_node->parent;
                while (m_node != nullptr && m_node->value < prev->value);
            }
            else
            {
                m_node = m_node->right;
                while (m_node->left != nullptr)
                    m_node = m_node->left;
            }
            return *this;
        }

        inline const_Iterator  operator ++ (int) { const_Iterator temp(*this); ++(*this); return temp; }

    };
};

}

#endif // SET_HPP
#pragma once
#ifndef GUARD_LIS_H
#define GUARD_LIS_H

#include <cstddef>

template <class T>
class Node
{
public:
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node() : value(T()), next(0), prev(0) { }
    Node(T t) : value(t), next(0), prev(0) { }
};

template <class T>
class NodeItr
{
public:
    NodeItr& operator++();
    NodeItr& operator--();
    NodeItr operator++(int);
    NodeItr operator--(int);

    T& operator*() const
    {
        return node->value;
    }

    bool operator!=(const NodeItr& rhs) const
    {
        return node != rhs.node;
    }

    bool operator==(const NodeItr& rhs) const
    {
        return node == rhs.node;
    }

    NodeItr(Node<T>* n = 0) : node(n) { }

    Node<T>* getNode() const
    {
        return node;
    }

private:
    Node<T>* node;
};

template <class T>
NodeItr<T>& NodeItr<T>::operator++()
{
    node = node->next;
    return *this;
}

template <class T>
NodeItr<T>& NodeItr<T>::operator--()
{
    node = node->prev;
    return *this;
}

template <class T>
NodeItr<T> NodeItr<T>::operator++(int)
{
    NodeItr<T> ret(node);
    node = node->next;
    return ret;
}

template <class T>
NodeItr<T> NodeItr<T>::operator--(int)
{
    NodeItr<T> ret(node);
    node = node->prev;
    return ret;
}

template <class T>
class Lis
{
public:
    typedef NodeItr<T> iterator;
    typedef NodeItr<T> const_iterator;
    typedef std::size_t size_type;

    Lis() : b(0), e(0), s(0) { }

    explicit Lis(size_type n, const T& t = T())
    {
        create(n, t);
    }

    Lis(const Lis& v)
    {
        create(v.begin(), v.end());
    }

    Lis& operator=(const Lis& rhs);

    ~Lis()
    {
        uncreate();
    }

    void push_back(const T& t);

    size_type size() const
    {
        return s;
    }

    iterator begin()
    {
        return iterator(b);
    }

    const_iterator begin() const
    {
        return const_iterator(b);
    }

    iterator end()
    {
        return iterator(0);
    }

    const_iterator end() const
    {
        return const_iterator(0);
    }

    void clear()
    {
        uncreate();
    }

    bool empty() const
    {
        return s == 0;
    }

private:
    Node<T>* b;
    Node<T>* e;
    size_type s;

    void create(size_type, const T&);
    void create(iterator, iterator);
    void uncreate();
};

template <class T>
Lis<T>& Lis<T>::operator=(const Lis& rhs)
{
    if (this != &rhs)
    {
        uncreate();
        create(rhs.begin(), rhs.end());
    }

    return *this;
}

template <class T>
void Lis<T>::push_back(const T& t)
{
    Node<T>* node = new Node<T>(t);

    if (s == 0)
    {
        b = e = node;
    }
    else
    {
        e->next = node;
        node->prev = e;
        e = node;
    }

    s++;
}

template <class T>
void Lis<T>::create(size_type n, const T& t)
{
    for (size_type i = 0; i < n; i++)
    {
        push_back(t);
    }
}

template <class T>
void Lis<T>::create(iterator begin_it, iterator end_it)
{
    while (begin_it != end_it)
    {
        push_back(*begin_it);
        begin_it++;
    }
}

template <class T>
void Lis<T>::uncreate()
{
    Node<T>* node = b;

    while (node)
    {
        Node<T>* next = node->next;
        delete node;
        node = next;
    }

    b = e = 0;
    s = 0;
}

#endif

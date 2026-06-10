#pragma once
#ifndef GUARD_STR_H
#define GUARD_STR_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>

#include "Vec.h"

using namespace std;

class Str
{
    friend istream& operator>>(istream&, Str&);

public:
    typedef Vec<char>::size_type size_type;
    typedef Vec<char>::iterator iterator;
    typedef Vec<char>::const_iterator const_iterator;

    Str() { }

    Str(size_type n, char c)
        : data(n, c) { }

    Str(const char* cp)
    {
        copy(cp, cp + strlen(cp),
            back_inserter(data));
    }

    template <class In>
    Str(In b, In e)
    {
        copy(b, e, back_inserter(data));
    }

    size_type size() const
    {
        return data.size();
    }

    char& operator[](size_type i)
    {
        return data[i];
    }

    const char& operator[](size_type i) const
    {
        return data[i];
    }

    Str& operator+=(const Str& s)
    {
        copy(s.data.begin(), s.data.end(),
            back_inserter(data));

        return *this;
    }

    iterator begin()
    {
        return data.begin();
    }

    iterator end()
    {
        return data.end();
    }

    const_iterator begin() const
    {
        return data.begin();
    }

    const_iterator end() const
    {
        return data.end();
    }

    iterator insert(iterator d,
        iterator b,
        iterator e)
    {
        return data.insert(d, b, e);
    }

private:
    Vec<char> data;
};

ostream& operator<<(ostream&, const Str&);
Str operator+(const Str&, const Str&);

#endif

#include <iostream>
#include <stddef.h>
#include <string>
#include "string.h"

using namespace std;

void
String::__init()
{
    __start = nullptr;
    __write = nullptr;
    __end = nullptr;
    __inc = 2;
}

void
String::__alloc(size_type n)
{
    char *_str = __start;
    size_type _size = size();
    while (__inc < size() + n)
        __inc *= 2;
    __start = new char[__inc];
    if (_str)
        std::strcpy(__start, _str);
    __write = __start + _size;
    __end = __start + __inc;
    delete []_str;
}

void
String::__copy(const_pointer _str)
{
    size_type len = strlen(_str);
    __alloc(len + 1);
    std::strcpy(__start, _str);
    __write = __start + len;
}

/*
 * str[pos - n] --> before this->str[index]
 */
void
String::__insert(size_type index, const_pointer _str, size_type pos, size_type n)
{
    size_type len = strlen(_str);
    if (index > size())
        index = size();
    if (n > len)
        n = len;
    if (pos + n > len)
        return;
    if (n + 1 > capacity())
        __alloc(n + 1);
    if (_str) {
        if (index < size()) {  // insert
            std::memcpy(__start + index + n, __start + index, size() - index);
            __start[size() + n] = '\0';
            std::memcpy(__start + index, _str + pos, n);
            __write = __start + size() + n;
        } else {  // append
            std::memcpy(__write, _str + pos, n);
            __write += n;
        }
    }
    if (index >= size())
        *__write = '\0';
}

String::String(const_pointer _str)
{
    __init();
    __copy(_str);
}

String::String(size_type n, char c)
{
    char s[n + 1];
    std::memset(s, c, n);
    s[n] = '\0';
    __init();
    __copy(s);
}

String::String(const String& _str)
{
    __init();
    __copy(_str.c_str());
}

void
String::resize(size_type n, char c)
{
    if (n < size())
        std::memset(__start + n, 0, size() - n);
    else if (n < max_size())
        std::memset(__write, c, n - size());
    else {
        __alloc(n);
        std::memset(__write, c, n - size());
    }
    __write = __start + n;
}

void
String::resize(size_type n)
{
    resize(n, 0);
}

void
String::reserve(size_type res)
{
    if (res > capacity())
        __alloc(res);
}

void
String::clear()
{
    resize(0);
}

String&
String::operator=(const String& _str)
{
    __copy(_str.c_str());

    return *this;
}

String
String::operator+(const String& _str)
{
    append(_str.c_str());

    return *this;
}

bool
String::operator>(const String& _str)
{
    return std::strcmp(c_str(), _str.c_str()) > 0;
}

bool
String::operator<(const String& _str)
{
    return std::strcmp(c_str(), _str.c_str()) < 0;
}

bool
String::operator==(const String& _str)
{
    return std::strcmp(c_str(), _str.c_str()) == 0;
}

char&
String::operator[](size_type index)
{
    return const_cast<char&>(c_str()[index]);
}

void
String::append(const_pointer _str, size_type pos, size_type n)
{
    __insert(size(), _str, pos, n);
}

void
String::append(const String& _str, size_type pos, size_type n)
{
    append(_str.c_str(), pos, n);
}

void
String::append(const_pointer _str, size_type n)
{
    append(_str, 0, n);
}

void
String::append(const_pointer _str)
{
    append(_str, strlen(_str));
}

void
String::append(const String& _str)
{
    append(_str.c_str());
}

void
String::append(size_type n, char c)
{
    char s[n + 1];
    memset(s, c, n);
    s[n] = '\0';
    append(s);
}

int
String::compare(const_pointer _str)
{
    return strcmp(c_str(), _str);
}

int
String::compare(const String& _str)
{
    return compare(_str.c_str());
}

void
String::insert(size_type index, const_pointer _str)
{
    __insert(index, _str, 0, strlen(_str));
}

void
String::insert(size_type index, const String& _str)
{
    insert(index, _str.c_str());
}

void
String::swap(String& _str)
{
    std::swap(*this, _str);
}

int
main(void)
{
    String a("hello");
    String b("12234");
    a.swap(b);
    cout << a.c_str() << b.c_str() << endl;
    string s;
}

#include <iostream>
#include <cstring>
#include "string.h"

void String::_init()
{
    _start = nullptr;
    _write = nullptr;
    _end = nullptr;
    _inc = 2;
}

// 对String进行扩容
void String::_alloc(size_type n)
{
    char *_str = _start;
    size_type _size = size();
    while (_inc < size() + n)
        _inc *= 2;
    _start = new char[_inc];
    if (_str) strcpy(_start, _str);
    _write = _start + _size;
    _end = _start + _inc;
    delete []_str;
}

// 用于copy constructor and copy assign operator
void String::_copy(const_pointer _str)
{
    size_type len = strlen(_str);
    _alloc(len + 1);
    strcpy(_start, _str);
    _write = _start + len;
}

// str[pos - n] --> before this->str[index]
void String::_insert(size_type index, const_pointer _str, size_type pos, size_type n)
{
    size_type len = strlen(_str);
    if (index > size())
        index = size();
    if (n > len)
        n = len;
    if (pos + n > len)
        return;
    if (n + 1 > capacity())
        _alloc(n + 1);
    if (_str) {
        if (index < size()) {  // insert
            memcpy(_start + index + n, _start + index, size() - index);
            _start[size() + n] = '\0';
            memcpy(_start + index, _str + pos, n);
            _write = _start + size() + n;
        } else {  // append
            memcpy(_write, _str + pos, n);
            _write += n;
        }
    }
    if (index >= size())
        *_write = '\0';
}

String::String(const_pointer _str)
{
    _init();
    _copy(_str);
}

String::String(size_type n, value_type c)
{
    char s[n + 1];
    memset(s, c, n);
    s[n] = '\0';
    _init();
    _copy(s);
}

String::String(const String& _str)
{
    std::cout << "&\n";
    _init();
    _copy(_str.c_str());
}

String::String(String&& _str)
{
    std::cout << "&&\n";
    _start = _str._start;
    _write = _str._write;
    _end = _str._end;
    _inc = _str._inc;
    _str._start = nullptr;
}

String& String::operator=(String&& _str)
{
    _start = _str._start;
    _write = _str._write;
    _end = _str._end;
    _inc = _str._inc;
    _str._start = nullptr;
    return *this;
}

void String::resize(size_type n, value_type c)
{
    if (n < size())
        memset(_start + n, 0, size() - n);
    else if (n < max_size())
        memset(_write, c, n - size());
    else {
        _alloc(n);
        memset(_write, c, n - size());
    }
    _write = _start + n;
}

void String::resize(size_type n)
{
    resize(n, 0);
}

void String::reserve(size_type res)
{
    if (res > capacity())
        _alloc(res);
}

void String::clear()
{
    resize(0);
}

String& String::operator=(const String& _str)
{
    _copy(_str.c_str());

    return *this;
}

String operator+(const String& lhs, const String& rhs)
{
    String _str;
    _str.append(lhs);
    _str.append(rhs);

    return _str;
}

String String::operator+=(const String& _str)
{
    append(_str);

    return *this;
}

bool String::operator>(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) > 0;
}

bool String::operator>=(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) >= 0;
}

bool String::operator<(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) < 0;
}

bool String::operator<=(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) <= 0;
}

bool String::operator==(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) == 0;
}

bool String::operator!=(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) != 0;
}

String::value_type& String::operator[](size_type index)
{
    return const_cast<char&>(c_str()[index]);
}

std::ostream& operator<<(std::ostream& _cout, const String& _str)
{
    _cout << _str.c_str();

    return _cout;
}

std::istream& operator>>(std::istream& _cin, String& _str)
{
    char c;

    while ((c = _cin.get()) != '\n')
        _str.append(1, c);

    return _cin;
}

void String::append(const_pointer _str, size_type pos, size_type n)
{
    _insert(size(), _str, pos, n);
}

void String::append(const String& _str, size_type pos, size_type n)
{
    append(_str.c_str(), pos, n);
}

void String::append(const_pointer _str, size_type n)
{
    append(_str, 0, n);
}

void String::append(const_pointer _str)
{
    append(_str, strlen(_str));
}

void String::append(const String& _str)
{
    append(_str.c_str());
}

void String::append(size_type n, value_type c)
{
    char s[n + 1];
    memset(s, c, n);
    s[n] = '\0';
    append(s);
}

int String::compare(const_pointer _str)
{
    return strcmp(c_str(), _str);
}

int String::compare(const String& _str)
{
    return compare(_str.c_str());
}

void String::insert(size_type index, const_pointer _str)
{
    _insert(index, _str, 0, strlen(_str));
}

void String::insert(size_type index, const String& _str)
{
    insert(index, _str.c_str());
}

void String::erase(size_type pos, size_type n)
{
    if (pos + n > size())
        return;
    memcpy(_start + pos, _start + pos + n, size() - pos - n);
    _write -= n;
    *_write = '\0';
}

void String::erase(size_type pos)
{
    erase(pos, 1);
}

void String::push_back(value_type c)
{
    append(1, c);
}

void String::pop_back()
{
    erase(size() - 1, 1);
}

String::size_type String::find(const_pointer _str)
{
    const_pointer p;

    return (p = strstr(c_str(), _str)) ? p - begin() : npos;
}

String::size_type String::rfind(const_pointer _str)
{
    const_pointer p, q, r;

    for (p = cend() - strlen(_str); p >= cbegin(); p--) {
        for (r = p, q = _str; *q && *q == *r; q++, r++)
            ;
        if (*q == '\0')
            return p - cbegin();
    }
    return npos;
}

String::size_type String::find_first_of(const_pointer _str)
{
    const_pointer p, q;

    for (p = _str; *p; p++)
        for (q = cbegin(); q < cend(); q++)
            if (*q == *p)
                return q - cbegin();
    return npos;
}

String::size_type String::find_last_of(const_pointer _str)
{
    const_pointer p, q;

    for (p = _str; *p; p++)
        for (q = cend(); q >= cbegin(); q--)
            if (*q == *p)
                return q - cbegin();
    return npos;
}

String::size_type String::find_first_not_of(const_pointer _str)
{
    const_pointer p, q;

    for (p = cbegin(); p < cend(); p++) {
        for (q = _str; *q; q++)
            if (*q == *p)
                break;
        if (*q == '\0')
            return p - cbegin();
    }
    return npos;
}

String::size_type String::find_last_not_of(const_pointer _str)
{
    const_pointer p, q;

    for (p = cend(); p >= cbegin(); p++) {
        for (q = _str; *q; q++)
            if (*q == *p)
                break;
        if (*q == '\0')
            return p - cbegin();
    }
    return npos;
}

void String::replace(size_type pos, size_type n, const_pointer _str)
{
    if (pos + n > size())
        return;
    erase(pos, n);
    insert(pos, _str);
}

String String::substr(size_type pos, size_type n)
{
    String *_str = new String;

    _str->append(c_str(), pos, n);
    return *_str;
}

void String::swap(String& _str)
{
    std::swap(*this, _str);
}

#include <iostream>
#include <stddef.h>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

class String {
    public:
        typedef char * iterator;
        typedef const char * const_pointer;
        typedef unsigned long size_type;

        String() : _start(nullptr), _write(nullptr), _end(nullptr),
                   _inc(2) { }
        String(const char *str);
        String(size_type n, char c);
        String(const String& str);
        ~String() { delete []_start; }

        String& operator=(const String& str);
        String operator+(const String& str);
        bool operator>(const String& str);
        bool operator<(const String& str);
        bool operator==(const String& str);
        char& operator[](int index);

        iterator begin() const { return _start; }
        iterator end() const { return _end; }
        size_type size() const { return _write - _start; }
        size_type capacity() const { return _end - _write; }
        size_type max_size() const { return _end - _start; }
        const_pointer c_str() const { return _start; }
        bool empty() const { return _start == _write; }
        void append(const char *str, size_type pos, size_type n);
        void append(const String& str, size_type pos, size_type n);
        void append(const char *str, size_type n);
        void append(const char *str);
        void append(const String& str);
        void append(size_type n, char c);
        int compare(const char *str);
        int compare(const String& str);
        void insert(size_type index, const char *str);
        void insert(size_type index, const String& str);
        void reserve() {  }
        void swap() {  }
    private:
        void __copy(const char *str);
        void __insert(size_type index, const char *str, size_type pos, size_type n);
        char *_start;
        char *_write;
        char *_end;
        size_type _inc;
};

void
String::__copy(const char *str)
{
    if (str == nullptr)
        return;
    size_type len = strlen(str);
    _start = new char[len + 1];
    strcpy(_start, str);
    _write = _start + len;
    _end = _write + 1;
}

/*
 * str[pos - n] --> before this->str[index]
 */
void
String::__insert(size_type index, const char *str, size_type pos, size_type n)
{
    size_type len = strlen(str);
    if (index > size())
        index = size();
    if (n > len)
        n = len;
    if (pos + n > len)
        return;
    if (n + 1 > capacity()) {
        char *_str = _start;
        size_type _size = size();
        while (_inc < size() + n + 1)
            _inc *= 2;
        _start = new char[_inc];
        if (_str)
            strcpy(_start, _str);
        _write = _start + _size;
        _end = _start + _inc;
        delete []_str;
    }
    if (str) {
        if (index < size()) {  // insert
            memcpy(_start + index + n, _start + index, n);
            _write = _start + index;
        }
        while (n-- > 0)  // append
            *_write++ = str[pos++];
    }
    *_write = '\0';
}

String::String(const char *str)
{
    __copy(str);
    _inc = 2;
}

String::String(size_type n, char c)
{
    char s[n + 1];
    memset(s, c, n);
    s[n] = '\0';
    __copy(s);
}

String::String(const String& str)
{
    __copy(str.c_str());
    _inc = str._inc;
}

String&
String::operator=(const String& str)
{
    __copy(str.c_str());
    _inc = str._inc;
    return *this;
}

String
String::operator+(const String& str)
{
    append(str.c_str());
    return *this;
}

bool
String::operator>(const String& str)
{
    return strcmp(c_str(), str.c_str()) > 0;
}

bool
String::operator<(const String& str)
{
    return strcmp(c_str(), str.c_str()) < 0;
}

bool
String::operator==(const String& str)
{
    return strcmp(c_str(), str.c_str()) == 0;
}

char&
String::operator[](int index)
{
    return const_cast<char&>(c_str()[index]);
}

void
String::append(const char *str, size_type pos, size_type n)
{
    __insert(size(), str, pos, n);
}

void
String::append(const String& str, size_type pos, size_type n)
{
    append(str.c_str(), pos, n);
}

void
String::append(const char *str, size_type n)
{
    append(str, 0, n);
}

void
String::append(const char *str)
{
    append(str, strlen(str));
}

void
String::append(const String& str)
{
    append(str.c_str());
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
String::compare(const char *str)
{
    return strcmp(c_str(), str);
}

int
String::compare(const String& str)
{
    return compare(str.c_str());
}

void
String::insert(size_type index, const char *str)
{
    __insert(index, str, 0, strlen(str));
}

void
String::insert(size_type index, const String& str)
{
    insert(index, str.c_str());
}

int
main(void)
{
    String a;
    a.append("fjskl");
    a.append("12341234", 4);
    cout << a.c_str() << endl;

    string s;
    s.append("hello");
    s.insert(2, "123");
    cout << s.c_str() << endl;
}

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

        String() : __start(nullptr), __write(nullptr), __end(nullptr),
                   __inc(2) { }
        String(const char *str);
        String(size_type n, char c);
        String(const String& str);
        ~String() { delete []__start; }

        String& operator=(const String& str);
        String operator+(const String& str);
        bool operator>(const String& str);
        bool operator<(const String& str);
        bool operator==(const String& str);
        char& operator[](int index);

        iterator begin() const { return __start; }
        iterator end() const { return __end; }
        size_type size() const { return __write - __start; }
        size_type capacity() const { return __end - __write; }
        size_type max_size() const { return __end - __start; }
        const_pointer c_str() const { return __start; }
        bool empty() const { return __start == __write; }
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
        char *__start;
        char *__write;
        char *__end;
        size_type __inc;
};

void
String::__copy(const char *_str)
{
    if (_str == nullptr)
        return;
    size_type len = strlen(_str);
    __start = new char[len + 1];
    strcpy(__start, _str);
    __write = __start + len;
    __end = __start + len + 1;
}

/*
 * str[pos - n] --> before this->str[index]
 */
void
String::__insert(size_type index, const char *_str, size_type pos, size_type n)
{
    size_type len = strlen(_str);
    if (index > size())
        index = size();
    if (n > len)
        n = len;
    if (pos + n > len)
        return;
    if (n + 1 > capacity()) {
        char *_str = __start;
        size_type _size = size();
        while (__inc < size() + n + 1)
            __inc *= 2;
        __start = new char[__inc];
        if (_str)
            strcpy(__start, _str);
        __write = __start + _size;
        __end = __start + __inc;
        delete []_str;
    }
    if (_str) {
        if (index < size()) {  // insert
            memcpy(__start + index + n, __start + index, size() - index);
            __start[size() + n] = '\0';
            memcpy(__start + index, _str + pos, n);
            __write = __start + size() + n;
        } else {  // append
            memcpy(__write, _str + pos, n);
            __write += n;
        }
    }
    if (index >= size())
        *__write = '\0';
}

String::String(const char *_str)
{
    __copy(_str);
    __inc = 2;
}

String::String(size_type n, char c)
{
    char s[n + 1];
    memset(s, c, n);
    s[n] = '\0';
    __copy(s);
}

String::String(const String& _str)
{
    __copy(_str.c_str());
    __inc = _str.__inc;
}

String&
String::operator=(const String& _str)
{
    __copy(_str.c_str());
    __inc = _str.__inc;

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
    return strcmp(c_str(), _str.c_str()) > 0;
}

bool
String::operator<(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) < 0;
}

bool
String::operator==(const String& _str)
{
    return strcmp(c_str(), _str.c_str()) == 0;
}

char&
String::operator[](int index)
{
    return const_cast<char&>(c_str()[index]);
}

void
String::append(const char *_str, size_type pos, size_type n)
{
    __insert(size(), _str, pos, n);
}

void
String::append(const String& _str, size_type pos, size_type n)
{
    append(_str.c_str(), pos, n);
}

void
String::append(const char *_str, size_type n)
{
    append(_str, 0, n);
}

void
String::append(const char *_str)
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
String::compare(const char *_str)
{
    return strcmp(c_str(), _str);
}

int
String::compare(const String& _str)
{
    return compare(_str.c_str());
}

void
String::insert(size_type index, const char *_str)
{
    __insert(index, _str, 0, strlen(_str));
}

void
String::insert(size_type index, const String& _str)
{
    insert(index, _str.c_str());
}

int
main(void)
{
    String a;
    a.append("helloreadygo");
    cout << a.c_str() << endl;
    a.insert(5, "aaa123");
    cout << a.c_str() << endl;
    a.append("deskmate", 2, 3);
    cout << a.c_str() << endl;
}

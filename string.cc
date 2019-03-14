#include <iostream>
#include <stddef.h>
#include <cstring>

using namespace std;

class String {
    public:
        typedef char * iterator;
        typedef const char * const_pointer;
        typedef unsigned long size_type;

        String() : _start(nullptr), _write(nullptr), _end(nullptr),
                   _inc(2) {  }
        String(const char *str);
        ~String() { delete []_start; }

        String operator+(const String& str);
        String& operator=(const String& str);

        iterator begin() { return _start; }
        iterator end() { return _end; }
        size_type size() { return _write - _start; }
        size_type capacity() { return _end - _write; }
        size_type max_size() { return _end - _start; }
        const_pointer c_str() { return _start; }
        bool empty() { return _start == _write; }
        void reserve() {  }
        void swap() {  }
        void append(const char *str);
    private:
        void __write(size_type len) { _write = _start + len; }
        void __end(size_type len) { _end = _start + len; }
        char *_start;
        char *_write;
        char *_end;
        size_type _inc;
};

String::String(const String& str);
{
    size_type len = strlen(str._start);
    _start = new char[len + 1];
    __write(len);
    __end(len + 1);
}

String&
String::operator=(const String& str)
{
    if (this != &str) {
        delete []_start;
        size_type len = strlen(str._start);
        _start = new char[len + 1];
        __write(len);
        __end(len + 1);
        _inc = str._inc;
    }
    return *this;
}

void
String::append(const char *str)
{
    size_type len = strlen(str);
    if (len > capacity()) {
        char *_s = _start;
        size_type _size = size();
        while (_inc < len + _size + 1)
            _inc *= 2;
        _start = new char[_inc];
        memcpy(_start, _s, _size);
        __write(_size);
        __end(_inc);
        delete []_s;
    }
    memcpy(_write, str, len);
    _write = _start + len;
}

int
main(void)
{
    String a;
    a.append("hello");
}

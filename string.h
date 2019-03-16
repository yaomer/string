#ifndef _STRING_H
#define _STRING_H

class String {
    public:
        typedef char * iterator;
        typedef const char * const_pointer;
        typedef unsigned long size_type;

        String() : __start(nullptr), __write(nullptr), __end(nullptr),
                   __inc(2) { }
        String(const_pointer _str);
        String(size_type n, char c);
        String(const String& _str);
        ~String() { delete []__start; }

        String& operator=(const String& _str);
        String operator+(const String& _str);
        bool operator>(const String& _str);
        bool operator<(const String& _str);
        bool operator==(const String& _str);
        char& operator[](size_type index);

        iterator begin() const { return __start; }
        iterator end() const { return __end; }
        size_type size() const { return __write - __start; }
        size_type capacity() const { return __end - __write; }
        size_type max_size() const { return __end - __start; }
        const_pointer c_str() const { return __start; }
        bool empty() const { return __start == __write; }
        void clear();
        void resize(size_type n, char c);
        void resize(size_type n);
        void reserve(size_type res = 0);
        void append(const_pointer _str, size_type pos, size_type n);
        void append(const String& _str, size_type pos, size_type n);
        void append(const_pointer _str, size_type n);
        void append(const_pointer _str);
        void append(const String& _str);
        void append(size_type n, char c);
        int compare(const_pointer _str);
        int compare(const String& _str);
        void insert(size_type index, const_pointer _str);
        void insert(size_type index, const String& _str);
        void swap(String& _str);
    private:
        void __init();
        void __copy(const_pointer _str);
        void __insert(size_type index, const_pointer _str, size_type pos, size_type n);
        void __alloc(size_type n);
        char *__start;
        char *__write;
        char *__end;
        size_type __inc;
};

#endif /* _STRING_H */

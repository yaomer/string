#include <iostream>
#include <string>
#include "string.h"

using namespace std;

int
main(void)
{
    String a("hello");
    cout << a << endl;
    String b(a);
    cout << b << endl;
    String c = a;
    cout << c << endl;
    String d(10, 'c');
    cout << d << endl;

    cout << a << d << endl;
    a.swap(d);
    cout << a << d << endl;
    a.swap(d);

    a.append("right ");
    cout << a << endl;
    a.append(" angel", 3);
    cout << a << endl;
    a.append("windows", 2, 3);
    cout << a << endl;
    a.append(b);
    cout << a << endl;

    a.insert(2, " sex ");
    cout << a << endl;
    cout << "size = " << a.size() << "capacity = " << a.capacity() << endl;
    a.resize(64, ']');
    cout << a << endl;
    a.clear();
    cout << a << endl;
    cout << a.empty() << endl;

    cout << a + " XXXX" << endl;
    cout << a[5] << endl;
}

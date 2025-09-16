#include <bits/stdc++.h>
using namespace std;

// this examples shows that even when we call move on a lvalue, the
// destructor of the old lvalue is still called, dangerous if the
// destructor calls delete or something similar

struct A {
    int len = 0;
    int *arr = nullptr;

    A() {}

    A(int n): len(n), arr(new int[n]) {}

    A(A&& a): len(a.len), arr(a.arr) {
        a.arr = nullptr;
    }

    void operator=(A&& a) {
        arr = a.arr;
        len = a.len;
        a.arr = nullptr;
    }

    ~A() {
        cout << "hello" << endl;
        delete[] arr;
    }
};

int main() {
    
    A a1;
    {
        a1 = A(10); // hello is printed twice 
    }


}
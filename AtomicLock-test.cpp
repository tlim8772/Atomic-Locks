#include <bits/stdc++.h>
using namespace std;

#include "AtomicLock.hpp"

void test1() {
    int test = 0;
    AtomicLock lock;
    //mutex mut;
    {
        jthread t1([&test, &lock]() {
            for (int i = 0; i < 1000000; i++) {
                LockGuard locker(lock);
                test++;
            }
        });

        jthread t2([&test, &lock]() {
            for (int i = 0; i < 1000000; i++) {
                LockGuard locker(lock);
                test++;
            }
        });
    }
    cout << test << endl;
}

void test2() {
    int test = 0;
    AtomicLock lock;
    {
        jthread t1([&test, &lock]() {
            for (int i = 0; i < 1000000; i++) {
                LockGuard locker(lock);
                test++;
            }
        });

        jthread t2([&test, &lock]() {
            for (int i = 0; i < 1000000; i++) {
                LockGuard locker(lock);
                LockGuard locker2(std::move(locker));
                test++;
            }
        });
    }
    cout << test << endl;

}
int main() {
    test1();
    test2();
}
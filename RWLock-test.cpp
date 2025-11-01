#include <bits/stdc++.h>
#include "RWLock.hpp"
using namespace std;

RWLock rwlock;
int cnt = 0;

void reader(int tid) {
    for (int i = 0; i < 1000000; i++) {
        rwlock.r_lock();
        int c = cnt;
        rwlock.r_unlock();
    }
   
}

void writer(int tid) {
    for (int i = 0; i < 1000000; i++) {
        rwlock.w_lock();
        cnt++;
        rwlock.w_unlock();
    }
}

int main() {
    vector<jthread> threads;
    threads.emplace_back(reader, 0);
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);
    threads.emplace_back(writer, 3);
    threads.emplace_back(writer, 4);
    for (jthread& t : threads) t.join();
    cout << cnt << endl;
}
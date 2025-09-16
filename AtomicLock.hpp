#include <bits/stdc++.h>
using namespace std;

struct AtomicLock {
    atomic<bool> l = false; // false means open, true means locked

    void lock() {
        bool e = l.load();
        
        start:
            while (e) e = l.load();
        
        while (!l.compare_exchange_strong(e, true)) {
            if (e) goto start;
        }
    }

    void unlock() {
        l.store(false);
    }
};

struct LockGuard {
    bool valid = true;
    AtomicLock& lock;

    LockGuard(AtomicLock& lock): lock(lock) {
        //cout << "locking" << endl;
        lock.lock();
    }

    LockGuard(LockGuard&& l): lock(l.lock) {
        l.valid = false;
    }

    ~LockGuard() {
        if (!valid) return;
        //cout << "unlocking" << endl;
        lock.unlock();
    }
};
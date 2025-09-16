#include <bits/stdc++.h>
using namespace std;

// Pattern
// 1. load the result
// 2. check if it satisfy requirements
// 3. compute new value
// 4. compare and exchane
// 5. if fail check the stored value, if does not satisy requirement goto 1

struct AtomicSem {
    atomic<int> cnt;

    AtomicSem(int n = 1): cnt(n) {}

    void acquire() {
        int e = cnt.load();
        
        start:
            while (e == 0) e = cnt.load();
        
        int d;
        while (1) {
            d = e - 1;
            bool res = cnt.compare_exchange_strong(e, d);
            if (res) break;
            if (e == 0) goto start;
        }
    }

    void release() {
        cnt.fetch_add(1);
    }
};

struct SemGuard {
    bool valid = true;
    AtomicSem& sem;

    SemGuard(AtomicSem& sem): sem(sem) {
        sem.acquire();
    }

    SemGuard(SemGuard&& guard): sem(guard.sem) {
        guard.valid = false;
    }

    ~SemGuard() {
        if (!valid) return;
        sem.release();
    }
};
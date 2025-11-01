#pragma once
#include <atomic>
#include <utility>
using namespace std;

struct Store {
    int first = 0, second = 0;

    bool operator==(const Store& s) {
        return first == s.first && second == s.second;
    }

    bool operator!=(const Store& s) {
        return first != s.first || second != s.second;
    }
};

struct RWLock {
    atomic<Store> vals = Store{0, 0};

    void r_lock() {
        Store v = vals.load();

        start:
        while (v.second != 0) v = vals.load();

        while (!vals.compare_exchange_strong(v, {v.first + 1, v.second})) {
            if (v.second != 0) goto start;
        }
    }

    void r_unlock() {
        Store v = vals.load();
        while (!vals.compare_exchange_strong(v, {v.first - 1, v.second}));
    }

    void w_lock() {
        Store v = vals.load();
        
        start:
        while (v != Store{0, 0}) v = vals.load();

        while (!vals.compare_exchange_strong(v, {v.first, v.second + 1})) {
            if (v != Store{0, 0}) goto start;
        }
    }

    void w_unlock() {
        vals.store({0, 0});
    }
};
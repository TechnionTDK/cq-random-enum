//
// Created by shai.zeevi on 06/08/2019.
//
//taken from: https://eli.thegreenplace.net/2008/08/23/initializing-an-array-in-constant-time
#ifndef TEMPLATEDRANDOMORDERENUMERATION_INITIALIZEDARRAY_H
#define TEMPLATEDRANDOMORDERENUMERATION_INITIALIZEDARRAY_H

#include <cstdio>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

struct InitializedArray {
public:

    explicit InitializedArray(ull len_, ll init_val_ = 0) {
        vec = new ll[len_];
        from = new ull[len_];
        to = new ull[len_];
        top = 0;
        init_val = init_val_;
        len = len_;
    }

    ll& operator[](size_t n) {
        if (from[n] < top && to[from[n]] == n) {
            return vec[n];
        } else {
            from[n] = top;
            to[top] = n;
            vec[n] = init_val;
            top++;

            return vec[n];
        }
    }

    ~InitializedArray() {
        delete[] vec;
        delete[] from;
        delete[] to;
    }


    void rebuild(ull new_len_, ll new_init_val_) {
        delete[] vec;
        delete[] from;
        delete[] to;
        vec = new ll[new_len_];
        from = new ull[new_len_];
        to = new ull[new_len_];
        top = 0;
        init_val = new_init_val_;
        len = new_len_;
    };



    ull len;

private:
    ll* vec;
    ull* from;
    ull* to;
    ull top;
    ll init_val;
};


#endif //TEMPLATEDRANDOMORDERENUMERATION_INITIALIZEDARRAY_H

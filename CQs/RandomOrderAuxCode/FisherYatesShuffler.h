//
// Created by shai.zeevi on 26/05/2019.
//

#ifndef RANDOMORDERENUMERATION_FISHERYATESSHUFFLER_H
#define RANDOMORDERENUMERATION_FISHERYATESSHUFFLER_H

#include <vector>
#include <unordered_map>
#include <chrono>
#include <random>
#include <algorithm>
#include "InitializedArray.h"

using namespace std;
using namespace chrono;

typedef long long ll;

//saves space (uses a map to record the "markings")
class FisherYatesShuffler {
public:
    explicit FisherYatesShuffler(ll n) : n(n), i(0), A(),
    generator(system_clock::now().time_since_epoch().count()) {}

    FisherYatesShuffler() : FisherYatesShuffler(0) {}

    //re-initialize everything
    void build(ll _n) {
        this->n = _n;
        this->i = 0;
        this->A.clear();
        this->generator = default_random_engine(system_clock::now().time_since_epoch().count());
    }

    inline ll next() {
        ll j = uniform_int_distribution<ll>(i, n-1)(generator);
        ll res = at(j);
        A[j] = at(i);
        //A[i] = res; //now i is not fresh anymore
        //i++;
        A.erase(i++);
        return res;
    }

    inline bool done() {
        return (i >= n);
    }


private:
    unordered_map<ll, ll> A;
    ll n;
    ll i; //current position
    default_random_engine generator;

    inline ll at(ll x) {
        auto it = A.find(x);

        if(it == A.end()) return x;
        else return it->second;
    }
};


//saves time (uses an O(1)-array to record the "markings")
class ArrayFisherYatesShuffler {

#define UNINIT -1

public:
    explicit ArrayFisherYatesShuffler(ll n) : n(n), i(0), array(n, UNINIT),
                                         generator(system_clock::now().time_since_epoch().count()) {}

    ArrayFisherYatesShuffler() : ArrayFisherYatesShuffler(0) {}

    //re-initialize everything
    void build(ll _n) {
        this->n = _n;
        this->i = 0;
        this->array.rebuild(_n, UNINIT);
        this->generator = default_random_engine(system_clock::now().time_since_epoch().count());
    }

    //TODO: stopping condition?
    inline ll next() {
        ll j = uniform_int_distribution<ll>(i, n-1)(generator);
        ll res = at(j);
        array[j] = at(i);
        array[i] = res; //kind of unnecessary
        i++;
        return res;
    }

private:
    InitializedArray array; //-1 if uninitialized, else the number itself
    ll n;
    ll i; //current position
    default_random_engine generator;

    inline ll at(ll x) {
        return (array[x] == UNINIT) ? x : array[x];
    }
};


#endif //RANDOMORDERENUMERATION_FISHERYATESSHUFFLER_H

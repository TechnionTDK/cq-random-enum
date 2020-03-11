//
// Created by shai.zeevi on 26/05/2019.
//

#ifndef RANDOMORDERENUMERATION_UCQFISHERYATESSHUFFLER_H
#define RANDOMORDERENUMERATION_UCQFISHERYATESSHUFFLER_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <random>
#include <algorithm>
#include <assert.h>

using namespace std;
using namespace chrono;

typedef long long ll;

class ComplexFisherYatesShuffler {
public:
    explicit ComplexFisherYatesShuffler(ll n) : n(n), i(0), A(), H(),// disqualified(),
    generator(system_clock::now().time_since_epoch().count()) {}

    ComplexFisherYatesShuffler() : ComplexFisherYatesShuffler(0) {}

    //re-initialize everything
    void build(ll n) {
        this->n = n;
        this->i = 0;
        this->A.clear();
        this->H.clear();
        //this->disqualified.clear();
        this->generator = default_random_engine(system_clock::now().time_since_epoch().count());
    }

    inline ll next() {
        ll j = uniform_int_distribution<ll>(i, n-1)(generator); //this is a location, not value

        ll value_of_i = at(i);
        ll value_of_j = at(j); //the result

        A[i] = value_of_j;
        A[j] = value_of_i;

        H[value_of_i] = j;
        H[value_of_j] = i;

        i++;

        return value_of_j;
    }

    inline void disqualify(ll j/*, int origin, int me*/) {

        //if(wasDisqualified(j)) throw runtime_error("cannot disqualify a disqualified answer");
        //assert(find(j) >= i || origin == me); // !disqualified

        if(i <= find(j)) {
            //swap A[i] (current spot) with A[H[j]] (answer no. j)
            ll loc_of_j = find(j);
            ll value_of_i = at(i);

            A[loc_of_j] = value_of_i;
            A[i] = j;

            H[j] = i;
            H[value_of_i] = loc_of_j;

            i++;
        }

        //disqualified.insert(j);
        //assert(find(j) < i); // disqualified
    }

    inline bool wasDisqualified(ll j) {
        return find(j) < i;
        //return disqualified.find(j) != disqualified.end();
    }

    inline bool wasNotDisqualified(ll j) {
        return !wasDisqualified(j);
    }



//    string padded(ll j) {
//        if(j < 10) return " " + to_string(j);
//        else return to_string(j);
//    }

//    void printStatus() {
//        cout << "      ";
//        for(ll k = 0; k < n; k++) {
//            cout << padded(k) << " | ";
//        }
//        cout << endl;
//
//        cout << "  at: ";
//        for(ll k = 0; k < n; k++) {
//            cout << padded(at(k)) << " | ";
//        }
//        cout << endl;
//        cout << "find: ";
//        for(ll k = 0; k < n; k++) {
//            cout << padded(find(k)) << " | ";
//        }
//        cout << endl;
//    }

//    void checkStatus() {
//        for(int j = 0; j < n; j++) {
//            assert(at(find(j)) == j);
//        }
//    }


private:
    unordered_map<ll, ll> A;
    unordered_map<ll, ll> H;
    //unordered_set<ll> disqualified;
    ll n;
    ll i; //current position
    default_random_engine generator;

    inline ll at(ll x) {
        auto it = A.find(x);

        if(it == A.end()) return x;
        else return it->second;
    }

    inline ll find(ll x) {
        auto it = H.find(x);

        if(it == H.end()) return x;
        else return it->second;
    }
};

#endif //RANDOMORDERENUMERATION_UCQFISHERYATESSHUFFLER_H

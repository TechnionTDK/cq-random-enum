#ifndef RANDOMORDERENUMERATION_Q2_PS__R_PARCEL_H
#define RANDOMORDERENUMERATION_Q2_PS__R_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION_Q2_PS
#endif

using namespace std;


struct Q2_PS__R_Key {
    //data
    int regionKey;
    //end-data
    
    void print() const {
        cout << "{" << regionKey << "}";
    }
};


struct Q2_PS__R_Parcel {
    //data
    int regionKey;
    //end-data
    
    //construction
    static Q2_PS__R_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int regionKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {regionKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << regionKey << "}";
    }
};

//conversion to parent key
template<> Q2_PS__R_Key Q2_PS__R_Parcel::to<Q2_PS__R_Key>() const {
    return {regionKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2_PS__R_Key> {
        size_t operator()(const Q2_PS__R_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q2_PS__R_Parcel> {
        size_t operator()(const Q2_PS__R_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2_PS__R_Key> {
        bool operator()(const Q2_PS__R_Key& lhs, const Q2_PS__R_Key& rhs) const {
            return lhs.regionKey == rhs.regionKey;
        }
    };
    
    template<>
    struct equal_to<Q2_PS__R_Parcel> {
        bool operator()(const Q2_PS__R_Parcel& lhs, const Q2_PS__R_Parcel& rhs) const {
            return lhs.regionKey == rhs.regionKey;
        }
    };
}

typedef Table<Q2_PS__R_Parcel> Q2_PS__R_Table;
typedef SplitTable<Q2_PS__R_Key, Q2_PS__R_Parcel> Q2_PS__R_SplitTable;

#endif //RANDOMORDERENUMERATION_Q2_PS__R_PARCEL_H
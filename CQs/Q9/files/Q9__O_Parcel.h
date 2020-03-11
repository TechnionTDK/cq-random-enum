#ifndef RANDOMORDERENUMERATION_Q9__O_PARCEL_H
#define RANDOMORDERENUMERATION_Q9__O_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct Q9__O_Key {
    //data
    int orderKey;
    //end-data
    
    void print() const {
        cout << "{" << orderKey << "}";
    }
};


struct Q9__O_Parcel {
    //data
    int orderKey;
    //end-data
    
    //construction
    static Q9__O_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int orderKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {orderKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey << "}";
    }
};

//conversion to parent key
template<> Q9__O_Key Q9__O_Parcel::to<Q9__O_Key>() const {
    return {orderKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q9__O_Key> {
        size_t operator()(const Q9__O_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q9__O_Parcel> {
        size_t operator()(const Q9__O_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q9__O_Key> {
        bool operator()(const Q9__O_Key& lhs, const Q9__O_Key& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
    
    template<>
    struct equal_to<Q9__O_Parcel> {
        bool operator()(const Q9__O_Parcel& lhs, const Q9__O_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
}

typedef Table<Q9__O_Parcel> Q9__O_Table;
typedef SplitTable<Q9__O_Key, Q9__O_Parcel> Q9__O_SplitTable;

#endif //RANDOMORDERENUMERATION_Q9__O_PARCEL_H
#ifndef RANDOMORDERENUMERATION_Q3__C_PARCEL_H
#define RANDOMORDERENUMERATION_Q3__C_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct Q3__C_Key {
    //data
    int custKey;
    //end-data
    
    void print() const {
        cout << "{" << custKey << "}";
    }
};


struct Q3__C_Parcel {
    //data
    int custKey;
    //end-data
    
    //construction
    static Q3__C_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int custKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {custKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << custKey << "}";
    }
};

//conversion to parent key
template<> Q3__C_Key Q3__C_Parcel::to<Q3__C_Key>() const {
    return {custKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q3__C_Key> {
        size_t operator()(const Q3__C_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q3__C_Parcel> {
        size_t operator()(const Q3__C_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q3__C_Key> {
        bool operator()(const Q3__C_Key& lhs, const Q3__C_Key& rhs) const {
            return lhs.custKey == rhs.custKey;
        }
    };
    
    template<>
    struct equal_to<Q3__C_Parcel> {
        bool operator()(const Q3__C_Parcel& lhs, const Q3__C_Parcel& rhs) const {
            return lhs.custKey == rhs.custKey;
        }
    };
}

typedef Table<Q3__C_Parcel> Q3__C_Table;
typedef SplitTable<Q3__C_Key, Q3__C_Parcel> Q3__C_SplitTable;

#endif //RANDOMORDERENUMERATION_Q3__C_PARCEL_H
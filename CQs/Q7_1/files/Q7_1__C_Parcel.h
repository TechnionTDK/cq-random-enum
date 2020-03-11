#ifndef RANDOMORDERENUMERATION_Q7_1__C_PARCEL_H
#define RANDOMORDERENUMERATION_Q7_1__C_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q7_1__N2_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q7_1__C_Key {
    //data
    int custKey;
    //end-data
    
    void print() const {
        cout << "{" << custKey << "}";
    }
};


struct Q7_1__C_Parcel {
    //data
    int custKey;

    int nationKey2;
    //end-data
    
    //construction
    static Q7_1__C_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int custKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 2; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int nationKey2 = stoi(line.substr(0, pos));

        return {custKey, nationKey2};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << custKey;
        cout << ", " << nationKey2 << "}";
    }
};

//conversion to parent key
template<> Q7_1__C_Key Q7_1__C_Parcel::to<Q7_1__C_Key>() const {
    return {custKey};
}

//conversion to childKeys
template<> Q7_1__N2_Key Q7_1__C_Parcel::to<Q7_1__N2_Key>() const {
    return {nationKey2};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_1__C_Key> {
        size_t operator()(const Q7_1__C_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7_1__C_Parcel> {
        size_t operator()(const Q7_1__C_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.nationKey2);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_1__C_Key> {
        bool operator()(const Q7_1__C_Key& lhs, const Q7_1__C_Key& rhs) const {
            return lhs.custKey == rhs.custKey;
        }
    };
    
    template<>
    struct equal_to<Q7_1__C_Parcel> {
        bool operator()(const Q7_1__C_Parcel& lhs, const Q7_1__C_Parcel& rhs) const {
            return lhs.custKey == rhs.custKey && lhs.nationKey2 == rhs.nationKey2;
        }
    };
}

typedef Table<Q7_1__C_Parcel> Q7_1__C_Table;
typedef SplitTable<Q7_1__C_Key, Q7_1__C_Parcel> Q7_1__C_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7_1__C_PARCEL_H
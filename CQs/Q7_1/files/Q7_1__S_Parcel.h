#ifndef RANDOMORDERENUMERATION_Q7_1__S_PARCEL_H
#define RANDOMORDERENUMERATION_Q7_1__S_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q7_1__N1_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q7_1__S_Key {
    //data
    int suppKey;
    //end-data
    
    void print() const {
        cout << "{" << suppKey << "}";
    }
};


struct Q7_1__S_Parcel {
    //data
    int suppKey;

    int nationKey1;
    //end-data
    
    //construction
    static Q7_1__S_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 2; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int nationKey1 = stoi(line.substr(0, pos));

        return {suppKey, nationKey1};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << suppKey;
        cout << ", " << nationKey1 << "}";
    }
};

//conversion to parent key
template<> Q7_1__S_Key Q7_1__S_Parcel::to<Q7_1__S_Key>() const {
    return {suppKey};
}

//conversion to childKeys
template<> Q7_1__N1_Key Q7_1__S_Parcel::to<Q7_1__N1_Key>() const {
    return {nationKey1};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_1__S_Key> {
        size_t operator()(const Q7_1__S_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7_1__S_Parcel> {
        size_t operator()(const Q7_1__S_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey1);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_1__S_Key> {
        bool operator()(const Q7_1__S_Key& lhs, const Q7_1__S_Key& rhs) const {
            return lhs.suppKey == rhs.suppKey;
        }
    };
    
    template<>
    struct equal_to<Q7_1__S_Parcel> {
        bool operator()(const Q7_1__S_Parcel& lhs, const Q7_1__S_Parcel& rhs) const {
            return lhs.suppKey == rhs.suppKey && lhs.nationKey1 == rhs.nationKey1;
        }
    };
}

typedef Table<Q7_1__S_Parcel> Q7_1__S_Table;
typedef SplitTable<Q7_1__S_Key, Q7_1__S_Parcel> Q7_1__S_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7_1__S_PARCEL_H
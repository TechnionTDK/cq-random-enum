#ifndef RANDOMORDERENUMERATION_Q0__S_PARCEL_H
#define RANDOMORDERENUMERATION_Q0__S_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q0__N_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q0__S_Key {
    //data
    int suppKey;
    //end-data
    
    void print() const {
        cout << "{" << suppKey << "}";
    }
};


struct Q0__S_Parcel {
    //data
    int suppKey;

    int nationKey;
    //end-data
    
    //construction
    static Q0__S_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 2; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));

        return {suppKey, nationKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << suppKey;
        cout << ", " << nationKey << "}";
    }
};

//conversion to parent key
template<> Q0__S_Key Q0__S_Parcel::to<Q0__S_Key>() const {
    return {suppKey};
}

//conversion to childKeys
template<> Q0__N_Key Q0__S_Parcel::to<Q0__N_Key>() const {
    return {nationKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q0__S_Key> {
        size_t operator()(const Q0__S_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q0__S_Parcel> {
        size_t operator()(const Q0__S_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q0__S_Key> {
        bool operator()(const Q0__S_Key& lhs, const Q0__S_Key& rhs) const {
            return lhs.suppKey == rhs.suppKey;
        }
    };
    
    template<>
    struct equal_to<Q0__S_Parcel> {
        bool operator()(const Q0__S_Parcel& lhs, const Q0__S_Parcel& rhs) const {
            return lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey;
        }
    };
}

typedef Table<Q0__S_Parcel> Q0__S_Table;
typedef SplitTable<Q0__S_Key, Q0__S_Parcel> Q0__S_SplitTable;

#endif //RANDOMORDERENUMERATION_Q0__S_PARCEL_H
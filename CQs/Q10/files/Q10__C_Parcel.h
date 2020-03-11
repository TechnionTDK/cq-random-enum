#ifndef RANDOMORDERENUMERATION_Q10__C_PARCEL_H
#define RANDOMORDERENUMERATION_Q10__C_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q10__N_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q10__C_Key {
    //data
    int custKey;
    //end-data
    
    void print() const {
        cout << "{" << custKey << "}";
    }
};


struct Q10__C_Parcel {
    //data
    int custKey;

    int nationKey;
    //end-data
    
    //construction
    static Q10__C_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int custKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 2; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));

        return {custKey, nationKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << custKey;
        cout << ", " << nationKey << "}";
    }
};

//conversion to parent key
template<> Q10__C_Key Q10__C_Parcel::to<Q10__C_Key>() const {
    return {custKey};
}

//conversion to childKeys
template<> Q10__N_Key Q10__C_Parcel::to<Q10__N_Key>() const {
    return {nationKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q10__C_Key> {
        size_t operator()(const Q10__C_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q10__C_Parcel> {
        size_t operator()(const Q10__C_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q10__C_Key> {
        bool operator()(const Q10__C_Key& lhs, const Q10__C_Key& rhs) const {
            return lhs.custKey == rhs.custKey;
        }
    };
    
    template<>
    struct equal_to<Q10__C_Parcel> {
        bool operator()(const Q10__C_Parcel& lhs, const Q10__C_Parcel& rhs) const {
            return lhs.custKey == rhs.custKey && lhs.nationKey == rhs.nationKey;
        }
    };
}

typedef Table<Q10__C_Parcel> Q10__C_Table;
typedef SplitTable<Q10__C_Key, Q10__C_Parcel> Q10__C_SplitTable;

#endif //RANDOMORDERENUMERATION_Q10__C_PARCEL_H
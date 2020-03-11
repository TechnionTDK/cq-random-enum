#ifndef RANDOMORDERENUMERATION_Q10__O_PARCEL_H
#define RANDOMORDERENUMERATION_Q10__O_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q10__C_Parcel.h"
#include "Q10__L_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q10__O_Key {
    //data
    
    //end-data
    
    void print() const {
        cout << "{" << "}";
    }
};


struct Q10__O_Parcel {
    //data
    int orderKey;

    int custKey;
    //end-data
    
    //construction
    static Q10__O_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int orderKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        int custKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {orderKey, custKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << custKey << "}";
    }
};

//conversion to parent key
template<> Q10__O_Key Q10__O_Parcel::to<Q10__O_Key>() const {
    return {};
}

//conversion to childKeys
template<> Q10__C_Key Q10__O_Parcel::to<Q10__C_Key>() const {
    return {custKey};
}

template<> Q10__L_Key Q10__O_Parcel::to<Q10__L_Key>() const {
    return {orderKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q10__O_Key> {
        size_t operator()(const Q10__O_Key& p) const {
            size_t seed = 0;
            
            return seed;
        }
    };
    
    template<>
    struct hash<Q10__O_Parcel> {
        size_t operator()(const Q10__O_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q10__O_Key> {
        bool operator()(const Q10__O_Key& lhs, const Q10__O_Key& rhs) const {
            return true;
        }
    };
    
    template<>
    struct equal_to<Q10__O_Parcel> {
        bool operator()(const Q10__O_Parcel& lhs, const Q10__O_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey;
        }
    };
}

typedef Table<Q10__O_Parcel> Q10__O_Table;
typedef SplitTable<Q10__O_Key, Q10__O_Parcel> Q10__O_SplitTable;

#endif //RANDOMORDERENUMERATION_Q10__O_PARCEL_H
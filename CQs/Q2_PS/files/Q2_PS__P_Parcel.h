#ifndef RANDOMORDERENUMERATION_Q2_PS__P_PARCEL_H
#define RANDOMORDERENUMERATION_Q2_PS__P_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION_Q2_PS
#endif

using namespace std;


struct Q2_PS__P_Key {
    //data
    int partKey;
    //end-data
    
    void print() const {
        cout << "{" << partKey << "}";
    }
};


struct Q2_PS__P_Parcel {
    //data
    int partKey;
    //end-data
    
    //construction
    static Q2_PS__P_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int partKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {partKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << partKey << "}";
    }
};

//conversion to parent key
template<> Q2_PS__P_Key Q2_PS__P_Parcel::to<Q2_PS__P_Key>() const {
    return {partKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2_PS__P_Key> {
        size_t operator()(const Q2_PS__P_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q2_PS__P_Parcel> {
        size_t operator()(const Q2_PS__P_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2_PS__P_Key> {
        bool operator()(const Q2_PS__P_Key& lhs, const Q2_PS__P_Key& rhs) const {
            return lhs.partKey == rhs.partKey;
        }
    };
    
    template<>
    struct equal_to<Q2_PS__P_Parcel> {
        bool operator()(const Q2_PS__P_Parcel& lhs, const Q2_PS__P_Parcel& rhs) const {
            return lhs.partKey == rhs.partKey;
        }
    };
}

typedef Table<Q2_PS__P_Parcel> Q2_PS__P_Table;
typedef SplitTable<Q2_PS__P_Key, Q2_PS__P_Parcel> Q2_PS__P_SplitTable;

#endif //RANDOMORDERENUMERATION_Q2_PS__P_PARCEL_H
#ifndef RANDOMORDERENUMERATION_Q2__PS_PARCEL_H
#define RANDOMORDERENUMERATION_Q2__PS_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q2__S_Parcel.h"
#include "Q2__P_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q2__PS_Key {
    //data
    
    //end-data
    
    void print() const {
        cout << "{" << "}";
    }
};


struct Q2__PS_Parcel {
    //data
    int partKey;

    int suppKey;
    //end-data
    
    //construction
    static Q2__PS_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int partKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {partKey, suppKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << partKey;
        cout << ", " << suppKey << "}";
    }
};

//conversion to parent key
template<> Q2__PS_Key Q2__PS_Parcel::to<Q2__PS_Key>() const {
    return {};
}

//conversion to childKeys
template<> Q2__S_Key Q2__PS_Parcel::to<Q2__S_Key>() const {
    return {suppKey};
}

template<> Q2__P_Key Q2__PS_Parcel::to<Q2__P_Key>() const {
    return {partKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2__PS_Key> {
        size_t operator()(const Q2__PS_Key& p) const {
            size_t seed = 0;
            
            return seed;
        }
    };
    
    template<>
    struct hash<Q2__PS_Parcel> {
        size_t operator()(const Q2__PS_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2__PS_Key> {
        bool operator()(const Q2__PS_Key& lhs, const Q2__PS_Key& rhs) const {
            return true;
        }
    };
    
    template<>
    struct equal_to<Q2__PS_Parcel> {
        bool operator()(const Q2__PS_Parcel& lhs, const Q2__PS_Parcel& rhs) const {
            return lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey;
        }
    };
}

typedef Table<Q2__PS_Parcel> Q2__PS_Table;
typedef SplitTable<Q2__PS_Key, Q2__PS_Parcel> Q2__PS_SplitTable;

#endif //RANDOMORDERENUMERATION_Q2__PS_PARCEL_H
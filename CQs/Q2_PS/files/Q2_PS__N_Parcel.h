#ifndef RANDOMORDERENUMERATION_Q2_PS__N_PARCEL_H
#define RANDOMORDERENUMERATION_Q2_PS__N_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q2_PS__R_Parcel.h"
#ifdef PROJECTION_Q2_PS
#endif

using namespace std;


struct Q2_PS__N_Key {
    //data
    int nationKey;
    //end-data
    
    void print() const {
        cout << "{" << nationKey << "}";
    }
};


struct Q2_PS__N_Parcel {
    //data
    int nationKey;

    int regionKey;
    //end-data
    
    //construction
    static Q2_PS__N_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 1; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int regionKey = stoi(line.substr(0, pos));

        return {nationKey, regionKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey;
        cout << ", " << regionKey << "}";
    }
};

//conversion to parent key
template<> Q2_PS__N_Key Q2_PS__N_Parcel::to<Q2_PS__N_Key>() const {
    return {nationKey};
}

//conversion to childKeys
template<> Q2_PS__R_Key Q2_PS__N_Parcel::to<Q2_PS__R_Key>() const {
    return {regionKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q2_PS__N_Key> {
        size_t operator()(const Q2_PS__N_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q2_PS__N_Parcel> {
        size_t operator()(const Q2_PS__N_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q2_PS__N_Key> {
        bool operator()(const Q2_PS__N_Key& lhs, const Q2_PS__N_Key& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
    
    template<>
    struct equal_to<Q2_PS__N_Parcel> {
        bool operator()(const Q2_PS__N_Parcel& lhs, const Q2_PS__N_Parcel& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

typedef Table<Q2_PS__N_Parcel> Q2_PS__N_Table;
typedef SplitTable<Q2_PS__N_Key, Q2_PS__N_Parcel> Q2_PS__N_SplitTable;

#endif //RANDOMORDERENUMERATION_Q2_PS__N_PARCEL_H
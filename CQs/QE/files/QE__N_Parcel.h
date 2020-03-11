#ifndef RANDOMORDERENUMERATION_QE__N_PARCEL_H
#define RANDOMORDERENUMERATION_QE__N_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QE__R_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct QE__N_Key {
    //data
    int nationKey;
    //end-data
    
    void print() const {
        cout << "{" << nationKey << "}";
    }
};


struct QE__N_Parcel {
    //data
    int nationKey;

    int regionKey;
    //end-data
    
    //construction
    static QE__N_Parcel from(string line) {
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
template<> QE__N_Key QE__N_Parcel::to<QE__N_Key>() const {
    return {nationKey};
}

//conversion to childKeys
template<> QE__R_Key QE__N_Parcel::to<QE__R_Key>() const {
    return {regionKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QE__N_Key> {
        size_t operator()(const QE__N_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QE__N_Parcel> {
        size_t operator()(const QE__N_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QE__N_Key> {
        bool operator()(const QE__N_Key& lhs, const QE__N_Key& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
    
    template<>
    struct equal_to<QE__N_Parcel> {
        bool operator()(const QE__N_Parcel& lhs, const QE__N_Parcel& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

typedef Table<QE__N_Parcel> QE__N_Table;
typedef SplitTable<QE__N_Key, QE__N_Parcel> QE__N_SplitTable;

#endif //RANDOMORDERENUMERATION_QE__N_PARCEL_H
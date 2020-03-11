#ifndef RANDOMORDERENUMERATION_QAE__N_PARCEL_H
#define RANDOMORDERENUMERATION_QAE__N_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QAE__R_Parcel.h"
#ifdef PROJECTION_QAE
#endif

using namespace std;


struct QAE__N_Key {
    //data
    int nationKey;
    //end-data
    
    void print() const {
        cout << "{" << nationKey << "}";
    }
};


struct QAE__N_Parcel {
    //data
    int nationKey;

    int regionKey;
    //end-data
    
    //construction
    static QAE__N_Parcel from(string line) {
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
template<> QAE__N_Key QAE__N_Parcel::to<QAE__N_Key>() const {
    return {nationKey};
}

//conversion to childKeys
template<> QAE__R_Key QAE__N_Parcel::to<QAE__R_Key>() const {
    return {regionKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QAE__N_Key> {
        size_t operator()(const QAE__N_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QAE__N_Parcel> {
        size_t operator()(const QAE__N_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QAE__N_Key> {
        bool operator()(const QAE__N_Key& lhs, const QAE__N_Key& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
    
    template<>
    struct equal_to<QAE__N_Parcel> {
        bool operator()(const QAE__N_Parcel& lhs, const QAE__N_Parcel& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

typedef Table<QAE__N_Parcel> QAE__N_Table;
typedef SplitTable<QAE__N_Key, QAE__N_Parcel> QAE__N_SplitTable;

#endif //RANDOMORDERENUMERATION_QAE__N_PARCEL_H
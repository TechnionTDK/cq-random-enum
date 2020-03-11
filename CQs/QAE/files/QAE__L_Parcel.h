#ifndef RANDOMORDERENUMERATION_QAE__L_PARCEL_H
#define RANDOMORDERENUMERATION_QAE__L_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QAE__S_Parcel.h"
#ifdef PROJECTION_QAE
#endif

using namespace std;


struct QAE__L_Key {
    //data
    int orderKey;
    //end-data
    
    void print() const {
        cout << "{" << orderKey << "}";
    }
};


struct QAE__L_Parcel {
    //data
    int orderKey;

    int suppKey;
    //end-data
    
    //construction
    static QAE__L_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int orderKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 1; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));

        return {orderKey, suppKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << suppKey << "}";
    }
};

//conversion to parent key
template<> QAE__L_Key QAE__L_Parcel::to<QAE__L_Key>() const {
    return {orderKey};
}

//conversion to childKeys
template<> QAE__S_Key QAE__L_Parcel::to<QAE__S_Key>() const {
    return {suppKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QAE__L_Key> {
        size_t operator()(const QAE__L_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QAE__L_Parcel> {
        size_t operator()(const QAE__L_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QAE__L_Key> {
        bool operator()(const QAE__L_Key& lhs, const QAE__L_Key& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
    
    template<>
    struct equal_to<QAE__L_Parcel> {
        bool operator()(const QAE__L_Parcel& lhs, const QAE__L_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey;
        }
    };
}

typedef Table<QAE__L_Parcel> QAE__L_Table;
typedef SplitTable<QAE__L_Key, QAE__L_Parcel> QAE__L_SplitTable;

#endif //RANDOMORDERENUMERATION_QAE__L_PARCEL_H
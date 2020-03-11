#ifndef RANDOMORDERENUMERATION_QAE__O_PARCEL_H
#define RANDOMORDERENUMERATION_QAE__O_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QAE__L_Parcel.h"
#ifdef PROJECTION_QAE
#endif

using namespace std;


struct QAE__O_Key {
    //data
    
    //end-data
    
    void print() const {
        cout << "{" << "}";
    }
};


struct QAE__O_Parcel {
    //data
    int orderKey;
    //end-data
    
    //construction
    static QAE__O_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int orderKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {orderKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey << "}";
    }
};

//conversion to parent key
template<> QAE__O_Key QAE__O_Parcel::to<QAE__O_Key>() const {
    return {};
}

//conversion to childKeys
template<> QAE__L_Key QAE__O_Parcel::to<QAE__L_Key>() const {
    return {orderKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QAE__O_Key> {
        size_t operator()(const QAE__O_Key& p) const {
            size_t seed = 0;
            
            return seed;
        }
    };
    
    template<>
    struct hash<QAE__O_Parcel> {
        size_t operator()(const QAE__O_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QAE__O_Key> {
        bool operator()(const QAE__O_Key& lhs, const QAE__O_Key& rhs) const {
            return true;
        }
    };
    
    template<>
    struct equal_to<QAE__O_Parcel> {
        bool operator()(const QAE__O_Parcel& lhs, const QAE__O_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
}

typedef Table<QAE__O_Parcel> QAE__O_Table;
typedef SplitTable<QAE__O_Key, QAE__O_Parcel> QAE__O_SplitTable;

#endif //RANDOMORDERENUMERATION_QAE__O_PARCEL_H
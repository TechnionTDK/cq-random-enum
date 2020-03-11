#ifndef RANDOMORDERENUMERATION_QA__L_PARCEL_H
#define RANDOMORDERENUMERATION_QA__L_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QA__S_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct QA__L_Key {
    //data
    int orderKey;
    //end-data
    
    void print() const {
        cout << "{" << orderKey << "}";
    }
};


struct QA__L_Parcel {
    //data
    int orderKey;

    int suppKey;
    //end-data
    
    //construction
    static QA__L_Parcel from(string line) {
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
template<> QA__L_Key QA__L_Parcel::to<QA__L_Key>() const {
    return {orderKey};
}

//conversion to childKeys
template<> QA__S_Key QA__L_Parcel::to<QA__S_Key>() const {
    return {suppKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QA__L_Key> {
        size_t operator()(const QA__L_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QA__L_Parcel> {
        size_t operator()(const QA__L_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QA__L_Key> {
        bool operator()(const QA__L_Key& lhs, const QA__L_Key& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
    
    template<>
    struct equal_to<QA__L_Parcel> {
        bool operator()(const QA__L_Parcel& lhs, const QA__L_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey;
        }
    };
}

typedef Table<QA__L_Parcel> QA__L_Table;
typedef SplitTable<QA__L_Key, QA__L_Parcel> QA__L_SplitTable;

#endif //RANDOMORDERENUMERATION_QA__L_PARCEL_H
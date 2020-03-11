#ifndef RANDOMORDERENUMERATION_QA__O_PARCEL_H
#define RANDOMORDERENUMERATION_QA__O_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QA__L_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct QA__O_Key {
    //data
    
    //end-data
    
    void print() const {
        cout << "{" << "}";
    }
};


struct QA__O_Parcel {
    //data
    int orderKey;
    //end-data
    
    //construction
    static QA__O_Parcel from(string line) {
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
template<> QA__O_Key QA__O_Parcel::to<QA__O_Key>() const {
    return {};
}

//conversion to childKeys
template<> QA__L_Key QA__O_Parcel::to<QA__L_Key>() const {
    return {orderKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QA__O_Key> {
        size_t operator()(const QA__O_Key& p) const {
            size_t seed = 0;
            
            return seed;
        }
    };
    
    template<>
    struct hash<QA__O_Parcel> {
        size_t operator()(const QA__O_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QA__O_Key> {
        bool operator()(const QA__O_Key& lhs, const QA__O_Key& rhs) const {
            return true;
        }
    };
    
    template<>
    struct equal_to<QA__O_Parcel> {
        bool operator()(const QA__O_Parcel& lhs, const QA__O_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
}

typedef Table<QA__O_Parcel> QA__O_Table;
typedef SplitTable<QA__O_Key, QA__O_Parcel> QA__O_SplitTable;

#endif //RANDOMORDERENUMERATION_QA__O_PARCEL_H
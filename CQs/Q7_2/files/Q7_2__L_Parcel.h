#ifndef RANDOMORDERENUMERATION_Q7_2__L_PARCEL_H
#define RANDOMORDERENUMERATION_Q7_2__L_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q7_2__S_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q7_2__L_Key {
    //data
    int orderKey;
    //end-data
    
    void print() const {
        cout << "{" << orderKey << "}";
    }
};


struct Q7_2__L_Parcel {
    //data
    int orderKey;

    int partKey;

    int suppKey;

    int lnumber;
    //end-data
    
    //construction
    static Q7_2__L_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int orderKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        int partKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        int lnumber = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {orderKey, partKey, suppKey, lnumber};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << partKey;
        cout << ", " << suppKey;
        cout << ", " << lnumber << "}";
    }
};

//conversion to parent key
template<> Q7_2__L_Key Q7_2__L_Parcel::to<Q7_2__L_Key>() const {
    return {orderKey};
}

//conversion to childKeys
template<> Q7_2__S_Key Q7_2__L_Parcel::to<Q7_2__S_Key>() const {
    return {suppKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_2__L_Key> {
        size_t operator()(const Q7_2__L_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7_2__L_Parcel> {
        size_t operator()(const Q7_2__L_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_2__L_Key> {
        bool operator()(const Q7_2__L_Key& lhs, const Q7_2__L_Key& rhs) const {
            return lhs.orderKey == rhs.orderKey;
        }
    };
    
    template<>
    struct equal_to<Q7_2__L_Parcel> {
        bool operator()(const Q7_2__L_Parcel& lhs, const Q7_2__L_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber;
        }
    };
}

typedef Table<Q7_2__L_Parcel> Q7_2__L_Table;
typedef SplitTable<Q7_2__L_Key, Q7_2__L_Parcel> Q7_2__L_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7_2__L_PARCEL_H
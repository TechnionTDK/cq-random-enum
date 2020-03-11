#ifndef RANDOMORDERENUMERATION_Q9__L_PARCEL_H
#define RANDOMORDERENUMERATION_Q9__L_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "Q9__S_Parcel.h"
#include "Q9__O_Parcel.h"
#include "Q9__PS_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct Q9__L_Key {
    //data
    
    //end-data
    
    void print() const {
        cout << "{" << "}";
    }
};


struct Q9__L_Parcel {
    //data
    int orderKey;

    int partKey;

    int suppKey;

    int lnumber;
    //end-data
    
    //construction
    static Q9__L_Parcel from(string line) {
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
template<> Q9__L_Key Q9__L_Parcel::to<Q9__L_Key>() const {
    return {};
}

//conversion to childKeys
template<> Q9__S_Key Q9__L_Parcel::to<Q9__S_Key>() const {
    return {suppKey};
}

template<> Q9__O_Key Q9__L_Parcel::to<Q9__O_Key>() const {
    return {orderKey};
}

template<> Q9__PS_Key Q9__L_Parcel::to<Q9__PS_Key>() const {
    return {partKey, suppKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q9__L_Key> {
        size_t operator()(const Q9__L_Key& p) const {
            size_t seed = 0;
            
            return seed;
        }
    };
    
    template<>
    struct hash<Q9__L_Parcel> {
        size_t operator()(const Q9__L_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            return seed;
        }
    };

    template<>
    struct equal_to<Q9__L_Key> {
        bool operator()(const Q9__L_Key& lhs, const Q9__L_Key& rhs) const {
            return true;
        }
    };
    
    template<>
    struct equal_to<Q9__L_Parcel> {
        bool operator()(const Q9__L_Parcel& lhs, const Q9__L_Parcel& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber;
        }
    };
}

typedef Table<Q9__L_Parcel> Q9__L_Table;
typedef SplitTable<Q9__L_Key, Q9__L_Parcel> Q9__L_SplitTable;

#endif //RANDOMORDERENUMERATION_Q9__L_PARCEL_H
#ifndef RANDOMORDERENUMERATION_QE__R_PARCEL_H
#define RANDOMORDERENUMERATION_QE__R_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct QE__R_Key {
    //data
    int regionKey;
    //end-data
    
    void print() const {
        cout << "{" << regionKey << "}";
    }
};


struct QE__R_Parcel {
    //data
    int regionKey;

    string rname;
    //end-data
    
    //construction
    static QE__R_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int regionKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        string rname = (line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {regionKey, rname};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << regionKey;
        cout << ", " << rname << "}";
    }
};

//conversion to parent key
template<> QE__R_Key QE__R_Parcel::to<QE__R_Key>() const {
    return {regionKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<QE__R_Key> {
        size_t operator()(const QE__R_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QE__R_Parcel> {
        size_t operator()(const QE__R_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.regionKey);
            boost::hash_combine(seed, p.rname);
            return seed;
        }
    };

    template<>
    struct equal_to<QE__R_Key> {
        bool operator()(const QE__R_Key& lhs, const QE__R_Key& rhs) const {
            return lhs.regionKey == rhs.regionKey;
        }
    };
    
    template<>
    struct equal_to<QE__R_Parcel> {
        bool operator()(const QE__R_Parcel& lhs, const QE__R_Parcel& rhs) const {
            return lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

typedef Table<QE__R_Parcel> QE__R_Table;
typedef SplitTable<QE__R_Key, QE__R_Parcel> QE__R_SplitTable;

#endif //RANDOMORDERENUMERATION_QE__R_PARCEL_H
#ifndef RANDOMORDERENUMERATION_Q7__N1_PARCEL_H
#define RANDOMORDERENUMERATION_Q7__N1_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct Q7__N1_Key {
    //data
    int nationKey1;
    //end-data
    
    void print() const {
        cout << "{" << nationKey1 << "}";
    }
};


struct Q7__N1_Parcel {
    //data
    int nationKey1;
    //end-data
    
    //construction
    static Q7__N1_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey1 = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {nationKey1};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey1 << "}";
    }
};

//conversion to parent key
template<> Q7__N1_Key Q7__N1_Parcel::to<Q7__N1_Key>() const {
    return {nationKey1};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7__N1_Key> {
        size_t operator()(const Q7__N1_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey1);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7__N1_Parcel> {
        size_t operator()(const Q7__N1_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey1);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7__N1_Key> {
        bool operator()(const Q7__N1_Key& lhs, const Q7__N1_Key& rhs) const {
            return lhs.nationKey1 == rhs.nationKey1;
        }
    };
    
    template<>
    struct equal_to<Q7__N1_Parcel> {
        bool operator()(const Q7__N1_Parcel& lhs, const Q7__N1_Parcel& rhs) const {
            return lhs.nationKey1 == rhs.nationKey1;
        }
    };
}

typedef Table<Q7__N1_Parcel> Q7__N1_Table;
typedef SplitTable<Q7__N1_Key, Q7__N1_Parcel> Q7__N1_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7__N1_PARCEL_H
#ifndef RANDOMORDERENUMERATION_Q7__N2_PARCEL_H
#define RANDOMORDERENUMERATION_Q7__N2_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct Q7__N2_Key {
    //data
    int nationKey2;
    //end-data
    
    void print() const {
        cout << "{" << nationKey2 << "}";
    }
};


struct Q7__N2_Parcel {
    //data
    int nationKey2;
    //end-data
    
    //construction
    static Q7__N2_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey2 = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {nationKey2};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey2 << "}";
    }
};

//conversion to parent key
template<> Q7__N2_Key Q7__N2_Parcel::to<Q7__N2_Key>() const {
    return {nationKey2};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7__N2_Key> {
        size_t operator()(const Q7__N2_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey2);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7__N2_Parcel> {
        size_t operator()(const Q7__N2_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey2);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7__N2_Key> {
        bool operator()(const Q7__N2_Key& lhs, const Q7__N2_Key& rhs) const {
            return lhs.nationKey2 == rhs.nationKey2;
        }
    };
    
    template<>
    struct equal_to<Q7__N2_Parcel> {
        bool operator()(const Q7__N2_Parcel& lhs, const Q7__N2_Parcel& rhs) const {
            return lhs.nationKey2 == rhs.nationKey2;
        }
    };
}

typedef Table<Q7__N2_Parcel> Q7__N2_Table;
typedef SplitTable<Q7__N2_Key, Q7__N2_Parcel> Q7__N2_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7__N2_PARCEL_H
#ifndef RANDOMORDERENUMERATION_Q10__N_PARCEL_H
#define RANDOMORDERENUMERATION_Q10__N_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION
#endif

using namespace std;


struct Q10__N_Key {
    //data
    int nationKey;
    //end-data
    
    void print() const {
        cout << "{" << nationKey << "}";
    }
};


struct Q10__N_Parcel {
    //data
    int nationKey;
    //end-data
    
    //construction
    static Q10__N_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {nationKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey << "}";
    }
};

//conversion to parent key
template<> Q10__N_Key Q10__N_Parcel::to<Q10__N_Key>() const {
    return {nationKey};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q10__N_Key> {
        size_t operator()(const Q10__N_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };
    
    template<>
    struct hash<Q10__N_Parcel> {
        size_t operator()(const Q10__N_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q10__N_Key> {
        bool operator()(const Q10__N_Key& lhs, const Q10__N_Key& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
    
    template<>
    struct equal_to<Q10__N_Parcel> {
        bool operator()(const Q10__N_Parcel& lhs, const Q10__N_Parcel& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
}

typedef Table<Q10__N_Parcel> Q10__N_Table;
typedef SplitTable<Q10__N_Key, Q10__N_Parcel> Q10__N_SplitTable;

#endif //RANDOMORDERENUMERATION_Q10__N_PARCEL_H
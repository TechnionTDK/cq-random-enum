#ifndef RANDOMORDERENUMERATION_QA__N_PARCEL_H
#define RANDOMORDERENUMERATION_QA__N_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QA__R_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct QA__N_Key {
    //data
    int nationKey;
    //end-data
    
    void print() const {
        cout << "{" << nationKey << "}";
    }
};


struct QA__N_Parcel {
    //data
    int nationKey;

    int regionKey;
    //end-data
    
    //construction
    static QA__N_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 1; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int regionKey = stoi(line.substr(0, pos));

        return {nationKey, regionKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey;
        cout << ", " << regionKey << "}";
    }
};

//conversion to parent key
template<> QA__N_Key QA__N_Parcel::to<QA__N_Key>() const {
    return {nationKey};
}

//conversion to childKeys
template<> QA__R_Key QA__N_Parcel::to<QA__R_Key>() const {
    return {regionKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QA__N_Key> {
        size_t operator()(const QA__N_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QA__N_Parcel> {
        size_t operator()(const QA__N_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QA__N_Key> {
        bool operator()(const QA__N_Key& lhs, const QA__N_Key& rhs) const {
            return lhs.nationKey == rhs.nationKey;
        }
    };
    
    template<>
    struct equal_to<QA__N_Parcel> {
        bool operator()(const QA__N_Parcel& lhs, const QA__N_Parcel& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey;
        }
    };
}

typedef Table<QA__N_Parcel> QA__N_Table;
typedef SplitTable<QA__N_Key, QA__N_Parcel> QA__N_SplitTable;

#endif //RANDOMORDERENUMERATION_QA__N_PARCEL_H
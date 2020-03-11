#ifndef RANDOMORDERENUMERATION_QA__S_PARCEL_H
#define RANDOMORDERENUMERATION_QA__S_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#include "QA__N_Parcel.h"
#ifdef PROJECTION
#endif

using namespace std;


struct QA__S_Key {
    //data
    int suppKey;
    //end-data
    
    void print() const {
        cout << "{" << suppKey << "}";
    }
};


struct QA__S_Parcel {
    //data
    int suppKey;

    int nationKey;
    //end-data
    
    //construction
    static QA__S_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int suppKey = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        for(int _i = 0; _i < 2; _i++) {
            pos = line.find("|");
            line = line.substr(pos + 1, string::npos);
        }
        pos = line.find("|");
        int nationKey = stoi(line.substr(0, pos));

        return {suppKey, nationKey};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << suppKey;
        cout << ", " << nationKey << "}";
    }
};

//conversion to parent key
template<> QA__S_Key QA__S_Parcel::to<QA__S_Key>() const {
    return {suppKey};
}

//conversion to childKeys
template<> QA__N_Key QA__S_Parcel::to<QA__N_Key>() const {
    return {nationKey};
}


//hashers & equality operators
namespace std {
    template<>
    struct hash<QA__S_Key> {
        size_t operator()(const QA__S_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            return seed;
        }
    };
    
    template<>
    struct hash<QA__S_Parcel> {
        size_t operator()(const QA__S_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<QA__S_Key> {
        bool operator()(const QA__S_Key& lhs, const QA__S_Key& rhs) const {
            return lhs.suppKey == rhs.suppKey;
        }
    };
    
    template<>
    struct equal_to<QA__S_Parcel> {
        bool operator()(const QA__S_Parcel& lhs, const QA__S_Parcel& rhs) const {
            return lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey;
        }
    };
}

typedef Table<QA__S_Parcel> QA__S_Table;
typedef SplitTable<QA__S_Key, QA__S_Parcel> QA__S_SplitTable;

#endif //RANDOMORDERENUMERATION_QA__S_PARCEL_H
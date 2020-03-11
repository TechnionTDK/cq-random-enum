#ifndef RANDOMORDERENUMERATION_Q7_1_2__N2_PARCEL_H
#define RANDOMORDERENUMERATION_Q7_1_2__N2_PARCEL_H

#include <iostream>
#include <chrono>
#include "../../AbstractDatabase/Table.h"
#include "../../AbstractDatabase/SplitTable.h"
#include <boost/functional/hash.hpp>
#ifdef PROJECTION_Q7_1_2
#endif

using namespace std;


struct Q7_1_2__N2_Key {
    //data
    int nationKey2;
    //end-data
    
    void print() const {
        cout << "{" << nationKey2 << "}";
    }
};


struct Q7_1_2__N2_Parcel {
    //data
    int nationKey2;

    string n2_name;
    //end-data
    
    //construction
    static Q7_1_2__N2_Parcel from(string line) {
        size_t pos;

        pos = line.find("|");
        int nationKey2 = stoi(line.substr(0, pos));
        line = line.substr(pos+1, string::npos);

        pos = line.find("|");
        string n2_name = (line.substr(0, pos));
        line = line.substr(pos+1, string::npos);


        return {nationKey2, n2_name};
    }
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << nationKey2;
        cout << ", " << n2_name << "}";
    }
};

//conversion to parent key
template<> Q7_1_2__N2_Key Q7_1_2__N2_Parcel::to<Q7_1_2__N2_Key>() const {
    return {nationKey2};
}

//conversion to childKeys


//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_1_2__N2_Key> {
        size_t operator()(const Q7_1_2__N2_Key& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey2);
            return seed;
        }
    };
    
    template<>
    struct hash<Q7_1_2__N2_Parcel> {
        size_t operator()(const Q7_1_2__N2_Parcel& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey2);
            boost::hash_combine(seed, p.n2_name);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_1_2__N2_Key> {
        bool operator()(const Q7_1_2__N2_Key& lhs, const Q7_1_2__N2_Key& rhs) const {
            return lhs.nationKey2 == rhs.nationKey2;
        }
    };
    
    template<>
    struct equal_to<Q7_1_2__N2_Parcel> {
        bool operator()(const Q7_1_2__N2_Parcel& lhs, const Q7_1_2__N2_Parcel& rhs) const {
            return lhs.nationKey2 == rhs.nationKey2 && lhs.n2_name == rhs.n2_name;
        }
    };
}

typedef Table<Q7_1_2__N2_Parcel> Q7_1_2__N2_Table;
typedef SplitTable<Q7_1_2__N2_Key, Q7_1_2__N2_Parcel> Q7_1_2__N2_SplitTable;

#endif //RANDOMORDERENUMERATION_Q7_1_2__N2_PARCEL_H
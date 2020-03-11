#ifndef RANDOMORDERENUMERATION_QAANSWER_H
#define RANDOMORDERENUMERATION_QAANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "QA__O_Parcel.h"
#include "QA__L_Parcel.h"
#include "QA__S_Parcel.h"
#include "QA__N_Parcel.h"
#include "QA__R_Parcel.h"

struct QAAnswer {
    //data
    int orderKey;
    int suppKey;
    int nationKey;
    int regionKey;
    string rname;
    //end data
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }
    
    template<typename T>
    void set(const T& t) {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << suppKey;
        cout << ", " << nationKey;
        cout << ", " << regionKey;
        cout << ", " << rname << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << suppKey;
        st << ", " << nationKey;
        st << ", " << regionKey;
        st << ", " << rname;
        st << "}";
        return st.str();
    }
};

template<> QA__O_Key QAAnswer::to<QA__O_Key>() const {
    return {};
}

template<> QA__L_Key QAAnswer::to<QA__L_Key>() const {
    return {orderKey};
}

template<> QA__S_Key QAAnswer::to<QA__S_Key>() const {
    return {suppKey};
}

template<> QA__N_Key QAAnswer::to<QA__N_Key>() const {
    return {nationKey};
}

template<> QA__R_Key QAAnswer::to<QA__R_Key>() const {
    return {regionKey};
}

template<> QA__O_Parcel QAAnswer::to<QA__O_Parcel>() const {
    return {orderKey};
}

template<> QA__L_Parcel QAAnswer::to<QA__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QA__S_Parcel QAAnswer::to<QA__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QA__N_Parcel QAAnswer::to<QA__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QA__R_Parcel QAAnswer::to<QA__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QAAnswer::set<QA__O_Parcel>(const QA__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QAAnswer::set<QA__L_Parcel>(const QA__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QAAnswer::set<QA__S_Parcel>(const QA__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QAAnswer::set<QA__N_Parcel>(const QA__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QAAnswer::set<QA__R_Parcel>(const QA__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QAAnswer> {
        size_t operator()(const QAAnswer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            boost::hash_combine(seed, p.rname);
            return seed;
        }
    };

    template<>
    struct equal_to<QAAnswer> {
        bool operator()(const QAAnswer& lhs, const QAAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#else

#include "QA__O_Parcel.h"
#include "QA__L_Parcel.h"
#include "QA__S_Parcel.h"
#include "QA__N_Parcel.h"
#include "QA__R_Parcel.h"

struct QAAnswer {
    //data
    int orderKey;
    int suppKey;
    int nationKey;
    int regionKey;
    string rname;
    //end data
    
    template<typename T>
    T to() const {
        throw runtime_error("not implemented");
    }
    
    template<typename T>
    void set(const T& t) {
        throw runtime_error("not implemented");
    }

    void print() const {
        cout << "{" << orderKey;
        cout << ", " << suppKey;
        cout << ", " << nationKey;
        cout << ", " << regionKey;
        cout << ", " << rname << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << suppKey;
        st << ", " << nationKey;
        st << ", " << regionKey;
        st << ", " << rname;
        st << "}";
        return st.str();
    }
};

template<> QA__O_Key QAAnswer::to<QA__O_Key>() const {
    return {};
}

template<> QA__L_Key QAAnswer::to<QA__L_Key>() const {
    return {orderKey};
}

template<> QA__S_Key QAAnswer::to<QA__S_Key>() const {
    return {suppKey};
}

template<> QA__N_Key QAAnswer::to<QA__N_Key>() const {
    return {nationKey};
}

template<> QA__R_Key QAAnswer::to<QA__R_Key>() const {
    return {regionKey};
}

template<> QA__O_Parcel QAAnswer::to<QA__O_Parcel>() const {
    return {orderKey};
}

template<> QA__L_Parcel QAAnswer::to<QA__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QA__S_Parcel QAAnswer::to<QA__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QA__N_Parcel QAAnswer::to<QA__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QA__R_Parcel QAAnswer::to<QA__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QAAnswer::set<QA__O_Parcel>(const QA__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QAAnswer::set<QA__L_Parcel>(const QA__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QAAnswer::set<QA__S_Parcel>(const QA__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QAAnswer::set<QA__N_Parcel>(const QA__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QAAnswer::set<QA__R_Parcel>(const QA__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QAAnswer> {
        size_t operator()(const QAAnswer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.regionKey);
            boost::hash_combine(seed, p.rname);
            return seed;
        }
    };

    template<>
    struct equal_to<QAAnswer> {
        bool operator()(const QAAnswer& lhs, const QAAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_QAANSWER_H
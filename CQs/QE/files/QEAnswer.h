#ifndef RANDOMORDERENUMERATION_QEANSWER_H
#define RANDOMORDERENUMERATION_QEANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "QE__O_Parcel.h"
#include "QE__L_Parcel.h"
#include "QE__S_Parcel.h"
#include "QE__N_Parcel.h"
#include "QE__R_Parcel.h"

struct QEAnswer {
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

template<> QE__O_Key QEAnswer::to<QE__O_Key>() const {
    return {};
}

template<> QE__L_Key QEAnswer::to<QE__L_Key>() const {
    return {orderKey};
}

template<> QE__S_Key QEAnswer::to<QE__S_Key>() const {
    return {suppKey};
}

template<> QE__N_Key QEAnswer::to<QE__N_Key>() const {
    return {nationKey};
}

template<> QE__R_Key QEAnswer::to<QE__R_Key>() const {
    return {regionKey};
}

template<> QE__O_Parcel QEAnswer::to<QE__O_Parcel>() const {
    return {orderKey};
}

template<> QE__L_Parcel QEAnswer::to<QE__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QE__S_Parcel QEAnswer::to<QE__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QE__N_Parcel QEAnswer::to<QE__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QE__R_Parcel QEAnswer::to<QE__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QEAnswer::set<QE__O_Parcel>(const QE__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QEAnswer::set<QE__L_Parcel>(const QE__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QEAnswer::set<QE__S_Parcel>(const QE__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QEAnswer::set<QE__N_Parcel>(const QE__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QEAnswer::set<QE__R_Parcel>(const QE__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QEAnswer> {
        size_t operator()(const QEAnswer& p) const {
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
    struct equal_to<QEAnswer> {
        bool operator()(const QEAnswer& lhs, const QEAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#else

#include "QE__O_Parcel.h"
#include "QE__L_Parcel.h"
#include "QE__S_Parcel.h"
#include "QE__N_Parcel.h"
#include "QE__R_Parcel.h"

struct QEAnswer {
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

template<> QE__O_Key QEAnswer::to<QE__O_Key>() const {
    return {};
}

template<> QE__L_Key QEAnswer::to<QE__L_Key>() const {
    return {orderKey};
}

template<> QE__S_Key QEAnswer::to<QE__S_Key>() const {
    return {suppKey};
}

template<> QE__N_Key QEAnswer::to<QE__N_Key>() const {
    return {nationKey};
}

template<> QE__R_Key QEAnswer::to<QE__R_Key>() const {
    return {regionKey};
}

template<> QE__O_Parcel QEAnswer::to<QE__O_Parcel>() const {
    return {orderKey};
}

template<> QE__L_Parcel QEAnswer::to<QE__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QE__S_Parcel QEAnswer::to<QE__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QE__N_Parcel QEAnswer::to<QE__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QE__R_Parcel QEAnswer::to<QE__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QEAnswer::set<QE__O_Parcel>(const QE__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QEAnswer::set<QE__L_Parcel>(const QE__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QEAnswer::set<QE__S_Parcel>(const QE__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QEAnswer::set<QE__N_Parcel>(const QE__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QEAnswer::set<QE__R_Parcel>(const QE__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QEAnswer> {
        size_t operator()(const QEAnswer& p) const {
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
    struct equal_to<QEAnswer> {
        bool operator()(const QEAnswer& lhs, const QEAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_QEANSWER_H
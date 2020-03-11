#ifndef RANDOMORDERENUMERATION_QAEANSWER_H
#define RANDOMORDERENUMERATION_QAEANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION_QAE

#include "QAE__O_Parcel.h"
#include "QAE__L_Parcel.h"
#include "QAE__S_Parcel.h"
#include "QAE__N_Parcel.h"
#include "QAE__R_Parcel.h"

struct QAEAnswer {
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

template<> QAE__O_Key QAEAnswer::to<QAE__O_Key>() const {
    return {};
}

template<> QAE__L_Key QAEAnswer::to<QAE__L_Key>() const {
    return {orderKey};
}

template<> QAE__S_Key QAEAnswer::to<QAE__S_Key>() const {
    return {suppKey};
}

template<> QAE__N_Key QAEAnswer::to<QAE__N_Key>() const {
    return {nationKey};
}

template<> QAE__R_Key QAEAnswer::to<QAE__R_Key>() const {
    return {regionKey};
}

template<> QAE__O_Parcel QAEAnswer::to<QAE__O_Parcel>() const {
    return {orderKey};
}

template<> QAE__L_Parcel QAEAnswer::to<QAE__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QAE__S_Parcel QAEAnswer::to<QAE__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QAE__N_Parcel QAEAnswer::to<QAE__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QAE__R_Parcel QAEAnswer::to<QAE__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QAEAnswer::set<QAE__O_Parcel>(const QAE__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QAEAnswer::set<QAE__L_Parcel>(const QAE__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QAEAnswer::set<QAE__S_Parcel>(const QAE__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QAEAnswer::set<QAE__N_Parcel>(const QAE__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QAEAnswer::set<QAE__R_Parcel>(const QAE__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QAEAnswer> {
        size_t operator()(const QAEAnswer& p) const {
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
    struct equal_to<QAEAnswer> {
        bool operator()(const QAEAnswer& lhs, const QAEAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#else

#include "QAE__O_Parcel.h"
#include "QAE__L_Parcel.h"
#include "QAE__S_Parcel.h"
#include "QAE__N_Parcel.h"
#include "QAE__R_Parcel.h"

struct QAEAnswer {
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

template<> QAE__O_Key QAEAnswer::to<QAE__O_Key>() const {
    return {};
}

template<> QAE__L_Key QAEAnswer::to<QAE__L_Key>() const {
    return {orderKey};
}

template<> QAE__S_Key QAEAnswer::to<QAE__S_Key>() const {
    return {suppKey};
}

template<> QAE__N_Key QAEAnswer::to<QAE__N_Key>() const {
    return {nationKey};
}

template<> QAE__R_Key QAEAnswer::to<QAE__R_Key>() const {
    return {regionKey};
}

template<> QAE__O_Parcel QAEAnswer::to<QAE__O_Parcel>() const {
    return {orderKey};
}

template<> QAE__L_Parcel QAEAnswer::to<QAE__L_Parcel>() const {
    return {orderKey, suppKey};
}

template<> QAE__S_Parcel QAEAnswer::to<QAE__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> QAE__N_Parcel QAEAnswer::to<QAE__N_Parcel>() const {
    return {nationKey, regionKey};
}

template<> QAE__R_Parcel QAEAnswer::to<QAE__R_Parcel>() const {
    return {regionKey, rname};
}


template<> void QAEAnswer::set<QAE__O_Parcel>(const QAE__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void QAEAnswer::set<QAE__L_Parcel>(const QAE__L_Parcel& p) {
    orderKey = p.orderKey;
    suppKey = p.suppKey;
}

template<> void QAEAnswer::set<QAE__S_Parcel>(const QAE__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void QAEAnswer::set<QAE__N_Parcel>(const QAE__N_Parcel& p) {
    nationKey = p.nationKey;
    regionKey = p.regionKey;
}

template<> void QAEAnswer::set<QAE__R_Parcel>(const QAE__R_Parcel& p) {
    regionKey = p.regionKey;
    rname = p.rname;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<QAEAnswer> {
        size_t operator()(const QAEAnswer& p) const {
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
    struct equal_to<QAEAnswer> {
        bool operator()(const QAEAnswer& lhs, const QAEAnswer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.suppKey == rhs.suppKey && lhs.nationKey == rhs.nationKey && lhs.regionKey == rhs.regionKey && lhs.rname == rhs.rname;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_QAEANSWER_H
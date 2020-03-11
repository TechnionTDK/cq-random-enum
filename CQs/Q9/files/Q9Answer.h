#ifndef RANDOMORDERENUMERATION_Q9ANSWER_H
#define RANDOMORDERENUMERATION_Q9ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q9__L_Parcel.h"
#include "Q9__S_Parcel.h"
#include "Q9__O_Parcel.h"
#include "Q9__PS_Parcel.h"
#include "Q9__N_Parcel.h"
#include "Q9__P_Parcel.h"

struct Q9Answer {
    //data
    int nationKey;
    int suppKey;
    int orderKey;
    int lnumber;
    int partKey;
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
        cout << "{" << nationKey;
        cout << ", " << suppKey;
        cout << ", " << orderKey;
        cout << ", " << lnumber;
        cout << ", " << partKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << nationKey;
        st << ", " << suppKey;
        st << ", " << orderKey;
        st << ", " << lnumber;
        st << ", " << partKey;
        st << "}";
        return st.str();
    }
};

template<> Q9__L_Key Q9Answer::to<Q9__L_Key>() const {
    return {};
}

template<> Q9__S_Key Q9Answer::to<Q9__S_Key>() const {
    return {suppKey};
}

template<> Q9__O_Key Q9Answer::to<Q9__O_Key>() const {
    return {orderKey};
}

template<> Q9__PS_Key Q9Answer::to<Q9__PS_Key>() const {
    return {partKey, suppKey};
}

template<> Q9__N_Key Q9Answer::to<Q9__N_Key>() const {
    return {nationKey};
}

template<> Q9__P_Key Q9Answer::to<Q9__P_Key>() const {
    return {partKey};
}

template<> Q9__L_Parcel Q9Answer::to<Q9__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q9__S_Parcel Q9Answer::to<Q9__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q9__O_Parcel Q9Answer::to<Q9__O_Parcel>() const {
    return {orderKey};
}

template<> Q9__PS_Parcel Q9Answer::to<Q9__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q9__N_Parcel Q9Answer::to<Q9__N_Parcel>() const {
    return {nationKey};
}

template<> Q9__P_Parcel Q9Answer::to<Q9__P_Parcel>() const {
    return {partKey};
}


template<> void Q9Answer::set<Q9__L_Parcel>(const Q9__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q9Answer::set<Q9__S_Parcel>(const Q9__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q9Answer::set<Q9__O_Parcel>(const Q9__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void Q9Answer::set<Q9__PS_Parcel>(const Q9__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q9Answer::set<Q9__N_Parcel>(const Q9__N_Parcel& p) {
    nationKey = p.nationKey;
}

template<> void Q9Answer::set<Q9__P_Parcel>(const Q9__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q9Answer> {
        size_t operator()(const Q9Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.partKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q9Answer> {
        bool operator()(const Q9Answer& lhs, const Q9Answer& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.suppKey == rhs.suppKey && lhs.orderKey == rhs.orderKey && lhs.lnumber == rhs.lnumber && lhs.partKey == rhs.partKey;
        }
    };
}

#else

#include "Q9__L_Parcel.h"
#include "Q9__S_Parcel.h"
#include "Q9__O_Parcel.h"
#include "Q9__PS_Parcel.h"
#include "Q9__N_Parcel.h"
#include "Q9__P_Parcel.h"

struct Q9Answer {
    //data
    int nationKey;
    int suppKey;
    int orderKey;
    int lnumber;
    int partKey;
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
        cout << "{" << nationKey;
        cout << ", " << suppKey;
        cout << ", " << orderKey;
        cout << ", " << lnumber;
        cout << ", " << partKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << nationKey;
        st << ", " << suppKey;
        st << ", " << orderKey;
        st << ", " << lnumber;
        st << ", " << partKey;
        st << "}";
        return st.str();
    }
};

template<> Q9__L_Key Q9Answer::to<Q9__L_Key>() const {
    return {};
}

template<> Q9__S_Key Q9Answer::to<Q9__S_Key>() const {
    return {suppKey};
}

template<> Q9__O_Key Q9Answer::to<Q9__O_Key>() const {
    return {orderKey};
}

template<> Q9__PS_Key Q9Answer::to<Q9__PS_Key>() const {
    return {partKey, suppKey};
}

template<> Q9__N_Key Q9Answer::to<Q9__N_Key>() const {
    return {nationKey};
}

template<> Q9__P_Key Q9Answer::to<Q9__P_Key>() const {
    return {partKey};
}

template<> Q9__L_Parcel Q9Answer::to<Q9__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q9__S_Parcel Q9Answer::to<Q9__S_Parcel>() const {
    return {suppKey, nationKey};
}

template<> Q9__O_Parcel Q9Answer::to<Q9__O_Parcel>() const {
    return {orderKey};
}

template<> Q9__PS_Parcel Q9Answer::to<Q9__PS_Parcel>() const {
    return {partKey, suppKey};
}

template<> Q9__N_Parcel Q9Answer::to<Q9__N_Parcel>() const {
    return {nationKey};
}

template<> Q9__P_Parcel Q9Answer::to<Q9__P_Parcel>() const {
    return {partKey};
}


template<> void Q9Answer::set<Q9__L_Parcel>(const Q9__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q9Answer::set<Q9__S_Parcel>(const Q9__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey = p.nationKey;
}

template<> void Q9Answer::set<Q9__O_Parcel>(const Q9__O_Parcel& p) {
    orderKey = p.orderKey;
}

template<> void Q9Answer::set<Q9__PS_Parcel>(const Q9__PS_Parcel& p) {
    partKey = p.partKey;
    suppKey = p.suppKey;
}

template<> void Q9Answer::set<Q9__N_Parcel>(const Q9__N_Parcel& p) {
    nationKey = p.nationKey;
}

template<> void Q9Answer::set<Q9__P_Parcel>(const Q9__P_Parcel& p) {
    partKey = p.partKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q9Answer> {
        size_t operator()(const Q9Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.nationKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.partKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q9Answer> {
        bool operator()(const Q9Answer& lhs, const Q9Answer& rhs) const {
            return lhs.nationKey == rhs.nationKey && lhs.suppKey == rhs.suppKey && lhs.orderKey == rhs.orderKey && lhs.lnumber == rhs.lnumber && lhs.partKey == rhs.partKey;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q9ANSWER_H
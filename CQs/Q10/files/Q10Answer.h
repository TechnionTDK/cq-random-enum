#ifndef RANDOMORDERENUMERATION_Q10ANSWER_H
#define RANDOMORDERENUMERATION_Q10ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q10__C_Parcel.h"
#include "Q10__L_Parcel.h"
#include "Q10__O_Parcel.h"
#include "Q10__N_Parcel.h"

struct Q10Answer {
    //data
    int orderKey;
    int custKey;
    int partKey;
    int suppKey;
    int lnumber;
    int nationKey;
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
        cout << ", " << custKey;
        cout << ", " << partKey;
        cout << ", " << suppKey;
        cout << ", " << lnumber;
        cout << ", " << nationKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << ", " << nationKey;
        st << "}";
        return st.str();
    }
};

template<> Q10__C_Key Q10Answer::to<Q10__C_Key>() const {
    return {custKey};
}

template<> Q10__L_Key Q10Answer::to<Q10__L_Key>() const {
    return {orderKey};
}

template<> Q10__O_Key Q10Answer::to<Q10__O_Key>() const {
    return {};
}

template<> Q10__N_Key Q10Answer::to<Q10__N_Key>() const {
    return {nationKey};
}

template<> Q10__C_Parcel Q10Answer::to<Q10__C_Parcel>() const {
    return {custKey, nationKey};
}

template<> Q10__L_Parcel Q10Answer::to<Q10__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q10__O_Parcel Q10Answer::to<Q10__O_Parcel>() const {
    return {orderKey, custKey};
}

template<> Q10__N_Parcel Q10Answer::to<Q10__N_Parcel>() const {
    return {nationKey};
}


template<> void Q10Answer::set<Q10__C_Parcel>(const Q10__C_Parcel& p) {
    custKey = p.custKey;
    nationKey = p.nationKey;
}

template<> void Q10Answer::set<Q10__L_Parcel>(const Q10__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q10Answer::set<Q10__O_Parcel>(const Q10__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

template<> void Q10Answer::set<Q10__N_Parcel>(const Q10__N_Parcel& p) {
    nationKey = p.nationKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q10Answer> {
        size_t operator()(const Q10Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q10Answer> {
        bool operator()(const Q10Answer& lhs, const Q10Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber && lhs.nationKey == rhs.nationKey;
        }
    };
}

#else

#include "Q10__C_Parcel.h"
#include "Q10__L_Parcel.h"
#include "Q10__O_Parcel.h"
#include "Q10__N_Parcel.h"

struct Q10Answer {
    //data
    int orderKey;
    int custKey;
    int partKey;
    int suppKey;
    int lnumber;
    int nationKey;
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
        cout << ", " << custKey;
        cout << ", " << partKey;
        cout << ", " << suppKey;
        cout << ", " << lnumber;
        cout << ", " << nationKey << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << ", " << nationKey;
        st << "}";
        return st.str();
    }
};

template<> Q10__C_Key Q10Answer::to<Q10__C_Key>() const {
    return {custKey};
}

template<> Q10__L_Key Q10Answer::to<Q10__L_Key>() const {
    return {orderKey};
}

template<> Q10__O_Key Q10Answer::to<Q10__O_Key>() const {
    return {};
}

template<> Q10__N_Key Q10Answer::to<Q10__N_Key>() const {
    return {nationKey};
}

template<> Q10__C_Parcel Q10Answer::to<Q10__C_Parcel>() const {
    return {custKey, nationKey};
}

template<> Q10__L_Parcel Q10Answer::to<Q10__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q10__O_Parcel Q10Answer::to<Q10__O_Parcel>() const {
    return {orderKey, custKey};
}

template<> Q10__N_Parcel Q10Answer::to<Q10__N_Parcel>() const {
    return {nationKey};
}


template<> void Q10Answer::set<Q10__C_Parcel>(const Q10__C_Parcel& p) {
    custKey = p.custKey;
    nationKey = p.nationKey;
}

template<> void Q10Answer::set<Q10__L_Parcel>(const Q10__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q10Answer::set<Q10__O_Parcel>(const Q10__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

template<> void Q10Answer::set<Q10__N_Parcel>(const Q10__N_Parcel& p) {
    nationKey = p.nationKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q10Answer> {
        size_t operator()(const Q10Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.nationKey);
            return seed;
        }
    };

    template<>
    struct equal_to<Q10Answer> {
        bool operator()(const Q10Answer& lhs, const Q10Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber && lhs.nationKey == rhs.nationKey;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q10ANSWER_H
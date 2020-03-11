#ifndef RANDOMORDERENUMERATION_Q3ANSWER_H
#define RANDOMORDERENUMERATION_Q3ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q3__C_Parcel.h"
#include "Q3__L_Parcel.h"
#include "Q3__O_Parcel.h"

struct Q3Answer {
    //data
    int orderKey;
    int custKey;
    int partKey;
    int suppKey;
    int lnumber;
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
        cout << ", " << lnumber << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << "}";
        return st.str();
    }
};

template<> Q3__C_Key Q3Answer::to<Q3__C_Key>() const {
    return {custKey};
}

template<> Q3__L_Key Q3Answer::to<Q3__L_Key>() const {
    return {orderKey};
}

template<> Q3__O_Key Q3Answer::to<Q3__O_Key>() const {
    return {};
}

template<> Q3__C_Parcel Q3Answer::to<Q3__C_Parcel>() const {
    return {custKey};
}

template<> Q3__L_Parcel Q3Answer::to<Q3__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q3__O_Parcel Q3Answer::to<Q3__O_Parcel>() const {
    return {orderKey, custKey};
}


template<> void Q3Answer::set<Q3__C_Parcel>(const Q3__C_Parcel& p) {
    custKey = p.custKey;
}

template<> void Q3Answer::set<Q3__L_Parcel>(const Q3__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q3Answer::set<Q3__O_Parcel>(const Q3__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q3Answer> {
        size_t operator()(const Q3Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            return seed;
        }
    };

    template<>
    struct equal_to<Q3Answer> {
        bool operator()(const Q3Answer& lhs, const Q3Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber;
        }
    };
}

#else

#include "Q3__C_Parcel.h"
#include "Q3__L_Parcel.h"
#include "Q3__O_Parcel.h"

struct Q3Answer {
    //data
    int orderKey;
    int custKey;
    int partKey;
    int suppKey;
    int lnumber;
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
        cout << ", " << lnumber << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << "}";
        return st.str();
    }
};

template<> Q3__C_Key Q3Answer::to<Q3__C_Key>() const {
    return {custKey};
}

template<> Q3__L_Key Q3Answer::to<Q3__L_Key>() const {
    return {orderKey};
}

template<> Q3__O_Key Q3Answer::to<Q3__O_Key>() const {
    return {};
}

template<> Q3__C_Parcel Q3Answer::to<Q3__C_Parcel>() const {
    return {custKey};
}

template<> Q3__L_Parcel Q3Answer::to<Q3__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q3__O_Parcel Q3Answer::to<Q3__O_Parcel>() const {
    return {orderKey, custKey};
}


template<> void Q3Answer::set<Q3__C_Parcel>(const Q3__C_Parcel& p) {
    custKey = p.custKey;
}

template<> void Q3Answer::set<Q3__L_Parcel>(const Q3__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q3Answer::set<Q3__O_Parcel>(const Q3__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q3Answer> {
        size_t operator()(const Q3Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            return seed;
        }
    };

    template<>
    struct equal_to<Q3Answer> {
        bool operator()(const Q3Answer& lhs, const Q3Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q3ANSWER_H
#ifndef RANDOMORDERENUMERATION_Q7_1ANSWER_H
#define RANDOMORDERENUMERATION_Q7_1ANSWER_H

#include <iostream>
#include <chrono>
#include <boost/functional/hash.hpp>

using namespace std;

#ifndef PROJECTION

#include "Q7_1__O_Parcel.h"
#include "Q7_1__L_Parcel.h"
#include "Q7_1__C_Parcel.h"
#include "Q7_1__S_Parcel.h"
#include "Q7_1__N1_Parcel.h"
#include "Q7_1__N2_Parcel.h"

struct Q7_1Answer {
    //data
    int orderKey;
    int custKey;
    int nationKey1;
    int nationKey2;
    int partKey;
    int suppKey;
    int lnumber;
    string n1_name;
    string n2_name;
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
        cout << ", " << nationKey1;
        cout << ", " << nationKey2;
        cout << ", " << partKey;
        cout << ", " << suppKey;
        cout << ", " << lnumber;
        cout << ", " << n1_name;
        cout << ", " << n2_name << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << nationKey1;
        st << ", " << nationKey2;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << ", " << n1_name;
        st << ", " << n2_name;
        st << "}";
        return st.str();
    }
};

template<> Q7_1__N2_Key Q7_1Answer::to<Q7_1__N2_Key>() const {
    return {nationKey2};
}

template<> Q7_1__N1_Key Q7_1Answer::to<Q7_1__N1_Key>() const {
    return {nationKey1};
}

template<> Q7_1__S_Key Q7_1Answer::to<Q7_1__S_Key>() const {
    return {suppKey};
}

template<> Q7_1__C_Key Q7_1Answer::to<Q7_1__C_Key>() const {
    return {custKey};
}

template<> Q7_1__L_Key Q7_1Answer::to<Q7_1__L_Key>() const {
    return {orderKey};
}

template<> Q7_1__O_Key Q7_1Answer::to<Q7_1__O_Key>() const {
    return {};
}

template<> Q7_1__O_Parcel Q7_1Answer::to<Q7_1__O_Parcel>() const {
    return {orderKey, custKey};
}

template<> Q7_1__L_Parcel Q7_1Answer::to<Q7_1__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q7_1__C_Parcel Q7_1Answer::to<Q7_1__C_Parcel>() const {
    return {custKey, nationKey2};
}

template<> Q7_1__S_Parcel Q7_1Answer::to<Q7_1__S_Parcel>() const {
    return {suppKey, nationKey1};
}

template<> Q7_1__N1_Parcel Q7_1Answer::to<Q7_1__N1_Parcel>() const {
    return {nationKey1, n1_name};
}

template<> Q7_1__N2_Parcel Q7_1Answer::to<Q7_1__N2_Parcel>() const {
    return {nationKey2, n2_name};
}


template<> void Q7_1Answer::set<Q7_1__O_Parcel>(const Q7_1__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

template<> void Q7_1Answer::set<Q7_1__L_Parcel>(const Q7_1__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q7_1Answer::set<Q7_1__C_Parcel>(const Q7_1__C_Parcel& p) {
    custKey = p.custKey;
    nationKey2 = p.nationKey2;
}

template<> void Q7_1Answer::set<Q7_1__S_Parcel>(const Q7_1__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey1 = p.nationKey1;
}

template<> void Q7_1Answer::set<Q7_1__N1_Parcel>(const Q7_1__N1_Parcel& p) {
    nationKey1 = p.nationKey1;
    n1_name = p.n1_name;
}

template<> void Q7_1Answer::set<Q7_1__N2_Parcel>(const Q7_1__N2_Parcel& p) {
    nationKey2 = p.nationKey2;
    n2_name = p.n2_name;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_1Answer> {
        size_t operator()(const Q7_1Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.nationKey1);
            boost::hash_combine(seed, p.nationKey2);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.n1_name);
            boost::hash_combine(seed, p.n2_name);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_1Answer> {
        bool operator()(const Q7_1Answer& lhs, const Q7_1Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.nationKey1 == rhs.nationKey1 && lhs.nationKey2 == rhs.nationKey2 && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber && lhs.n1_name == rhs.n1_name && lhs.n2_name == rhs.n2_name;
        }
    };
}

#else

#include "Q7_1__O_Parcel.h"
#include "Q7_1__L_Parcel.h"
#include "Q7_1__C_Parcel.h"
#include "Q7_1__S_Parcel.h"
#include "Q7_1__N1_Parcel.h"
#include "Q7_1__N2_Parcel.h"

struct Q7_1Answer {
    //data
    int orderKey;
    int custKey;
    int nationKey1;
    int nationKey2;
    int partKey;
    int suppKey;
    int lnumber;
    string n1_name;
    string n2_name;
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
        cout << ", " << nationKey1;
        cout << ", " << nationKey2;
        cout << ", " << partKey;
        cout << ", " << suppKey;
        cout << ", " << lnumber;
        cout << ", " << n1_name;
        cout << ", " << n2_name << "}";
    }
    
    string to_string() const {
        stringstream st;
        st << "{" << orderKey;
        st << ", " << custKey;
        st << ", " << nationKey1;
        st << ", " << nationKey2;
        st << ", " << partKey;
        st << ", " << suppKey;
        st << ", " << lnumber;
        st << ", " << n1_name;
        st << ", " << n2_name;
        st << "}";
        return st.str();
    }
};

template<> Q7_1__N2_Key Q7_1Answer::to<Q7_1__N2_Key>() const {
    return {nationKey2};
}

template<> Q7_1__N1_Key Q7_1Answer::to<Q7_1__N1_Key>() const {
    return {nationKey1};
}

template<> Q7_1__S_Key Q7_1Answer::to<Q7_1__S_Key>() const {
    return {suppKey};
}

template<> Q7_1__C_Key Q7_1Answer::to<Q7_1__C_Key>() const {
    return {custKey};
}

template<> Q7_1__L_Key Q7_1Answer::to<Q7_1__L_Key>() const {
    return {orderKey};
}

template<> Q7_1__O_Key Q7_1Answer::to<Q7_1__O_Key>() const {
    return {};
}

template<> Q7_1__O_Parcel Q7_1Answer::to<Q7_1__O_Parcel>() const {
    return {orderKey, custKey};
}

template<> Q7_1__L_Parcel Q7_1Answer::to<Q7_1__L_Parcel>() const {
    return {orderKey, partKey, suppKey, lnumber};
}

template<> Q7_1__C_Parcel Q7_1Answer::to<Q7_1__C_Parcel>() const {
    return {custKey, nationKey2};
}

template<> Q7_1__S_Parcel Q7_1Answer::to<Q7_1__S_Parcel>() const {
    return {suppKey, nationKey1};
}

template<> Q7_1__N1_Parcel Q7_1Answer::to<Q7_1__N1_Parcel>() const {
    return {nationKey1, n1_name};
}

template<> Q7_1__N2_Parcel Q7_1Answer::to<Q7_1__N2_Parcel>() const {
    return {nationKey2, n2_name};
}


template<> void Q7_1Answer::set<Q7_1__O_Parcel>(const Q7_1__O_Parcel& p) {
    orderKey = p.orderKey;
    custKey = p.custKey;
}

template<> void Q7_1Answer::set<Q7_1__L_Parcel>(const Q7_1__L_Parcel& p) {
    orderKey = p.orderKey;
    partKey = p.partKey;
    suppKey = p.suppKey;
    lnumber = p.lnumber;
}

template<> void Q7_1Answer::set<Q7_1__C_Parcel>(const Q7_1__C_Parcel& p) {
    custKey = p.custKey;
    nationKey2 = p.nationKey2;
}

template<> void Q7_1Answer::set<Q7_1__S_Parcel>(const Q7_1__S_Parcel& p) {
    suppKey = p.suppKey;
    nationKey1 = p.nationKey1;
}

template<> void Q7_1Answer::set<Q7_1__N1_Parcel>(const Q7_1__N1_Parcel& p) {
    nationKey1 = p.nationKey1;
    n1_name = p.n1_name;
}

template<> void Q7_1Answer::set<Q7_1__N2_Parcel>(const Q7_1__N2_Parcel& p) {
    nationKey2 = p.nationKey2;
    n2_name = p.n2_name;
}

//hashers & equality operators
namespace std {
    template<>
    struct hash<Q7_1Answer> {
        size_t operator()(const Q7_1Answer& p) const {
            size_t seed = 0;
            boost::hash_combine(seed, p.orderKey);
            boost::hash_combine(seed, p.custKey);
            boost::hash_combine(seed, p.nationKey1);
            boost::hash_combine(seed, p.nationKey2);
            boost::hash_combine(seed, p.partKey);
            boost::hash_combine(seed, p.suppKey);
            boost::hash_combine(seed, p.lnumber);
            boost::hash_combine(seed, p.n1_name);
            boost::hash_combine(seed, p.n2_name);
            return seed;
        }
    };

    template<>
    struct equal_to<Q7_1Answer> {
        bool operator()(const Q7_1Answer& lhs, const Q7_1Answer& rhs) const {
            return lhs.orderKey == rhs.orderKey && lhs.custKey == rhs.custKey && lhs.nationKey1 == rhs.nationKey1 && lhs.nationKey2 == rhs.nationKey2 && lhs.partKey == rhs.partKey && lhs.suppKey == rhs.suppKey && lhs.lnumber == rhs.lnumber && lhs.n1_name == rhs.n1_name && lhs.n2_name == rhs.n2_name;
        }
    };
}

#endif

#endif //RANDOMORDERENUMERATION_Q7_1ANSWER_H